#pragma region Include

#include <math.h>
#include <string>
#include <typeinfo>
#include "GameScene.h"
#include "GameObject.h"
#include "../libs/B2DebugDrawLayer.h"
#include "../libs/TiledBodyCreator.h"
#include "../libs/GB2ShapeCache-x.h"
#include "RayCast.h"
#include "SceneMgr.h"
#include "MainMenuScene.h"
#include "Utils.h"
#include "AudioEngine.h"
#include "SoundMgr.h"

#pragma endregion

Scene* GameScene::createScene(bool boolean)
{
	Scene* scene = Scene::create();

	GameScene* layer = GameScene::createWithLoad(boolean);

	scene->addChild(layer, 0);

	return scene;
}

GameScene* GameScene::createWithLoad(bool boolean)
{
	GameScene* scene = new GameScene();
	if (scene && scene->initWithLoad(boolean))
	{
		scene->autorelease();
		return scene;
	}
	delete scene;
	scene = nullptr;
	return nullptr;
}

bool GameScene::initWithLoad(bool boolean)
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->m_isLoadGame = boolean;
	CCLOG("crash 1");
	// Tao the gioi
	this->m_physicWorld->getWorld()->SetContactListener(this->m_contactListener);
	this->m_drawNode = DrawNode::create();
	this->addChild(this->m_drawNode, 10);

	if (isEnableDebug)
		this->addChild(B2DebugDrawLayer::create(this->m_physicWorld->getWorld(), 32.0f), INT_MAX);
	CCLOG("crash 2");
	this->m_map = MapTMX::create();
	this->m_map->SetInit(Path_TMX_MAP);
	this->addChild(this->m_map);

	this->CreateCollision(this->m_physicWorld->getWorld());
	this->CreatePlayer(boolean);

	this->archivement = Archivement::create();
	this->addChild(this->archivement);

	this->CreateMovementButton();
	this->CreateShopButton();
	this->CreateBackpackButton();
	this->CreateCamera();

	CCLOG("crash 3");
	this->CreateBackground();
	CCLOG("crash 4");
	this->CreateNotification();
	CCLOG("crash 5");
	// Create Diamond
	this->CreateDiamond();
	// Create Check Point
	this->CreateCheckPoint();
	// Create Treasure Chest
	this->CreateTreasureChest();
	// Create Enemy
	this->CreateEnemy();
	// Create boss
	this->CreateBoss();
	// Movingplatform
	this->CreateMovingPlatform();
	// Elevator
	this->CreateElevator();
	// Stone
	this->CreateStone();

	this->CreateCheckPointLocate();

	this->CreatePartical();
	CCLOG("crash 4");
	// Lang nghe su kien touch
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::OnTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::OnTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::OnTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->CreateSimulationWorld(this->m_physicWorld->GetGravity());

	this->m_location = Location::create();
	this->m_location->setVisible(false);
	this->m_location->setScale(0.8);
	this->addChild(this->m_location);
	this->m_location->setCameraMask((unsigned int)CameraFlag::USER1);

	this->CreatePauseMenu();
	this->m_hubLayer = HUDLayer::create();
	this->m_hubLayer->SetPositionForHub(this->m_player->getPosition(), true);
	this->m_hubLayer->setCameraMask((unsigned int)CameraFlag::USER1);
	this->addChild(this->m_hubLayer);

	this->m_hubLayer->SetPauseMenu(this->m_popUpPauseGame);
	this->CreateJail();

	this->CreateWind();
	SoundMgr::getInstance()->ResetBooleanBgMusicMap();

	this->scheduleUpdate();
	return true;
}

void GameScene::update(float dt)
{
	this->ShowLocalLabel(this->m_player->getPosition().y);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->m_physicWorld->update(dt);

	GameScene::FixBugMoveButton();

	this->m_timeChangeWind += dt;
	if (abs(5.f - this->m_timeChangeWind) < TimeFixMovementBug)
	{
		if (this->m_turnChangeWindDirection == true)
		{
			this->m_turnChangeWindDirection = false;
			this->m_timeChangeWind = 0;
		}
		else
		{
			this->m_turnChangeWindDirection = true;
			this->m_timeChangeWind = 0;
		}
	}

	GameScene::CreateWindChallenge();

	//Slow down
	if (this->m_isJumpingAgain)
	{
		Director::getInstance()->getScheduler()->setTimeScale(0.3);
	}

	// Update With Can Jump
	if (this->m_contactListener->CanJump())
	{
		if (this->m_maxHeight < (this->m_player->getPosition().y - 448) / 145)
		{
			this->m_maxHeight = (this->m_player->getPosition().y - 448) / 145;
			this->m_hubLayer->SetScore(this->m_maxHeight);
		}
		if (this->m_player->GetB2Body()->GetLinearVelocity().Length() < MinVelocityDoAutoFixBug)
		{
			this->m_isJumpAgain = true;
		}
		this->m_flyingPartical->setVisible(false);
	}

	if (!this->m_contactListener->CanJump() && !this->m_isPull2 && this->m_player->getActionByTag(11) == nullptr)
	{
		this->m_flyingPartical->setVisible(true);
		this->m_flyingPartical->setPosition(this->m_player->getPosition());
	}

	if (this->m_contactListener->GetEnemyPointer() != nullptr && GameValue::getInstance()->getUsedSlingShot() == 2)
	{
		Enemy* tempEnemy = this->m_contactListener->GetEnemyPointer();

		tempEnemy->GetB2Body()->SetActive(false);
		tempEnemy->RunDeadAnimation();
		this->m_contactListener->SetEnemyPointer();
	}

	if (this->m_contactListener->CheckContactWithJail())
	{
		auto* scene = EndScene::create();
		Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
	}

	this->UpdateStatusPlayer();
	this->UpdateCheckPoint();
	this->UpdateDiamond();
	this->UpdateTreasureChest();
	this->UpdatePauseMenu();
	this->UpdateCamera();
	this->UpdateHub(dt);
	this->UpdatePlayer();
	this->UpdateGameValue();
	this->UpdateNotification(dt);
	this->UpdateSound();
	this->UpdateSlingshot();
	this->UpdateBossContactWithStone();
	this->UpdateOnElevatorButton();
	this->UpdateWind(dt);
	this->UpdateImageSlingShot();
	this->UpdateEffectLand(dt);


	if (this->m_player->getActionByTag(11) == nullptr || this->m_contactListener->GetOnSpineVariable() == false)
		GameScene::CreateBoucingMethod();

	// Update perfect
	if (!this->m_bIsFly)
	{
		this->m_perfectPath = true;
		this->m_numCoinInPath = -1;
		this->m_Indexpath = -1;
		this->m_numCointHas = -1;
	}
}

void GameScene::onEnter()
{
	Layer::onEnter();
	this->resumeSchedulerAndActions();
	if (!this->m_firstTimeShopping)
	{
		for (int i = 0; i < GameItems; i++)
		{
			if (GameValue::getInstance()->checkItems(i))
			{
				this->archivement->setStringForLabel("Got achievement: \nIntelligent Consumers");
				this->archivement->setPositionForAll(Vec2(Director::getInstance()->getVisibleSize().width / 2,
					Director::getInstance()->getVisibleSize().height / 2 - 250));
				this->archivement->setCameraMask((unsigned int)CameraFlag::USER1);
				this->archivement->RunAction();
				this->m_firstTimeShopping = true;
				break;
			}
		}
	}
}

void GameScene::onExit()
{
	this->pauseSchedulerAndActions();
	Layer::onExit();
}

Point GameScene::SetViewPointCenter(Vec2 position)
{
	Size winSize = Director::getInstance()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (this->m_map->GetSizeWidth()) - winSize.width / 2);
	y = MIN(y, (this->m_map->GetSizeHeight()) - winSize.height / 2);

	Point actualPosition = ccp(x, y);

	Point centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	Point viewPoint = ccpSub(centerOfView, actualPosition);

	return viewPoint;
}

#pragma region OnTouch

bool GameScene::OnTouchBegan(Touch* touch, Event* event)
{
	if (this->m_isPlayerDie)
		return true;
	else
		this->m_isTouchBegan = true;

	this->m_bSimulateTrajectory = false;
	this->unschedule(schedule_selector(GameScene::CheckMoveLoop));
	this->m_leftButtonPressed = false;
	this->m_rightButtonPressed = false;
	this->m_isTouch = true;
	this->m_notification->setVisible(false);

	if (this->m_isJumpAgain && !this->m_contactListener->CanJump()
		&& GameValue::getInstance()->getUsedSlingShot() == 1 && !Director::getInstance()->isPaused())
	{
		this->m_OnTouch = true;
		this->m_positionPlayer = this->m_player->getPosition();
		if (this->m_contactListener->GetOnMovingPlatform() || this->m_contactListener->GetOnElevator())
			this->m_bTouchWhenOnMovingPlatform = true;
		this->m_Vec2DragOffsetStartInView = touch->getLocationInView();

		this->TouchBeganFunction(touch);
		this->m_isJumpingAgain = true;
		this->m_isJumpAgain = false;
		return true;
	}
	else
		if (this->m_contactListener->CanJump() && !Director::getInstance()->isPaused())
		{
			this->TouchBeganFunction(touch);
			return true;
		}
	return false;
}

