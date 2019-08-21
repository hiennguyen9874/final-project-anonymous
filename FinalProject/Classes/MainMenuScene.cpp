#pragma region Include

#include "MainMenuScene.h"
#include "GameScene.h"
#include "LoadGameScene.h"
#include "Utils.h"
#include "CustomLayer.h"
#include "InfiniteParallaxNode.h"
#include "Config.h"
#include "AudioEngine.h"
#include "SoundMgr.h"

#pragma endregion

USING_NS_CC;
using namespace ui;
using namespace std;

Scene* MainMenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
	layer->init();
	scene->addChild(layer);
	return scene;
}

bool MainMenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	SoundMgr::getInstance()->PlayMainMenuMusic();


	Vector<Layer *> vectorLayer;
	for (int i = 0; i < 7; i++)
	{
		auto layer = CustomLayer::CreateWithSpriteName("Background/parallax/1/" + std::to_string(7 - i) + ".png");
		vectorLayer.pushBack(layer);
		m_Size = layer->GetContentSizeOfSprite();
	}

	m_parallaxBackground = InfiniteParallaxNode::create();
	m_parallaxBackground->setAnchorPoint(Vec2(0.5f, 0.5f));
	for (int i = 0; i < 7; i++)
	{
		m_parallaxBackground->addChild(vectorLayer.at(i), 0.0f, Vec2(0.3 + i * 0.075, 0.3 + i * 0.1), Vec2::ZERO);
	}
	this->addChild(m_parallaxBackground, -10.0f);

	// Title
	auto _title = Sprite::create("Background/Name.png");
	_title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 8.f / 10.0f));
	this->addChild(_title);

	// Button Play
	auto buttonPlay = Button::create("Images/play.png", "Images/play1.png");
	buttonPlay->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 5.5f / 10.0f));
	buttonPlay->setScale(0.35);
	this->addChild(buttonPlay);

	this->m_popUpPlay = PopUpPlay::create();
	this->m_popUpPlay->retain();
	this->addChild(this->m_popUpPlay, 2);
	buttonPlay->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::OnButtonPlay, this));

	// High score
	auto buttonPrize = Button::create("Images/prize.png", "Images/prize1.png");
	buttonPrize->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 4.0f / 10.0f));
	buttonPrize->setScale(buttonPlay->getBoundingBox().size.width / buttonPrize->getContentSize().width);
	this->addChild(buttonPrize);

	this->m_popUpHighScore = PopupHighScore::create();
	this->m_popUpHighScore->retain();
	this->addChild(this->m_popUpHighScore, 2);
	buttonPrize->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::OnButtonHighScore, this));

	// About
	auto buttonAbout = Button::create("Images/about.png", "Images/about1.png");
	buttonAbout->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 2.5f / 10.0f));
	buttonAbout->setScale(buttonPlay->getBoundingBox().size.width / buttonAbout->getContentSize().width);
	this->addChild(buttonAbout);

	this->m_popUpAbout = PopUpAbout::create();
	this->m_popUpAbout->retain();
	this->addChild(this->m_popUpAbout, 2);
	buttonAbout->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::OnButtonAbout, this));

	// Setting
	auto buttonSetting = Button::create("Images/setting.png", "Images/setting1.png");
	buttonSetting->setPosition(Vec2(visibleSize.width * 9.25f / 10.0f, visibleSize.height * 0.5f / 10.0f));
	buttonSetting->setScale(buttonPlay->getBoundingBox().size.width * 0.5 / buttonSetting->getContentSize().width);
	this->addChild(buttonSetting);

	this->m_popupSetting = PopupSetting::create();
	this->m_popupSetting->retain();
	this->addChild(this->m_popupSetting, 2);
	buttonSetting->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::OnButtonSetting, this));

	// Button Exit
	auto buttonExit = Button::create("Images/close.png", "Images/close1.png");
	buttonExit->setPosition(Vec2(visibleSize.width * 0.75f / 10.0f, visibleSize.height * 0.5f / 10.0f));
	buttonExit->setScale(buttonPlay->getBoundingBox().size.width * 0.5 / buttonExit->getContentSize().width);
	this->addChild(buttonExit);

	this->m_popUpQuit = PopUpQuit::create();
	this->m_popUpQuit->retain();
	this->addChild(this->m_popUpQuit, 2);
	buttonExit->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::OnButtonExit, this));

	this->schedule(schedule_selector(MainMenuScene::updateBackground), 1 / 30.f);
	return true;
}

void MainMenuScene::updateBackground(float dt) {
	if (this->m_xuoi)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		float PositionX = m_parallaxBackground->getPosition().x - visibleSize.width * 0.005;
		this->m_parallaxBackground->setPositionX(PositionX);
		if (m_parallaxBackground->getPosition().x <= -1024)
			this->m_xuoi = !this->m_xuoi;
	}
	else
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		float PositionX = m_parallaxBackground->getPosition().x + visibleSize.width * 0.005;
		this->m_parallaxBackground->setPositionX(PositionX);
		if (m_parallaxBackground->getPosition().x >= 1024)
			this->m_xuoi = !this->m_xuoi;
	}
}

void MainMenuScene::onEnter()
{
	Scene::onEnter();
}

void MainMenuScene::onExit()
{
	Scene::onExit();
}

void MainMenuScene::OnButtonPlay(Ref * sender, Widget::TouchEventType type)
{
	int id = experimental::AudioEngine::play2d("audios/click.mp3");
	experimental::AudioEngine::setVolume(id, SoundMgr::getInstance()->GetVolumeEffect());

	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		if (!this->HasPopUp())
			this->m_popUpPlay->appear();
		break;
	default:
		break;
	}
}

void MainMenuScene::OnButtonSetting(Ref * sender, Widget::TouchEventType type)
{
	int id = experimental::AudioEngine::play2d("audios/click.mp3");
	experimental::AudioEngine::setVolume(id, SoundMgr::getInstance()->GetVolumeEffect());
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		if (!this->HasPopUp())
			this->m_popupSetting->appear();
		break;
	default:
		break;
	}
}

void MainMenuScene::OnButtonAbout(Ref * sender, Widget::TouchEventType type)
{
	int id = experimental::AudioEngine::play2d("audios/click.mp3");
	experimental::AudioEngine::setVolume(id, SoundMgr::getInstance()->GetVolumeEffect());
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		if (!this->HasPopUp())
			this->m_popUpAbout->appear();
		break;
	default:
		break;
	}
}

void MainMenuScene::OnButtonHighScore(Ref * sender, Widget::TouchEventType type)
{
	int id = experimental::AudioEngine::play2d("audios/click.mp3");
	experimental::AudioEngine::setVolume(id, SoundMgr::getInstance()->GetVolumeEffect());
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		if (!this->HasPopUp())
			this->m_popUpHighScore->appear();
		break;
	default:
		break;
	}
}

void MainMenuScene::OnButtonExit(Ref * sender, Widget::TouchEventType type)
{
	int id = experimental::AudioEngine::play2d("audios/click.mp3");
	experimental::AudioEngine::setVolume(id, SoundMgr::getInstance()->GetVolumeEffect());
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		if (!this->HasPopUp())
			this->m_popUpQuit->appear();
		break;
	default:
		break;
	}
}

Vec2 MainMenuScene::setViewPointCenter(Point position) {
	auto winSize = Director::getInstance()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);

	x = MIN(x, m_Size.x - winSize.width / 2);
	y = MIN(y, m_Size.y - winSize.height / 2);

	auto actualPosition = Point(x, y);

	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;
	return viewPoint;
}
