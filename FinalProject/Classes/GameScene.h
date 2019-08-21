#pragma once

#pragma region Include
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "ui\CocosGUI.h"
#include "Player.h"
#include "SlingShot.h"
#include "Config.h"
#include "ObjectPool.h"
#include "ContacListener.h"
#include "MapTMX.h"
#include "CheckPoint.h"
#include "Location.h"
#include "HUDLayer.h"
#include "TreasureChest.h"
#include "LayerWindSprite.h"
#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include "ShopingScene.h"
#include "BackpackScene.h"
#include "GameValue.h"
#include "PopUpPause.h"
#include "PopupSetting.h"
#include "Enemy.h"
#include "ItemLoot.h"
#include "ContacListenerSimulate.h"
#include "Archievement.h"
#include "Boss.h"
#include "Wind.h"
#include "Stone.h"
#include "MovingPlatform.h"
#include "Elevator.h"
#include "PlayPlot2.h"
#include "EndScene.h"
#include "TurtorialLayer.h"
#include "Wind.h"
#pragma endregion

USING_NS_CC;
using namespace ui;

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(bool boolean);
	bool initWithLoad(bool boolean);
	static GameScene* createWithLoad(bool boolean);

	void update(float dt);
	void onEnter();
	void onExit();
	
	bool OnTouchBegan(Touch* touch, Event* event);
	bool OnTouchMoved(Touch* touch, Event* event);
	bool OnTouchEnded(Touch* touch, Event* event);

	void OnButtonLeftTouch(Ref* sender, Widget::TouchEventType type);
	void OnButtonRightTouch(Ref* sender, Widget::TouchEventType type);
	void OnButtonShopTouch(Ref* sender, Widget::TouchEventType type);
	void OnButtonBackpackTouch(Ref* sender, Widget::TouchEventType type);
private:
	CCPoint SetViewPointCenter(Vec2 position);
	Vec2 CalculatePointOnTheCircle(Vec2 m_neoCircle, Vec2 m_point);

	void SimulateTrajectory(b2Vec2 & startingPosition, b2Vec2 & startingVelocity);
	void SimulateTrajectory();
	b2Vec2 GetTrajectoryPoint(b2Vec2& startingPosition, b2Vec2& startingVelocity, float n);
	void TouchBeganFunction(Touch* touch);

	void CreateMovementButton();
	void CreateCamera();
	void CreatePlayer(bool boolean);
	void CreateCheckPoint();
	void CreateDiamond();
	void CreateTreasureChest();
	void CreateEnemy();
	void CreateBoss();

	void CreateSimulationWorld(b2Vec2 gravity);
	void CreateCheckPointLocate();
	void CreateNotification();
	void CreateBackground();
	void CreateCollision(b2World *world);

	Vec2 GetLocationInView(Vec2 location);
	void CheckMoveLoop(float delta);
	void MoveToLeft();
	void MoveToRight();
	void UpdateDiamond();
	void UpdateTreasureChest();
	void UpdateCheckPoint();
	void UpdatePauseMenu();
	void UpdatePlayer();
	void UpdateHub(float dt);
	void UpdateCamera();
	void UpdateStatusPlayer();
	void UpdateGameValue();
	void UpdateNotification(float dt);
	void UpdateSound();
	void UpdateSlingshot();
	void UpdateBossContactWithStone();
	void UpdateOnElevatorButton();
	void UpdatePlayerDie();
	void UpdateWind(float dt);
	void EndWin();
	void UpdateImageSlingShot();
	void UpdatePerfect(Gold *gold);
	void UpdateEffectLand(float dt);

	void BeginDie() {
		this->m_notification->setString("You Die!");
		this->m_notification->setVisible(true);
		this->m_hubLayer->Dead();
	}

	void EndDie() {
		this->m_player->setVisible(true);

		//if (MovePositionPlayerWithTranform)
		//{
		//	this->m_player->m_movePositionPlayer = false;
		//	this->m_player->GetB2Body()->SetLinearVelocity(b2Vec2(0, 0));
		//}
		//else
		//	this->m_player->CreateBody(this->m_physicWorld->getWorld(), true);

		this->m_player->CreateBody(this->m_physicWorld->getWorld(), true);
		this->m_player->m_movePositionPlayer = false;
		
		this->m_notification->setVisible(false);

		this->m_isPlayerDie = false;
	}

	void CreateBoucingMethod();
	void CreateWindChallenge();
	void CreateWind();
	void CreateShopButton();
	void CreateBackpackButton();
	void CreatePauseMenu();
	void CreatePartical();
	void CreateMovingPlatform();
	void CreateElevator();
	void CreateStone();

	void ShowLocalLabel(float y);

	void FixBugMoveButton();
	Vec2 CenterPointCamera(Vec2 position);

	void ShowArchieveAnnoucement(TypeItem item);

	void CreateAnimationAppearanceSlingShot();

	void ScheduleStoneFall(float dt);

	void SetScheduleStoneToTrue() {
		m_bOnElevatorStartBoss = false;
		this->schedule(schedule_selector(GameScene::ScheduleStoneFall), 5);
		this->m_BossMatMau = true;
	}

	void CreateJail();

	Vec2 GetPositionCamera();