bool GameScene::OnTouchMoved(Touch* touch, Event* event)
{
	this->m_vec2FirstPositionPlayerAndSlingShot.x = this->m_slingShot->getPosition().x;
	this->m_vec2FirstPositionPlayerAndSlingShot.y = this->m_slingShot->getPosition().y + 90;

	this->m_Vec2DragOffsetEndInView = touch->getLocationInView();

	if (this->m_Vec2DragOffsetStartInView.distance(this->m_Vec2DragOffsetEndInView) > 64)
	{
		if (this->m_isCancle)
			this->CreateAnimationAppearanceSlingShot();
		this->m_isCancle = false;
		this->m_isPull = true;
		this->m_slingShot->setVisible(true);

		this->m_Vec2DragDistance = this->m_Vec2DragOffsetEndInView - this->m_Vec2DragOffsetStartInView;
		this->m_Vec2DragDistance = Vec2(-this->m_Vec2DragDistance.x, this->m_Vec2DragDistance.y);

		if (this->m_Vec2DragDistance.length() > MaxVectorDistance)
		{
			this->m_Vec2DragDistance.normalize();
			this->m_Vec2DragDistance *= MaxVectorDistance;
		}

		this->m_location->ShowCircle();
		this->m_location->SetScaleX(this->m_Vec2DragDistance.length() * 0.35f / MaxVectorDistance);
		this->m_location->setRotation(180 - this->m_Vec2DragDistance.getAngle() * 180 / M_PI);
	}
	else
	{
		this->m_location->ShowCancleCircle();
		this->m_isCancle = true;
		this->m_player->setPosition(Vec2(this->m_slingShot->getPosition().x, this->m_slingShot->getPosition().y + this->m_player->GetPlayerSize().height / 2));
		this->m_slingShot->setVisible(false);
		this->m_drawNode->clear();
		this->m_drawNodeSimulation->clear();
	}
	return true;
}

bool GameScene::OnTouchEnded(Touch* touch, Event* event)
{
	if (!m_isTouchBegan)
	{
		this->m_location->setVisible(false);
		this->m_drawNodeSimulation->clear();
		this->m_isTouch = false;
		this->m_slingShot->setVisible(false);
		this->m_drawNode->clear();

		m_isTouchBegan = false;
		return true;
	}
	m_isTouchBegan = false;

	this->m_bSimulateTrajectory = false;

	if (this->m_isJumpingAgain)
	{
		Director::getInstance()->getScheduler()->setTimeScale(1);
		this->m_isJumpingAgain = false;
	}
	if (!Director::getInstance()->isPaused())
	{
		this->m_bTouchWhenOnMovingPlatform = false;
		this->m_OnTouch = false;

		this->m_location->setVisible(false);
		this->m_drawNodeSimulation->clear();
		this->m_isTouch = false;
		this->m_slingShot->setVisible(false);
		this->m_drawNode->clear();

		if (this->m_isCancle == false)
		{
			this->m_player->setPosition(this->m_vec2FirstPositionPlayerAndSlingShot);

			if (this->m_isPull2) {
				if (MovePositionPlayerWithTranform)
					this->m_player->m_movePositionPlayer = false;
				else
					this->m_player->CreateBody(this->m_physicWorld->getWorld(), true);
			}

			this->m_isPull2 = false;

			this->m_NumJump++;
			if (this->m_contactListener->CanJump() || this->m_isPull == true)
			{
				this->m_Vec2DragOffsetEndInView = touch->getLocationInView();
				this->m_Vec2DragDistance = this->m_Vec2DragOffsetEndInView - this->m_Vec2DragOffsetStartInView;
				this->m_Vec2DragDistance = Vec2(-this->m_Vec2DragDistance.x, this->m_Vec2DragDistance.y);

				if (this->m_Vec2DragDistance.length() > MaxVectorDistance)
				{
					this->m_Vec2DragDistance.normalize();
					this->m_Vec2DragDistance *= MaxVectorDistance;
				}

				this->m_player->GetB2Body()->SetTransform(b2Vec2(this->m_vec2FirstPositionPlayerAndSlingShot.x / PTM_RATIO,
					this->m_vec2FirstPositionPlayerAndSlingShot.y / PTM_RATIO), 0);

				if (this->m_player->getPosition().y >= HeightStartIce && this->m_player->getPosition().y < HeightEndIce - 250)
					// Trong map bang
					if (GameValue::getInstance()->getUsedItem() == 1)
					{
						this->m_player->GetB2Body()->SetLinearVelocity(b2Vec2((this->m_Vec2DragDistance.x * PowerMultiplier) / PTM_RATIO,
							(this->m_Vec2DragDistance.y * PowerMultiplier) / PTM_RATIO));
					}
					else
					{
						this->m_player->GetB2Body()->SetLinearVelocity(b2Vec2((this->m_Vec2DragDistance.x * 0.8 * PowerMultiplier) / PTM_RATIO,
							(this->m_Vec2DragDistance.y * 0.8 * PowerMultiplier) / PTM_RATIO));
					}
				else
				{
					this->m_player->GetB2Body()->SetLinearVelocity(b2Vec2((this->m_Vec2DragDistance.x * PowerMultiplier) / PTM_RATIO,
						(this->m_Vec2DragDistance.y * PowerMultiplier) / PTM_RATIO));
				}

				this->m_speed = this->m_player->GetB2Body()->GetLinearVelocity().Length();

				int id = experimental::AudioEngine::play2d("audios/effects/king_jump.mp3");
				experimental::AudioEngine::setVolume(id, SoundMgr::getInstance()->GetVolumeEffect());

				this->m_player->RunFlyAnimation();
				m_bIsFly = true;

				if (this->m_player->GetB2Body()->GetLinearVelocity().x >= 0)
					this->m_player->setScaleX(1);
				else
					this->m_player->setScaleX(-1);
				this->m_isPull = false;

				this->m_contactListener->SetOnMovingPlatform(false);
				this->m_contactListener->SetOnElevator(false);
			}
		}
		else
		{
			if (this->m_isPull2)
			{
				if (MovePositionPlayerWithTranform)
					this->m_player->m_movePositionPlayer = false;
				else
					this->m_player->CreateBody(this->m_physicWorld->getWorld(), true);
			}
			this->m_isPull2 = false;
		}
		return true;
	}
	return false;
}

void GameScene::OnButtonShopTouch(Ref* sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		if (this->m_player->getPosition().x > this->m_checkPoint.x - 50 || this->m_player->getPosition().x > this->m_checkPoint.x + 50)
		{
			auto* scene = ShopingScene::create();
			Director::getInstance()->pushScene(TransitionFade::create(0.3, scene));
		}
		else
		{
			this->m_notification->setString("You don't near checkpoint");
			this->m_notification->setVisible(true);
			this->m_bUpdateNotification = true;
		}
	}
	break;
	default:
		break;
	}
}

void GameScene::OnButtonBackpackTouch(Ref* sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		auto scene = BackpackScene::createScene();
		Director::getInstance()->pushScene(TransitionFade::create(0.3, scene));
	}
	break;
	default:
		break;
	}
}

void GameScene::TouchBeganFunction(Touch* touch)
{
	this->m_OnTouch = true;
	this->m_positionPlayer = this->m_player->getPosition();
	if (this->m_contactListener->GetOnMovingPlatform() || this->m_contactListener->GetOnElevator())
		this->m_bTouchWhenOnMovingPlatform = true;
	this->m_Vec2DragOffsetStartInView = touch->getLocationInView();

	this->CreateAnimationAppearanceSlingShot();

	this->m_slingShot->setVisible(true);
	if (MovePositionPlayerWithTranform)
		this->m_player->m_movePositionPlayer = true;
	else
		this->m_player->DestroyBody(this->m_physicWorld->getWorld());
	this->m_isPull2 = true;

	// Hinh tron
	this->m_location->setPosition(touch->getLocation());
	this->m_location->setVisible(true);
}

#pragma endregion

Vec2 GameScene::CalculatePointOnTheCircle(Vec2 m_neoCircle, Vec2 m_point)
{
	Vec2 m_vector = m_point - m_neoCircle;
	float m_anpha = m_vector.getAngle();
	Vec2 m_result;
	m_result.x = m_neoCircle.x + 30 * cos(m_anpha);
	m_result.y = m_neoCircle.y + 30 * sin(m_anpha);
	return m_result;
}

#pragma region Move

void GameScene::CheckMoveLoop(float delta)
{
	if (this->m_leftButtonPressed == true)
		GameScene::MoveToLeft();
	else
		if (this->m_rightButtonPressed == true)
			GameScene::MoveToRight();
}

void GameScene::OnButtonLeftTouch(Ref* sender, Widget::TouchEventType type)
{
	if (!Director::getInstance()->isPaused())
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
		{
			if (abs(this->m_player->GetB2Body()->GetLinearVelocity().Length()) < MinVelocityDoAutoFixBug)
			{
				if (this->m_cheatCode.length() < strlen(CHEAT_CODE))
				{
					this->m_cheatCode += 'l';
				}
				else
				{
					this->m_cheatCode.erase(0, 1);
					this->m_cheatCode += 'l';
				}
				Sprite* m_tempSprite = (Sprite*)this->m_player->GetB2Body()->GetUserData();
				this->m_player->GetB2Body()->ApplyLinearImpulse(b2Vec2(-180, 0), this->m_player->GetB2Body()->GetWorldCenter(), true);
				m_tempSprite->setScaleX(-1);
				this->m_leftButtonPressed = true;
				this->schedule(schedule_selector(GameScene::CheckMoveLoop), 0.05);
			}
		}
		break;
		case Widget::TouchEventType::ENDED:
		{
			if (this->m_cheatCode.compare(CHEAT_CODE) == 0)
			{
				if (this->m_enableCheat == true)
				{
					this->m_enableCheat = false;
					this->m_notification->setString("Cheat deactivated");
					this->m_notification->setVisible(true);
				}
				else
				{
					this->m_enableCheat = true;
					this->m_notification->setString("Cheat activated");
					this->m_notification->setVisible(true);
				}
			}
			this->unschedule(schedule_selector(GameScene::CheckMoveLoop));
			this->m_leftButtonPressed = false;
		}
		break;
		default:
			break;
		}
	}
}

void GameScene::OnButtonRightTouch(Ref* sender, Widget::TouchEventType type)
{
	if (!Director::getInstance()->isPaused())
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
		{
			if (abs(this->m_player->GetB2Body()->GetLinearVelocity().Length()) < MinVelocityDoAutoFixBug)
			{
				if (this->m_cheatCode.length() < strlen(CHEAT_CODE))
				{
					this->m_cheatCode += 'r';
				}
				else
				{
					this->m_cheatCode.erase(0, 1);
					this->m_cheatCode += 'r';
				}
				Sprite* m_tempSprite = (Sprite*)this->m_player->GetB2Body()->GetUserData();
				this->m_player->GetB2Body()->ApplyLinearImpulse(b2Vec2(180, 0), this->m_player->GetB2Body()->GetWorldCenter(), true);
				m_tempSprite->setScaleX(1);
				this->m_rightButtonPressed = true;
				this->schedule(schedule_selector(GameScene::CheckMoveLoop), 0.05);
			}
		}
		break;
		case Widget::TouchEventType::ENDED:
		{
			if (this->m_cheatCode.compare(CHEAT_CODE) == 0)
			{
				if (this->m_enableCheat == true)
				{
					this->m_enableCheat = false;
					this->m_notification->setString("Cheat deactivated");
					this->m_notification->setVisible(true);
				}
				else
				{
					this->m_enableCheat = true;
					this->m_notification->setString("Cheat activated");
					this->m_notification->setVisible(true);
				}
			}
			this->unschedule(schedule_selector(GameScene::CheckMoveLoop));
			this->m_rightButtonPressed = false;
		}
		break;
		default:
			break;
		}
	}
}

void GameScene::MoveToLeft()
{
	if (abs(this->m_player->GetB2Body()->GetLinearVelocity().Length()) < MinVelocityDoAutoFixBug)
	{
		Sprite* m_tempSprite = (Sprite*)this->m_player->GetB2Body()->GetUserData();
		this->m_player->GetB2Body()->ApplyLinearImpulse(b2Vec2(-180, 0), this->m_player->GetB2Body()->GetWorldCenter(), true);
		m_tempSprite->setScaleX(-1);
	}
}

void GameScene::MoveToRight()
{
	if (abs(this->m_player->GetB2Body()->GetLinearVelocity().Length()) < MinVelocityDoAutoFixBug)
	{
		Sprite* m_tempSprite = (Sprite*)this->m_player->GetB2Body()->GetUserData();
		this->m_player->GetB2Body()->ApplyLinearImpulse(b2Vec2(180, 0), this->m_player->GetB2Body()->GetWorldCenter(), true);
		m_tempSprite->setScaleX(1);
	}
}

#pragma endregion

#pragma region Update

void GameScene::UpdateDiamond()
{
	bool eat_Diamond = false;
	if (this->m_preDiamond == nullptr && this->m_contactListener->GetDiamondContact() != nullptr)
		eat_Diamond = true;
	else if (this->m_contactListener->GetDiamondContact() != nullptr && this->m_preDiamond != this->m_contactListener->GetDiamondContact())
		eat_Diamond = true;

	if (eat_Diamond)
	{
		int id = experimental::AudioEngine::play2d("audios/effects/gold.mp3");
		experimental::AudioEngine::setVolume(id, SoundMgr::getInstance()->GetVolumeEffect());

		this->m_contactListener->GetDiamondContact()->SetActive(false);
		this->m_contactListener->GetDiamondContact()->setVisible(false);
		this->UpdatePerfect(this->m_contactListener->GetDiamondContact());

		auto sprite = Sprite::create("Images/plus_gold.png");
		sprite->setPosition(this->m_contactListener->GetDiamondContact()->getPosition().x,
			this->m_contactListener->GetDiamondContact()->getPosition().y + Director::getInstance()->getVisibleSize().height * 0.025);
		sprite->setScale(0.1);
		this->addChild(sprite, 3);

		auto moveBy = MoveBy::create(2, Vec2(0, 50));
		auto fadeo = FadeOut::create(2);
		auto spa = Spawn::createWithTwoActions(moveBy, fadeo);
		auto seq1 = Sequence::create(spa, RemoveSelf::create(), nullptr);
		sprite->runAction(seq1);
		this->m_preDiamond = this->m_contactListener->GetDiamondContact();
	}

}

void GameScene::UpdateTreasureChest()
{
	bool eat_TreasureChest = false;
	if (this->m_preTreasureChest == nullptr && this->m_contactListener->GetTreasureChestContact() != nullptr)
		eat_TreasureChest = true;
	else if (this->m_contactListener->GetTreasureChestContact() != nullptr && this->m_contactListener->GetTreasureChestContact() != this->m_preTreasureChest)
		eat_TreasureChest = true;

	if (eat_TreasureChest)
	{
		this->m_contactListener->GetTreasureChestContact()->RunAction();
		this->m_contactListener->GetTreasureChestContact()->SetActive(false);

		auto visibleSize = Director::getInstance()->getVisibleSize();

		ItemLoot* itemLoot = ItemLoot::createWithTypeItem(this->m_contactListener->GetTreasureChestContact()->GetItem());
		itemLoot->setPosition(this->m_contactListener->GetTreasureChestContact()->getPosition());
		this->addChild(itemLoot, 10);

		auto seq = Sequence::create(
			MoveTo::create(1.f, Vec2(CenterPointCamera(this->m_player->getPosition()).x,
				CenterPointCamera(this->m_player->getPosition()).y + visibleSize.height * 1.f / 4.f / ScaleFactor)),
			DelayTime::create(1.25),
			Spawn::createWithTwoActions(MoveTo::create(1.f, Vec2(CenterPointCamera(this->m_player->getPosition()).x + visibleSize.width / ScaleFactor * 0.32
				, CenterPointCamera(this->m_player->getPosition()).y + visibleSize.height * 0.40 / ScaleFactor)), ScaleTo::create(1.25f, 0.1f)),
			RemoveSelf::create(), nullptr);

		itemLoot->runAction(seq);
		GameValue::getInstance()->getSlingShot(this->m_contactListener->GetTreasureChestContact()->GetItem().ItemSlingShotToInt());
		this->m_preTreasureChest = this->m_contactListener->GetTreasureChestContact();

		this->ShowArchieveAnnoucement(this->m_contactListener->GetTreasureChestContact()->GetItem().GetTypeItem());
	}
}

void GameScene::UpdateCheckPoint()
{
	if (this->m_contactListener->GetCheckPointContact() != nullptr && this->m_contactListener->GetCheckPointContact()->isVisible() == true)
	{
		int id = experimental::AudioEngine::play2d("audios/effects/checkpoint.mp3");
		experimental::AudioEngine::setVolume(id, SoundMgr::getInstance()->GetVolumeEffect());
		this->m_contactListener->GetCheckPointContact()->SetActive(false);
		this->m_contactListener->GetCheckPointContact()->setVisible(false);
		this->m_checkPoint = this->m_contactListener->GetCheckPointContact()->getPosition();
		this->m_checkPointLocate->setPosition(Vec2(this->m_checkPoint.x,
			this->m_checkPoint.y - Director::getInstance()->getVisibleSize().height * 0.015));
	}
}

void GameScene::UpdatePauseMenu()
{
	if (this->m_popUpPauseGame->GetResume())
	{
		this->m_hubLayer->SetStatusPause(false);
		this->m_popUpPauseGame->SetResume(false);
	}
}

void GameScene::UpdatePlayer()
{
	if (this->m_bIsFly)
	{
		if (this->m_contactListener->CanJump())
		{
			m_bIsFly = false;
			this->m_player->RunIdleAnimation();
		}
	}
}

void GameScene::UpdateHub(float dt)
{
	this->m_hubLayer->AddTime(dt);
	this->m_hubLayer->SetDiamond(GameValue::getInstance()->cornScore);
}

void GameScene::UpdateCamera()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto position = GameScene::SetViewPointCenter(this->m_player->getPosition());

	this->m_defaultCamera = Camera::getDefaultCamera();
	this->m_defaultCamera->setScaleZ(ScaleFactor);

	auto positionCamera = this->GetPositionCamera();
	Vec2 cameraPos = m_defaultCamera->getPosition();
	cameraPos.smooth(positionCamera, 1.f, 2.5f);

	if (!this->m_isCancle)
	{
		if (this->m_isInBouncing)
		{
			//Bouncing
			if (position != CCPoint::ZERO)
			{
				m_defaultCamera->setPosition(cameraPos);
			}
		}
		else if (this->m_contactListener->GetOnMovingPlatform() || m_bOnElevatorStartBoss)
		{
			// Moving platform, elevator
			m_defaultCamera->setPosition(cameraPos);
		}
		else if (this->m_player->getActionByTag(11) != nullptr)
		{
			// Chet
			m_defaultCamera->setPosition(cameraPos);
		}
		else if (!this->m_isPull2)
		{
			// Flying
			m_defaultCamera->setPosition(cameraPos);
		}
	}
	if (m_bStartGame)
	{
		// Start game
		m_defaultCamera->setPosition(cameraPos);
		this->m_bStartGame = false;
	}
	else if (m_isPlayerDie)
	{
		m_defaultCamera->setPosition(cameraPos);
	}
}

void GameScene::UpdateStatusPlayer()
{
	if (!this->m_isPlayerDie)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		if (this->m_contactListener->GetOnSpineVariable())
		{
			this->UpdatePlayerDie();
			this->m_contactListener->SetOnSpineVariable(false);
		}
		if (this->m_contactListener->GetOnEnemy())
		{
			this->UpdatePlayerDie();
			this->m_contactListener->SetOnEnemy(false);
		}
		if (this->m_contactListener->GetOnBoss())
		{
			if (!this->m_contactListener->GetBossPointer()->isDead())
			{
				this->UpdatePlayerDie();
				this->m_contactListener->SetOnBoss(false);
			}
		}
		if (this->m_contactListener->GetOnPlayerConttactWithStone())
		{
			if (this->m_contactListener->GetStoneOnContactWithPlayer()->isVisible())
			{
				this->UpdatePlayerDie();
				this->m_contactListener->SetOnPlayerContactWithStone(false);

				Stone* stone = this->m_contactListener->GetStoneOnContactWithPlayer();
				stone->StopActionDrop();
				stone->SetParent(this, stone->getPosition());
				stone->CreateBrokenStone();
			}
		}
	}
}