private:
	int m_maxHeight = 0;
	RefPtr<Sprite> m_wind;

	RefPtr<Camera> m_camera;
	RefPtr<Camera> m_defaultCamera;

	RefPtr<MapTMX> m_map;
	RefPtr<SlingShot> m_slingShot;
	RefPtr<Player> m_player;

	Vec2 m_vec2FirstPositionPlayerAndSlingShot;
	Vec2 m_DesPositionOfPlayer;

	RefPtr<DrawNode> m_drawNode;
	RefPtr<DrawNode> m_drawNodeSimulation;
	RefPtr<Sprite> m_checkPointLocate;

	RefPtr<Label> m_notification;

	ContacListener* m_contactListener = new ContacListener();
	ContacListenerSimulate *m_contactListenerSimualate = new ContacListenerSimulate();

	Vec2 m_vec2DesPosition;

	PhysicsSystem* m_physicWorld = new PhysicsSystem;

	b2World *m_SimulationWorld;
	b2Body *m_SimalationPlayerBody;

	bool m_isPull = false;
	bool m_isTouch = false;
	bool m_isPull2 = false;

	Vec2 m_Vec2DragDistance;
	Vec2 m_checkPoint;	

	bool m_windyLabelBool = true;
	bool m_icyLabelBool = true;
	bool m_castleLabelBool = true;
	RefPtr<Label> m_windyLabel;
	RefPtr<Label> m_icyLabel;
	RefPtr<Label> m_castleLabel;

	RefPtr<ParticleSystemQuad> m_flyingPartical;

	std::vector<Vec2> m_points;
	int m_NumJump = 0;				// So lan da nhay

	RefPtr<Button> m_Left;
	RefPtr<Button> m_Right;
	RefPtr<Button> m_Shop;
	RefPtr<Button> m_Backpack;

	bool m_leftButtonPressed = false;
	bool m_rightButtonPressed = false;

	string m_cheatCode;
	bool m_enableCheat = true;
	
	RefPtr<Location> m_location;			// Xac dinh vi tri touch

	RefPtr<HUDLayer> m_hubLayer;

	Vector<RefPtr<Gold>> m_VectorDiamond;
	Vector<RefPtr<TreasureChest>> m_VectorTreasureChest;
	Vector<RefPtr<CheckPoint>> m_VectorCheckPoint;

	bool m_isCancle;				
	bool m_bStartGame = true;
	bool m_isLoadGame;
	float m_timeFixMovementBug;
	float m_timeChangeWind;
	bool m_turnChangeWindDirection = false;
	bool m_isInBouncing = false;
	bool m_isInBouncingSimulate = false;
	bool m_isJumpAgain = true;
	bool m_isJumpingAgain = false;

	// Pause game
	RefPtr<PopUpPause> m_popUpPauseGame;
	bool m_prePauseGame = false;

	// Vector of Enemy
	Vector<RefPtr<Enemy>> m_vectorEnemy;

	// Pre treasure chest
	RefPtr<TreasureChest> m_preTreasureChest = nullptr;

	bool m_bIsFly = false;			// true: player dang nhay
	float m_speed;
	float m_fTimepNotification = 3.f;
	bool m_bUpdateNotification = false;

	Vector<RefPtr<Boss>> m_vectorBoss;
	RefPtr<Archivement> archivement;
	bool m_firstTimeShopping = false;
	RefPtr<Sprite> m_backGround;

	// pre Diamond
	RefPtr<Gold> m_preDiamond = nullptr;

	//ObjectPool<RefPtr<Wind>> m_opWind;
	Vector<RefPtr<MovingPlatform>> m_vectorMovingPlatform;
	bool m_bTouchWhenOnMovingPlatform = false;

	Vec2 m_Vec2DragOffsetStartInView;
	Vec2 m_Vec2DragOffsetEndInView;

	bool m_bSimulateTrajectory = false;
	b2Vec2 m_startPosition;
	b2Vec2 m_startVelocity;

	bool m_OnTouch = false;
	Vec2 m_drawFrom;
	Vec2 m_drawTo;
	Vec2 m_drawFrom1;
	Vec2 m_drawTo1;
	float m_drawRadious;

	Vec2 m_positionPlayer;
	
	Vec2 m_positionSlingShot = Vec2::ZERO;

	// Vector of Elevator
	Vector<RefPtr<Elevator>> m_vectorElevator;

	// Vector of Checkpoint
	Vector<RefPtr<CheckPoint>> m_checkPointMoving;

	// Vector of Stone
	ObjectPool<RefPtr<Stone>> m_vectorStone;

	bool m_bOnElevatorStartBoss = false;

	RefPtr<Sprite> m_jail;

	bool m_isPlayerDie = false;
	bool m_isTouchBegan = false;

	// Vector of Wind
	ObjectPool<RefPtr<Wind>> m_vectorWind;

	float m_fTimeMoveWind = DelayTimeUpdateWind;

	bool m_BossMatMau = false;		// true: Con boss se bi mat hp

	// Perfect
	bool m_perfectPath = true;
	int m_numCoinInPath = -1;
	int m_Indexpath = -1;
	int m_numCointHas = -1;

	float m_fPreTimeEffectLand = -1;
	bool m_preIsFlying = false;
};