void GameScene::UpdateGameValue()
{
	GameValue::getInstance()->SetPositionPlayer(this->m_player->getPosition());
	GameValue::getInstance()->SetCheckPoint(this->m_checkPoint);
	if (this->m_maxHeight > GameValue::getInstance()->GetHighScore())
		GameValue::getInstance()->SetHighScore(this->m_maxHeight);
}

void GameScene::UpdateNotification(float dt)
{
	if (this->m_bUpdateNotification) {
		if (this->m_fTimepNotification <= 0)
		{
			this->m_notification->setVisible(false);
			this->m_fTimepNotification = 3.f;
			m_bUpdateNotification = false;
		}
		else
			this->m_fTimepNotification -= dt;
	}

}

void GameScene::UpdateSound()
{
	float y = this->m_player->getPosition().y;
	if (y >= 0 && y < HeightStartWind - 50)
	{
		if (!SoundMgr::getInstance()->b_Map1)
		{
			SoundMgr::getInstance()->PlayBgSound(1);
		}
	}
	else if (y >= HeightStartWind && y < HeightStartIce - 50)
	{
		if (!SoundMgr::getInstance()->b_Map2)
		{
			SoundMgr::getInstance()->PlayBgSound(2);
		}
	}
	else if (y >= HeightStartIce && y < HeightStartCastle - 50)
	{
		if (!SoundMgr::getInstance()->b_Map3)
		{
			SoundMgr::getInstance()->PlayBgSound(3);
		}
	}
	else
	{
		if (!SoundMgr::getInstance()->b_Map4)
		{
			SoundMgr::getInstance()->PlayBgSound(4);
		}
	}
}

void GameScene::UpdateSlingshot()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (this->m_OnTouch)
	{
		if (!m_isTouchBegan)
		{
			this->m_location->setVisible(false);
			this->m_drawNodeSimulation->clear();
			this->m_isTouch = false;
			this->m_slingShot->setVisible(false);
			this->m_drawNode->clear();
		}
		else
		{
			if (this->m_bTouchWhenOnMovingPlatform)
			{
				this->m_positionSlingShot = Vec2(this->m_contactListener->GetPositionPlatform().x,
					this->m_contactListener->GetPositionPlatform().y + visibleSize.height * 0.1f / 10.f);
			}
			else
			{
				this->m_positionSlingShot = Vec2(this->m_positionPlayer.x, this->m_positionPlayer.y - this->m_player->GetPlayerSize().height / 2);
			}

			this->m_slingShot->setPosition(m_positionSlingShot);
			this->m_vec2FirstPositionPlayerAndSlingShot.x = this->m_slingShot->getPosition().x;
			this->m_vec2FirstPositionPlayerAndSlingShot.y = this->m_slingShot->getPosition().y + 90;
			this->m_player->setPosition(this->m_slingShot->getPosition().x, this->m_slingShot->getPosition().y + 90);

			if (this->m_Vec2DragOffsetStartInView.distance(this->m_Vec2DragOffsetEndInView) > 64)
			{
				if (this->m_NumJump > MaxJump && !this->m_enableCheat)
				{
					this->m_startPosition = b2Vec2(this->m_vec2FirstPositionPlayerAndSlingShot.x,
						this->m_vec2FirstPositionPlayerAndSlingShot.y);
					this->m_startVelocity = b2Vec2((this->m_Vec2DragDistance.x * CON_SO_KY_LA) / PTM_RATIO,
						(this->m_Vec2DragDistance.y * CON_SO_KY_LA) / PTM_RATIO);
					this->SimulateTrajectory(m_startPosition, m_startVelocity);
				}

				this->m_DesPositionOfPlayer = this->m_vec2FirstPositionPlayerAndSlingShot - this->m_Vec2DragDistance;
				if (this->m_vec2FirstPositionPlayerAndSlingShot.distance(m_DesPositionOfPlayer) < 30)
				{
					this->m_player->setPosition(m_DesPositionOfPlayer);
					this->m_drawNode->clear();
					this->m_drawNode->drawSegment(Point(this->m_vec2FirstPositionPlayerAndSlingShot.x + 15, this->m_vec2FirstPositionPlayerAndSlingShot.y),
						Point(m_DesPositionOfPlayer), 3.0, Color4F::RED);
					this->m_drawNode->drawSegment(Point(this->m_vec2FirstPositionPlayerAndSlingShot.x - 15, this->m_vec2FirstPositionPlayerAndSlingShot.y),
						Point(m_DesPositionOfPlayer), 3.0, Color4F::RED);
				}
				else
				{
					auto position1 = CalculatePointOnTheCircle(this->m_vec2FirstPositionPlayerAndSlingShot, m_DesPositionOfPlayer);
					this->m_player->setPosition(position1);
					this->m_drawNode->clear();
					this->m_drawNode->drawSegment(Point(this->m_vec2FirstPositionPlayerAndSlingShot.x + 15, this->m_vec2FirstPositionPlayerAndSlingShot.y),
						Point(CalculatePointOnTheCircle(this->m_vec2FirstPositionPlayerAndSlingShot, m_DesPositionOfPlayer)), 3.0, Color4F::RED);
					this->m_drawNode->drawSegment(Point(this->m_vec2FirstPositionPlayerAndSlingShot.x - 15, this->m_vec2FirstPositionPlayerAndSlingShot.y),
						Point(CalculatePointOnTheCircle(this->m_vec2FirstPositionPlayerAndSlingShot, m_DesPositionOfPlayer)), 3.0, Color4F::RED);
				}

				if (this->m_DesPositionOfPlayer.x > this->m_vec2FirstPositionPlayerAndSlingShot.x)
				{
					this->m_slingShot->setScaleX(-1);
					this->m_player->setScaleX(-1);
				}
				else
				{
					this->m_slingShot->setScaleX(1);
					this->m_player->setScaleX(1);
				}

				if (this->m_NumJump <= MaxJump || this->m_enableCheat)
				{
					this->SimulateTrajectory();
				}
			}
			else
			{
				this->m_location->ShowCancleCircle();
				this->m_isCancle = true;
				this->m_player->setPosition(Vec2(this->m_slingShot->getPosition().x, this->m_slingShot->getPosition().y + this->m_player->GetPlayerSize().height / 2));
				this->m_slingShot->setVisible(false);
				this->m_drawNode->clear();
				this->m_drawNodeSimulation->clear();
			}
		}
	}
}

void GameScene::UpdateBossContactWithStone()
{
	if (this->m_contactListener->GetOnBossContactWithStone() && this->m_BossMatMau)
	{
		Boss* boss = this->m_contactListener->GetBossOnContactWithStone();
		boss->RunHurtAniamtion(false);
		this->m_contactListener->SetBossContactWithStone(false);
		boss->SetPercent(boss->GetPercentHp() - 1 / 8.0f);

		Stone* stone = this->m_contactListener->GetStoneOnContactWithBoss();
		stone->StopActionDrop();
		stone->SetParent(this, stone->getPosition());
		stone->CreateBrokenStone();
	}
	if (this->m_BossMatMau) {
		for (int i = 0; i < this->m_vectorBoss.size(); i++)
		{
			auto boss = this->m_vectorBoss.at(i);
			if (boss->GetPercentHp() <= 0)
			{
				for (int j = 0; j < m_vectorStone.size(); j++)
				{
					auto stone = m_vectorStone.at(j);
					stone->RemoveStone();
				}
				if (!boss->isDead())
					this->m_vectorElevator.at(1)->RunActionMoveToEnd1();

				boss->RunDeadAnimation();
				this->unschedule(schedule_selector(GameScene::ScheduleStoneFall));
				break;
			}
		}
	}
}

void GameScene::UpdateOnElevatorButton()
{
	if (this->m_contactListener->GetOnElevatorButton())
	{
		Elevator* elevator = this->m_contactListener->GetPtrElevatorButton();
		if (elevator->m_bool == false)
		{
			this->unschedule(schedule_selector(GameScene::ScheduleStoneFall));
			for (int i = 0; i < this->m_vectorStone.size(); i++)
			{
				auto stone = this->m_vectorStone.at(i);
				stone->StopActionDrop();
				stone->SetParent(this, stone->getPosition());
				stone->CreateBrokenStone();
			}
			elevator->m_bool = true;
			this->m_bOnElevatorStartBoss = true;
			elevator->RunActionMoveTo();
			this->runAction(Sequence::create(DelayTime::create(elevator->GetTimeRun()),
				CallFunc::create(CC_CALLBACK_0(GameScene::SetScheduleStoneToTrue, this)), nullptr));
		}

		this->m_checkPoint = Vec2(elevator->m_movePosition[0].x,
			elevator->m_movePosition[0].y + Director::getInstance()->getVisibleSize().height * 0.05);

		this->m_checkPointLocate->setPosition(Vec2(this->m_checkPoint.x,
			this->m_checkPoint.y - Director::getInstance()->getVisibleSize().height * 0.015));

		this->m_contactListener->SetOnElevatorButton(false);
	}
}

void GameScene::UpdatePlayerDie()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	int id = experimental::AudioEngine::play2d("audios/effects/Player_death.mp3");
	experimental::AudioEngine::setVolume(id, SoundMgr::getInstance()->GetVolumeEffect());

	this->m_isPlayerDie = true;
	m_isTouchBegan = false;

	//if (MovePositionPlayerWithTranform)
	//	this->m_player->m_movePositionPlayer = true;
	//else
	//	this->m_player->DestroyBody(this->m_physicWorld->getWorld());

	this->m_player->DestroyBody(this->m_physicWorld->getWorld());

	this->m_player->setVisible(false);

	auto spriteAnimation = Sprite::createWithSpriteFrameName("Red-Bird-Die-Effects-Flappy-0.png");
	spriteAnimation->setPosition(this->m_player->getPosition());
	spriteAnimation->setScale(0.5f);
	this->addChild(spriteAnimation, 10);

	const int iNumberSprite = 4;
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(iNumberSprite);
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Red-Bird-Die-Effects-Flappy-0.png"));
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Red-Bird-Die-Effects-Flappy-1.png"));
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Red-Bird-Die-Effects-Flappy-2.png"));
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Red-Bird-Die-Effects-Flappy-3.png"));
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	auto animate = Animate::create(animation);
	spriteAnimation->runAction(Sequence::create(animate, RemoveSelf::create(), nullptr));

	auto seq = Sequence::create(
		CallFunc::create(CC_CALLBACK_0(GameScene::BeginDie, this)),
		DelayTime::create(0.5f),
		MoveTo::create(1.0f, Vec2(this->m_checkPoint.x, this->m_checkPoint.y + visibleSize.height * 0.05)),
		CallFunc::create(CC_CALLBACK_0(GameScene::EndDie, this)), nullptr);
	seq->setTag(11);
	this->m_player->runAction(seq);
}

void GameScene::UpdateWind(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (m_fTimeMoveWind <= 0)
	{
		float positionY = rand_float(HeightStartWind, HeightEndWind);
		float positionY2 = rand_float(positionY - visibleSize.height * 0.1, positionY + visibleSize.height * 0.1);
		float positionX, positionX1;

		auto wind = this->m_vectorWind.getObject();

		if (this->m_turnChangeWindDirection)
		{
			positionX = 0;
			positionX1 = this->m_map->GetSizeWidth() + visibleSize.width;
			wind->m_directorIsLeftToRight = true;
		}
		else
		{
			positionX = this->m_map->GetSizeWidth();
			positionX1 = -visibleSize.width;
			wind->m_directorIsLeftToRight = false;
		}
		wind->setPosition(positionX, positionY);
		wind->setVisible(true);

		auto moveTo = MoveTo::create(2.5f, Vec2(positionX1, positionY2));
		wind->runAction(Sequence::create(moveTo, nullptr));

		m_fTimeMoveWind = DelayTimeUpdateWind;
	}
	else
		m_fTimeMoveWind -= dt;

	for (int i = 0; i < this->m_vectorWind.size(); i++)
	{
		auto wind = this->m_vectorWind.at(i);
		if (wind->m_directorIsLeftToRight != this->m_turnChangeWindDirection)
		{
			wind->setVisible(false);
		}
	}
}

void GameScene::EndWin()
{
	for (int i = 0; i < this->m_vectorWind.size(); i++)
	{
		auto wind = this->m_vectorWind.at(i);
		wind->setVisible(false);
	}
}

void GameScene::UpdateImageSlingShot()
{
	int useSlingshot = GameValue::getInstance()->getUsedSlingShot();
	this->m_slingShot->SetImageSlingShot(useSlingshot);
}

void GameScene::UpdatePerfect(Gold* gold)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (gold->m_numCoinInPath <= 0)
	{
		this->m_perfectPath = false;
	}
	else if (this->m_bIsFly)
	{
		if (this->m_perfectPath)
		{
			if (m_numCoinInPath == -1)
			{
				this->m_perfectPath = true;
				// Coin bat dau
				this->m_numCoinInPath = gold->m_numCoinInPath;
				this->m_Indexpath = gold->m_indexPath;
				this->m_numCointHas = 1;
			}
			else
			{
				// Cac coint tiep theo
				if (m_Indexpath == gold->m_indexPath
					&& this->m_numCoinInPath == gold->m_numCoinInPath)
				{
					this->m_perfectPath = true;
					this->m_numCointHas += 1;
				}
				else
				{
					this->m_perfectPath = false;
				}
			}
			if (this->m_perfectPath && this->m_numCointHas == gold->m_numCoinInPath)
			{
				auto _label = Sprite::createWithSpriteFrameName("perfect.png");
				_label->setScale(0.45);

				_label->setPosition(Vec2(CenterPointCamera(this->m_player->getPosition()).x,
					CenterPointCamera(this->m_player->getPosition()).y
					+ Director::getInstance()->getVisibleSize().height * 1.f / 4.f / ScaleFactor));

				this->addChild(_label, 3);

				auto fadeo = FadeOut::create(2);
				auto seq1 = Sequence::create(fadeo, RemoveSelf::create(), nullptr);
				_label->runAction(seq1);

				GameValue::getInstance()->cornScore += this->m_numCointHas / 2;
				this->m_perfectPath = true;

				int id = experimental::AudioEngine::play2d("audios/effects/perfect.mp3");
				experimental::AudioEngine::setVolume(id, SoundMgr::getInstance()->GetVolumeEffect());
			}
		}
		else
		{
			this->m_perfectPath = false;
		}
	}
	else
	{
		this->m_perfectPath = true;
		this->m_numCoinInPath = -1;
		this->m_Indexpath = -1;
		this->m_numCointHas = -1;
	}
	if (this->m_perfectPath == false)
	{
		this->m_numCoinInPath = -1;
		this->m_Indexpath = -1;
		this->m_numCointHas = -1;
	}
}

void GameScene::UpdateEffectLand(float dt)
{
	//if (this->m_contactListener->GetIsPlayerEffectLand())
	//{
	//	if (this->m_fPreTimeEffectLand == -1)
	//	{
	//		int id = experimental::AudioEngine::play2d("audios/effects/king_land.mp3");
	//		experimental::AudioEngine::setVolume(id, SoundMgr::getInstance()->GetVolumeEffect());
	//	}
	//	else if (GameValue::getInstance()->m_fTime - this->m_fPreTimeEffectLand >= TimeEffectLand)
	//	{
	//		int id = experimental::AudioEngine::play2d("audios/effects/king_land.mp3");
	//		experimental::AudioEngine::setVolume(id, SoundMgr::getInstance()->GetVolumeEffect());
	//	}
	//	this->m_fPreTimeEffectLand = GameValue::getInstance()->m_fTime;
	//	this->m_contactListener->SetIsPlayerEffectLand(false);
	//}
	if (m_preIsFlying == true && m_bIsFly == false)
	{
		int id = experimental::AudioEngine::play2d("audios/effects/king_land.mp3");
		experimental::AudioEngine::setVolume(id, SoundMgr::getInstance()->GetVolumeEffect());
	}
	m_preIsFlying = m_bIsFly;
}

#pragma endregion

#pragma region Simulate

void GameScene::SimulateTrajectory()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	this->m_SimalationPlayerBody->SetTransform(b2Vec2(this->m_vec2FirstPositionPlayerAndSlingShot.x / PTM_RATIO,
		this->m_vec2FirstPositionPlayerAndSlingShot.y / PTM_RATIO), 0);

	if (this->m_player->getPosition().y >= HeightStartIce && this->m_player->getPosition().y < HeightEndIce - 250)
		if (GameValue::getInstance()->getUsedItem() == 1)
		{
			this->m_SimalationPlayerBody->SetLinearVelocity(b2Vec2((this->m_Vec2DragDistance.x * PowerMultiplier) / PTM_RATIO,
				(this->m_Vec2DragDistance.y * PowerMultiplier) / PTM_RATIO));
		}
		else
		{
			this->m_SimalationPlayerBody->SetLinearVelocity(b2Vec2((this->m_Vec2DragDistance.x * 0.8 * PowerMultiplier) / PTM_RATIO,
				(this->m_Vec2DragDistance.y * 0.8 * PowerMultiplier) / PTM_RATIO));
		}
	else
	{
		this->m_SimalationPlayerBody->SetLinearVelocity(b2Vec2((this->m_Vec2DragDistance.x * PowerMultiplier) / PTM_RATIO,
			(this->m_Vec2DragDistance.y * PowerMultiplier) / PTM_RATIO));
	}

	m_drawNodeSimulation->clear();
	m_points.clear();
	for (int i = 0; i < 60; i++)
	{
		this->m_SimulationWorld->Step(1 / 60.0f, 8, 1);

		if (this->m_contactListenerSimualate->CanJump())
		{
			this->m_contactListenerSimualate->ReFalseIsBoucing();
			this->m_isInBouncingSimulate = false;
		}
		if (this->m_contactListenerSimualate->CheckBoucing() == true && !this->m_isInBouncingSimulate)
		{
			this->m_isInBouncingSimulate = true;

			this->m_SimalationPlayerBody->SetLinearVelocity(b2Vec2(-this->m_contactListenerSimualate->GetLinearVelocity().x * 1.2,
				this->m_contactListenerSimualate->GetLinearVelocity().y * 1.2));
			this->m_contactListenerSimualate->ReFalseIsBoucing();
		}

		if (i % 3 == 0) {
			m_points.emplace_back(Vec2{ this->m_SimalationPlayerBody->GetPosition().x * PTM_RATIO,
				this->m_SimalationPlayerBody->GetPosition().y * PTM_RATIO });
		}
	}
	m_drawNodeSimulation->clear();

	auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	m_drawNodeSimulation->drawPoints(m_points.data(), m_points.size(), 5.f * frameSize.width / 720.0f, Color4F::RED);
}

void GameScene::SimulateTrajectory(b2Vec2& startingPosition, b2Vec2& startingVelocity)
{
	if (startingVelocity.x == 0 && startingVelocity.y == 0)
		return;
	m_drawNodeSimulation->clear();
	m_points.clear();
	for (int i = 0; i < MAX_DOT; i++)
	{
		b2Vec2 trajectoryPosition = this->GetTrajectoryPoint(startingPosition, startingVelocity, i);
		m_points.emplace_back(Vec2(trajectoryPosition.x, trajectoryPosition.y));
	}
	m_drawNodeSimulation->clear();
	auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	m_drawNodeSimulation->drawPoints(m_points.data(), m_points.size(), 4.f * frameSize.width / 720.0f, Color4F::RED);
}

b2Vec2 GameScene::GetTrajectoryPoint(b2Vec2& startingPosition, b2Vec2& startingVelocity, float n)
{
	float t = 1 / FPS_Trajectory;
	b2Vec2 stepVelocity = t * startingVelocity;
	b2Vec2 stepGravity = t * t * this->m_physicWorld->getWorld()->GetGravity();

	return startingPosition + n * stepVelocity + 0.5f * (n * n + n) * stepGravity;
}

#pragma endregion

#pragma region Create

void GameScene::CreateBoucingMethod()
{
	if (this->m_contactListener->CanJump())
	{
		this->m_contactListener->ReFalseIsBoucing();
		this->m_isInBouncing = false;
	}
	if (this->m_contactListener->CheckBoucing() == true && !this->m_isInBouncing)
	{
		this->m_isInBouncing = true;

		this->m_player->GetB2Body()->SetLinearVelocity(b2Vec2(-this->m_contactListener->GetLinearVelocity().x * 1.2,
			this->m_contactListener->GetLinearVelocity().y * 1.2));
		this->m_contactListener->ReFalseIsBoucing();

		int id = experimental::AudioEngine::play2d("audios/effects/king_bump.mp3");
		experimental::AudioEngine::setVolume(id, SoundMgr::getInstance()->GetVolumeEffect());
	}
}

void GameScene::CreateWind()
{
	for (int i = 0; i < NumOfWind; i++) {
		auto wind = Wind::create();
		this->addChild(wind, 20);
		//wind->setPosition(this->m_player->getPosition());
		wind->setVisible(false);
		this->m_vectorWind.addObject(wind);
	}
}

void GameScene::CreateBackground()
{	
	auto height = 0;

	auto spriteBg1 = Sprite::create("Background/BackGround11.png");
	this->addChild(spriteBg1, -10);
	spriteBg1->setAnchorPoint(Vec2::ZERO);
	spriteBg1->setPosition(0, 0);

	auto spriteBg2 = Sprite::create("Background/BackGround12.png");
	this->addChild(spriteBg2, -10);
	spriteBg2->setAnchorPoint(Vec2::ZERO);
	spriteBg2->setPosition(0, spriteBg1->getBoundingBox().size.height);

	auto spriteBg3 = Sprite::create("Background/BackGround13.png");
	this->addChild(spriteBg3, -10);
	spriteBg3->setAnchorPoint(Vec2::ZERO);
	spriteBg3->setPosition(0, spriteBg1->getBoundingBox().size.height + spriteBg2->getBoundingBox().size.height);

	auto spriteBg4 = Sprite::create("Background/BackGround14.png");
	this->addChild(spriteBg4, -10);
	spriteBg4->setAnchorPoint(Vec2::ZERO);
	spriteBg4->setPosition(0, spriteBg1->getBoundingBox().size.height + spriteBg2->getBoundingBox().size.height + spriteBg3->getBoundingBox().size.height);

	auto spriteBg5 = Sprite::create("Background/BackGround15.png");
	this->addChild(spriteBg5, -10);
	spriteBg5->setAnchorPoint(Vec2::ZERO);
	spriteBg5->setPosition(0, spriteBg1->getBoundingBox().size.height 
		+ spriteBg2->getBoundingBox().size.height 
		+ spriteBg3->getBoundingBox().size.height 
		+ spriteBg4->getBoundingBox().size.height);

	auto spriteBg6 = Sprite::create("Background/BackGround16.png");
	this->addChild(spriteBg6, -10);
	spriteBg6->setAnchorPoint(Vec2::ZERO);
	spriteBg6->setPosition(0, spriteBg1->getBoundingBox().size.height
		+ spriteBg2->getBoundingBox().size.height
		+ spriteBg3->getBoundingBox().size.height
		+ spriteBg4->getBoundingBox().size.height
		+ spriteBg5->getBoundingBox().size.height);
}

void GameScene::CreateMovementButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Create movement button
	this->m_Left = Button::create("Images/Left11.png", "Images/Left1.png");
	this->m_Left->setOpacity(220);
	this->m_Right = Button::create("Images/Right11.png", "Images/Right1.png");
	this->m_Right->setOpacity(220);
	this->m_Left->setScale(0.3);
	this->m_Right->setScale(0.3);
	this->m_Left->setCameraMask((unsigned int)CameraFlag::USER1);
	this->m_Right->setCameraMask((unsigned int)CameraFlag::USER1);
	this->m_Left->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.1));
	this->m_Right->setPosition(Vec2(visibleSize.width * 0.9, visibleSize.height * 0.1));
	addChild(this->m_Left);
	addChild(this->m_Right);

	//Button callback
	this->m_Left->addTouchEventListener(CC_CALLBACK_2(GameScene::OnButtonLeftTouch, this));
	this->m_Right->addTouchEventListener(CC_CALLBACK_2(GameScene::OnButtonRightTouch, this));
}

void GameScene::CreateCamera()
{
	//Create camera
	m_camera = Camera::create();
	m_camera->setCameraFlag(CameraFlag::USER1);
	addChild(m_camera, 4);
}

void GameScene::CreatePlayer(bool boolean)
{
	//Add object
	this->m_slingShot = SlingShot::create();
	this->addChild(this->m_slingShot);

	this->m_player = Player::create();
	if (!boolean)
	{
		this->m_player->setPosition(this->m_map->GetSpawnPoint());
		this->m_checkPoint = this->m_player->getPosition();
	}
	else
	{
		this->m_checkPoint = GameValue::getInstance()->GetCheckPoint();
		this->m_player->setPosition(GameValue::getInstance()->GetPositionPlayer());
	}
	this->m_player->CreateBody(this->m_physicWorld->getWorld(), true);
	this->addChild(this->m_player, 1);


}

void GameScene::CreateCheckPoint()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	cocos2d::ValueVector CheckPointObjects = this->m_map->GetObjectGroup("Flags");
	for (cocos2d::Value CheckPoinValue : CheckPointObjects)
	{
		float x = CheckPoinValue.asValueMap()["x"].asFloat();
		float y = CheckPoinValue.asValueMap()["y"].asFloat();

		CheckPoint* checkPoint = CheckPoint::create();
		checkPoint->setPosition(x, y + visibleSize.height * 0.012);
		checkPoint->CreateBody(this->m_physicWorld->getWorld());
		this->addChild(checkPoint, 0);
		this->m_VectorCheckPoint.pushBack(checkPoint);
	}
}

void GameScene::CreateDiamond()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	cocos2d::ValueVector DiamondObjects = this->m_map->GetObjectGroup("Diamond");
	for (cocos2d::Value DiamondValue : DiamondObjects)
	{
		float x = DiamondValue.asValueMap()["x"].asFloat();
		float y = DiamondValue.asValueMap()["y"].asFloat();

		Gold* gold = Gold::create();
		gold->setPosition(x, y + visibleSize.height * 0.0065);
		gold->CreateBody(this->m_physicWorld->getWorld());
		this->addChild(gold, 0);

		gold->m_indexPath = DiamondValue.asValueMap()["indexPath"].asInt();
		gold->m_numCoinInPath = DiamondValue.asValueMap()["numCoin"].asInt();

		this->m_VectorDiamond.pushBack(gold);
	}
}

void GameScene::CreateTreasureChest()
{
	cocos2d::ValueVector TreasureChestObjects = this->m_map->GetObjectGroup("TreasureChest");
	for (cocos2d::Value TreasureChestValue : TreasureChestObjects)
	{
		float x = TreasureChestValue.asValueMap()["x"].asFloat();
		float y = TreasureChestValue.asValueMap()["y"].asFloat();

		TreasureChest* treasureChest = TreasureChest::create();
		treasureChest->setPosition(x, y);
		treasureChest->CreateBody(this->m_physicWorld->getWorld());
		treasureChest->SetTypeItem(TreasureChestValue.asValueMap()["TypeItem"].asString());
		treasureChest->LoadItem();
		this->addChild(treasureChest, 0);
		this->m_VectorTreasureChest.pushBack(treasureChest);
	}
}

void GameScene::CreateEnemy()
{
	for (int i = 1; i <= 5; i++)
	{
		std::string nameObejct = "Enemy" + std::to_string(i);
		for (cocos2d::Value Enemy1Value : this->m_map->GetObjectGroup(nameObejct))
		{
			float x = Enemy1Value.asValueMap()["x"].asFloat();
			float y = Enemy1Value.asValueMap()["y"].asFloat();

			Enemy* enemy = Enemy::createWithType((TypeEnemy)i);
			enemy->setPosition(x, y);
			enemy->CreateBody(this->m_physicWorld->getWorld());

			auto numPosition = Enemy1Value.asValueMap()["numPosition"].asInt();
			for (int i = 1; i <= numPosition; i++)
			{
				float xP = Enemy1Value.asValueMap()["Position" + std::to_string(i) + "X"].asFloat();
				float yP = this->m_map->GetSizeHeight() - Enemy1Value.asValueMap()["Position" + std::to_string(i) + "Y"].asFloat();
				enemy->m_movePosition.push_back(Vec2(xP, yP));
			}
			enemy->m_timeRun = Enemy1Value.asValueMap()["timeFly"].asFloat();
			enemy->m_timeDelay = Enemy1Value.asValueMap()["timeDelay"].asFloat();
			if (numPosition > 1)
				enemy->RunActionMoveTo(rand_int(0, 1));
			this->addChild(enemy, 0);
			this->m_vectorEnemy.pushBack(enemy);
		}
	}
}

void GameScene::CreateBoss()
{
	for (cocos2d::Value Enemy1Value : this->m_map->GetObjectGroup("Boss"))
	{
		float x = Enemy1Value.asValueMap()["x"].asFloat();
		float y = Enemy1Value.asValueMap()["y"].asFloat();

		Boss* boss = Boss::create();
		boss->setPosition(x, y);
		boss->CreateBody(this->m_physicWorld->getWorld());
		this->addChild(boss, 0);

		auto numPosition = Enemy1Value.asValueMap()["numPosition"].asInt();
		for (int i = 1; i <= numPosition; i++)
		{
			float xP = Enemy1Value.asValueMap()["Position" + std::to_string(i) + "X"].asFloat();
			float yP = this->m_map->GetSizeHeight() - Enemy1Value.asValueMap()["Position" + std::to_string(i) + "Y"].asFloat();
			boss->m_movePosition.push_back(Vec2(xP, yP));
		}
		boss->m_timeRun = Enemy1Value.asValueMap()["timeFly"].asFloat();
		boss->m_timeDelay = Enemy1Value.asValueMap()["timeDelay"].asFloat();
		if (numPosition > 0)
			boss->RunActionMoveTo();
		this->m_vectorBoss.pushBack(boss);
	}
}

void GameScene::CreateSimulationWorld(b2Vec2 gravity)
{
	// Tao the gioi mo phong
	this->m_SimulationWorld = new b2World(gravity);
	this->m_SimulationWorld->SetContactListener(this->m_contactListenerSimualate);
	this->m_drawNodeSimulation = DrawNode::create();
	this->addChild(this->m_drawNodeSimulation, 100);

	this->CreateCollision(this->m_SimulationWorld);

	// Player
	b2PolygonShape bodyShape;
	bodyShape.SetAsBox(this->m_player->GetSizeBodyShape().x, this->m_player->GetSizeBodyShape().y);

	b2FixtureDef fixtureDef;
	fixtureDef.density = 10;
	fixtureDef.friction = 0.3;
	fixtureDef.restitution = 0;
	fixtureDef.shape = &bodyShape;
	fixtureDef.filter.categoryBits = 0x99;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(this->m_player->getPosition().x / PTM_RATIO, this->m_player->getPosition().y / PTM_RATIO);

	m_SimalationPlayerBody = this->m_SimulationWorld->CreateBody(&bodyDef);

	m_SimalationPlayerBody->CreateFixture(&fixtureDef);
	m_SimalationPlayerBody->SetFixedRotation(true);
	m_SimalationPlayerBody->SetGravityScale(10);

	// Chan cua character
	fixtureDef.isSensor = true;
	bodyShape.SetAsBox(this->m_player->GetSizeBodyShape().x * 0.9, 0.2, b2Vec2(0, -(this->m_player->GetSizeBodyShape().y + 0.01)), 0);
	b2Fixture* footSensorFixture = m_SimalationPlayerBody->CreateFixture(&fixtureDef);
	footSensorFixture->SetUserData(new TypeObject(FootSensorSimulateBody, this));

	// Tay trai
	bodyShape.SetAsBox(0.05, 0.46, b2Vec2(this->m_player->GetSizeBodyShape().x + 0.04, 0), 0);
	b2Fixture* leftHandSensorFixture = m_SimalationPlayerBody->CreateFixture(&fixtureDef);
	leftHandSensorFixture->SetUserData(new TypeObject(HandSensorSimulateBody, this));

	// Tay phai
	bodyShape.SetAsBox(0.05, 0.46, b2Vec2(-(this->m_player->GetSizeBodyShape().x + 0.04), 0), 0);
	b2Fixture* rightHandSensorFixture = m_SimalationPlayerBody->CreateFixture(&fixtureDef);
	rightHandSensorFixture->SetUserData(new TypeObject(HandSensorSimulateBody, this));

	// Debug
	if (isEnableDebugSimulation)
		this->addChild(B2DebugDrawLayer::create(this->m_SimulationWorld, 32.0f), INT_MAX);
}

void GameScene::CreateCheckPointLocate()
{
	this->m_checkPointLocate = Sprite::createWithSpriteFrameName("CheckPointLocate.png");
	this->m_checkPointLocate->setScale(0.07);
	this->m_checkPointLocate->setPosition(Vec2(this->m_checkPoint.x,
		this->m_checkPoint.y + Director::getInstance()->getVisibleSize().height * 0.001));
	this->addChild(this->m_checkPointLocate, 0);
}

void GameScene::CreateNotification()
{
	this->m_notification = Label::createWithSystemFont("TEMP", "Arial", 32);
	this->m_notification->setPosition(380, 60);
	this->m_notification->setColor(Color3B(255, 0, 0));
	this->m_notification->setCameraMask((unsigned int)CameraFlag::USER1);
	this->m_notification->setVisible(false);
	addChild(this->m_notification);
}

void GameScene::CreateCollision(b2World* world)
{
	this->m_map->CreateCollisionMap(world, Friction_Collision, Restitution_Collision, Density_Collision, 0x01, 0xffff, "Collision");
	this->m_map->CreateCollisionMap(world, Friction_Collision, Restitution_Collision, Density_Collision, 0x03, 0xffff, "Spine");
	this->m_map->CreateCollisionMap(world, Friction_Ice, Restitution_Ice, Density_Ice, 0x04, 0xffff, "Ice");
	this->m_map->CreateCollisionMap(world, Friction_Collision, Restitution_Collision, Density_Collision, 0x05, 0xffff, "BoucingLocation");
}

void GameScene::CreateWindChallenge()
{
	if (this->m_player->getPosition().y > HeightStartWind - 200 && this->m_player->getPosition().y < HeightEndWind + 50)
		this->m_hubLayer->ShowWindDirectionSprite();
	else
		this->m_hubLayer->HideWindDirectionSprite();

	this->m_hubLayer->ChangeWindDirection(this->m_turnChangeWindDirection);

	if (this->m_player->getPosition().y > HeightStartWind &&
		this->m_player->getPosition().y < HeightEndWind + 50)
	{
		if (!this->m_contactListener->CanJump())
		{
			if (this->m_turnChangeWindDirection == true)
			{
				if (GameValue::getInstance()->getUsedItem() == 3)
					this->m_player->GetB2Body()->ApplyForceToCenter(b2Vec2(150 * 0.5, 0), true);
				else
					this->m_player->GetB2Body()->ApplyForceToCenter(b2Vec2(150, 0), true);
			}
			else
			{
				if (GameValue::getInstance()->getUsedItem() == 3)
					this->m_player->GetB2Body()->ApplyForceToCenter(b2Vec2(-150 * 0.5, 0), true);
				else
					this->m_player->GetB2Body()->ApplyForceToCenter(b2Vec2(-150, 0), true);
			}
		}
	}
}

void GameScene::CreateShopButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	this->m_Shop = Button::create("Images/shop.png", "Images/shop1.png");
	this->m_Shop->setScale(0.3);
	this->m_Shop->setCameraMask((unsigned int)CameraFlag::USER1);
	this->m_Shop->setPosition(Vec2(visibleSize.width * 0.93, visibleSize.height * 0.93));
	addChild(this->m_Shop);

	this->m_Shop->addTouchEventListener(CC_CALLBACK_2(GameScene::OnButtonShopTouch, this));
}

void GameScene::CreateBackpackButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	this->m_Backpack = Button::create("Images/backpack.png", "Images/backpack1.png");
	this->m_Backpack->setScale(0.3);
	this->m_Backpack->setCameraMask((unsigned int)CameraFlag::USER1);
	this->m_Backpack->setPosition(Vec2(visibleSize.width * 0.82, visibleSize.height * 0.93));
	addChild(this->m_Backpack);

	this->m_Backpack->addTouchEventListener(CC_CALLBACK_2(GameScene::OnButtonBackpackTouch, this));
}

void GameScene::CreatePauseMenu()
{
	this->m_popUpPauseGame = PopUpPause::create();
	this->m_popUpPauseGame->setTitlePopup("Pause");
	this->m_popUpPauseGame->retain();
	this->m_popUpPauseGame->setCameraMask((unsigned int)CameraFlag::USER1);
	this->addChild(this->m_popUpPauseGame, 100);
}

void GameScene::CreatePartical()
{
	this->m_flyingPartical = ParticleSystemQuad::create("TexturePacker/flying.plist");
	this->m_flyingPartical->setVisible(false);
	this->m_flyingPartical->setScale(0.3);
	this->addChild(this->m_flyingPartical);
}

void GameScene::CreateMovingPlatform()
{
	for (cocos2d::Value Enemy1Value : this->m_map->GetObjectGroup("MovingObject"))
	{
		float x = Enemy1Value.asValueMap()["x"].asFloat();
		float y = Enemy1Value.asValueMap()["y"].asFloat();

		MovingPlatform* object = MovingPlatform::create();
		object->setPosition(x, y);
		this->addChild(object);
		object->CreateBody(this->m_physicWorld->getWorld());

		auto numPosition = Enemy1Value.asValueMap()["numPosition"].asInt();
		for (int i = 1; i <= numPosition; i++)
		{
			float xP = Enemy1Value.asValueMap()["Position" + std::to_string(i) + "X"].asFloat();
			float yP = this->m_map->GetSizeHeight() - Enemy1Value.asValueMap()["Position" + std::to_string(i) + "Y"].asFloat();
			object->m_movePosition.push_back(Vec2(xP, yP));
		}
		object->m_timeRun = Enemy1Value.asValueMap()["timeFly"].asFloat();
		object->m_timeDelay = Enemy1Value.asValueMap()["timeDelay"].asFloat();
		if (numPosition > 1)
			object->RunActionMoveTo();
		this->m_vectorMovingPlatform.pushBack(object);
	}
}

void GameScene::CreateElevator()
{
	for (cocos2d::Value Enemy1Value : this->m_map->GetObjectGroup("Elevator"))
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();

		float x = Enemy1Value.asValueMap()["x"].asFloat();
		float y = Enemy1Value.asValueMap()["y"].asFloat();

		Elevator* object = Elevator::create();
		object->setPosition(x, y);
		this->addChild(object);

		object->CreateBody(this->m_physicWorld->getWorld());

		auto numPosition = Enemy1Value.asValueMap()["numPosition"].asInt();
		for (int i = 1; i <= numPosition; i++)
		{
			float xP = Enemy1Value.asValueMap()["Position" + std::to_string(i) + "X"].asFloat();
			float yP = this->m_map->GetSizeHeight() - Enemy1Value.asValueMap()["Position" + std::to_string(i) + "Y"].asFloat();
			object->m_movePosition.push_back(Vec2(xP, yP));
		}

		object->m_timeRun = Enemy1Value.asValueMap()["timeFly"].asFloat();
		this->m_vectorElevator.pushBack(object);
	}
}

void GameScene::CreateStone()
{
	for (int i = 0; i < NumStone; i++)
	{
		auto stone = Stone::create();
		stone->Setb2World(this->m_physicWorld->getWorld());
		stone->CreateBody();
		stone->setVisible(false);
		this->addChild(stone);
		this->m_vectorStone.addObject(stone);
	}
}

#pragma endregion

void GameScene::FixBugMoveButton()
{
	if (!this->m_contactListener->CanJump())
	{
		this->unschedule(schedule_selector(GameScene::CheckMoveLoop));
		this->m_leftButtonPressed = false;
		this->m_rightButtonPressed = false;
	}
}

Vec2 GameScene::GetLocationInView(Vec2 location)
{
	return Vec2((location.x), (location.y + this->m_defaultCamera->getPosition().y - (Director::getInstance()->getVisibleSize().height / 2)));
}

void GameScene::ShowLocalLabel(float y)
{
	int i = y;
	if (i >= HeightStartWind - 10 && i < HeightStartIce - 20 && this->m_contactListener->GetCheckPointContact() != nullptr)
	{
		if (this->m_windyLabelBool)
		{
			auto visibleSize = Director::getInstance()->getVisibleSize();
			this->m_windyLabel = Label::createWithTTF("Windy land", "fonts/retro_computer_personal_use.ttf", 45);
			this->m_windyLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 250));
			this->m_windyLabel->setColor(Color3B::RED);
			this->addChild(this->m_windyLabel, 100);
			this->m_windyLabel->setCameraMask((unsigned int)CameraFlag::USER1);
			this->m_windyLabel->runAction(Sequence::create(FadeIn::create(0.5), DelayTime::create(1.5), FadeOut::create(1), RemoveSelf::create(true), NULL));
			this->m_windyLabelBool = false;
		}
	}
	else
		if (i >= HeightStartIce - 10 && i < HeightStartCastle - 20 && this->m_contactListener->GetCheckPointContact() != nullptr)
		{
			if (this->m_icyLabelBool)
			{
				auto visibleSize = Director::getInstance()->getVisibleSize();
				this->m_icyLabel = Label::createWithTTF("Icy land", "fonts/retro_computer_personal_use.ttf", 45);
				this->m_icyLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 250));
				this->m_icyLabel->setColor(Color3B::RED);
				this->addChild(this->m_icyLabel, 100);
				this->m_icyLabel->setCameraMask((unsigned int)CameraFlag::USER1);
				this->m_icyLabel->runAction(Sequence::create(FadeIn::create(0.5), DelayTime::create(1.5), FadeOut::create(1), RemoveSelf::create(true), NULL));
				this->m_icyLabelBool = false;

				this->archivement->setStringForLabel("Got achievement: \nWind Conqueror");
				this->archivement->setPositionForAll(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 250));
				this->archivement->setCameraMask((unsigned int)CameraFlag::USER1);
				this->archivement->RunAction();
			}
		}
		else
			if (i >= HeightStartCastle - 10 && this->m_contactListener->GetCheckPointContact() != nullptr)
				if (this->m_castleLabelBool)
				{
					auto* scene = PlayPlot2::create();
					Director::getInstance()->pushScene(TransitionFade::create(0.3, scene));

					this->ScheduleStoneFall(0);
					this->schedule(schedule_selector(GameScene::ScheduleStoneFall), 5);

					auto visibleSize = Director::getInstance()->getVisibleSize();
					this->m_castleLabel = Label::createWithTTF("Fairy castle", "fonts/retro_computer_personal_use.ttf", 45);
					this->m_castleLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 250));
					this->m_castleLabel->setColor(Color3B::RED);
					this->m_castleLabel->setCameraMask((unsigned int)CameraFlag::USER1);
					this->addChild(this->m_castleLabel);
					this->m_castleLabel->runAction(Sequence::create(FadeIn::create(0.5), DelayTime::create(1.5), FadeOut::create(1), RemoveSelf::create(true), NULL));
					this->m_castleLabelBool = false;

					this->archivement->setStringForLabel("Got achievement: \nKing Of Ice");
					this->archivement->setPositionForAll(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 250));
					this->archivement->setCameraMask((unsigned int)CameraFlag::USER1);
					this->archivement->RunAction();
				}
}

Vec2 GameScene::CenterPointCamera(Vec2 position)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (position.x < visibleSize.width / 2 / ScaleFactor)
		return Vec2(visibleSize.width / 2 / ScaleFactor, this->m_player->getPosition().y);
	else if (visibleSize.width - visibleSize.width / 2 / ScaleFactor)
		return Vec2(visibleSize.width - visibleSize.width / 2 / ScaleFactor, this->m_player->getPosition().y);
	else
		return Vec2(this->m_player->getPosition().x, this->m_player->getPosition().y);
}

void GameScene::ShowArchieveAnnoucement(TypeItem item)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	switch (item)
	{
	case TypeItem::TIME_SLINGSHOT:
	{
		this->archivement->setStringForLabel("Got achievement: \nTime Master");
		this->archivement->setPositionForAll(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 250));
		this->archivement->setCameraMask((unsigned int)CameraFlag::USER1);
		this->archivement->RunAction();
	}
	break;
	case TypeItem::FIRE_SLINGSHOT:
	{
		this->archivement->setStringForLabel("Got achievement: \nFire Wizard");
		this->archivement->setPositionForAll(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 250));
		this->archivement->setCameraMask((unsigned int)CameraFlag::USER1);
		this->archivement->RunAction();
	}
	break;
	case TypeItem::DIAMOND_SLINGSHOT:
	{
		this->archivement->setStringForLabel("Got achievement: \nProtector");
		this->archivement->setPositionForAll(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 250));
		this->archivement->setCameraMask((unsigned int)CameraFlag::USER1);
		this->archivement->RunAction();
	}
	}
}

void GameScene::CreateAnimationAppearanceSlingShot()
{
	auto spriteAnimation = Sprite::createWithSpriteFrameName("appearance_01.png");
	spriteAnimation->setPosition(this->m_player->getPosition());
	spriteAnimation->setScale(0.7f);
	this->addChild(spriteAnimation, 10);

	const int iNumberSprite = 9;
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(iNumberSprite);

	for (int i = 1; i <= 9; i++)
	{
		std::string name = "appearance_0" + std::to_string(i) + ".png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
	auto animate = Animate::create(animation);
	spriteAnimation->runAction(Sequence::create(animate, RemoveSelf::create(), nullptr));
}

void GameScene::ScheduleStoneFall(float dt)
{
	this->m_vectorBoss.at(0)->Attack();
	auto stone = this->m_vectorStone.getObject();
	stone->SetStartAndDestinatePosition(Vec2(this->m_player->getPosition().x, HeightEndCastle),
		Vec2(this->m_player->getPosition().x, HeightStartCastle));
	stone->SetParent(this, Vec2(this->m_player->getPosition().x, HeightStartCastle));
	stone->CreateAnimate();
}

void GameScene::CreateJail()
{
	b2Body* m_b2body;
	b2PolygonShape m_bodyShape;
	b2BodyDef m_bodyDef;
	b2FixtureDef m_fixtureDef;
	b2Fixture* m_fixture;
	this->m_jail = Sprite::create("Images/Jail.png");
	this->m_jail->setPosition(480, 13310);
	this->m_jail->setAnchorPoint(Vec2(0, 0));
	this->m_jail->setScale(0.15);
	this->addChild(this->m_jail);

	m_bodyShape.SetAsBox(this->m_jail->getBoundingBox().size.width / (2 * PTM_RATIO), this->m_jail->getBoundingBox().size.height / (2 * PTM_RATIO));

	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set((this->m_jail->getPosition().x + this->m_jail->getBoundingBox().size.width / 2) / 32.0f,
		(this->m_jail->getPosition().y + this->m_jail->getBoundingBox().size.height / 2) / 32.0f);

	m_fixtureDef.shape = &m_bodyShape;
	m_fixtureDef.isSensor = true;

	m_b2body = this->m_physicWorld->getWorld()->CreateBody(&m_bodyDef);
	m_fixture = m_b2body->CreateFixture(&m_fixtureDef);
	m_fixture->SetUserData(new TypeObject(IdJail, this));
}

Vec2 GameScene::GetPositionCamera()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto retPosition = Vec2::ZERO;

	if (this->m_player->getPosition().x < visibleSize.width / 2 / ScaleFactor)
		retPosition.x = visibleSize.width / 2 / ScaleFactor;
	else if (this->m_player->getPosition().x > this->m_map->GetSizeWidth() - visibleSize.width / 2 / ScaleFactor)
		retPosition.x = this->m_map->GetSizeWidth() - visibleSize.width / 2 / ScaleFactor;
	else
		retPosition.x = this->m_player->getPosition().x;

	if (this->m_player->getPosition().y < visibleSize.height / 2 / ScaleFactor)
		retPosition.y = visibleSize.height / 2 / ScaleFactor;
	else if (this->m_player->getPosition().y > this->m_map->GetSizeHeight() - visibleSize.height / 2 / ScaleFactor)
		retPosition.y = this->m_map->GetSizeHeight() - visibleSize.height / 2 / ScaleFactor;
	else
		retPosition.y = this->m_player->getPosition().y;

	return retPosition;
}
