#include "PopUpPause.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "LoadGameScene.h"
#include "SoundMgr.h"

bool PopUpPause::init()
{
	if (!Node::init())
		return false;

	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();

	m_popupLayer = Layer::create();
	m_popupLayer->setAnchorPoint(Vec2::ZERO);
	addChild(m_popupLayer);

	auto _background = Sprite::createWithSpriteFrameName("bg_pause.png");
	_background->setAnchorPoint(Vec2::ZERO);
	_background->setPosition(Point::ZERO);
	_background->setScale(0.55);
	m_popupLayer->addChild(_background);

	auto _background1 = Sprite::createWithSpriteFrameName("table_pause.png");
	_background1->setAnchorPoint(Vec2::ZERO);
	_background1->setPosition(Vec2(_background->getPositionX() + m_visibleSize.width * 0.04, _background->getPositionY() + m_visibleSize.height * 0.02));
	_background1->setScaleX(0.56);
	_background1->setScaleY(0.75);
	m_popupLayer->addChild(_background1);

	m_backgroundContentSize = _background->getBoundingBox().size;

	this->m_startPosition = Vec2(m_visibleSize.width + m_origin.x, m_visibleSize.height / 2 - m_backgroundContentSize.height / 2 + m_origin.y);
	this->m_endPosition = Vec2(m_visibleSize.width / 2 - m_backgroundContentSize.width / 2 + m_origin.x, m_visibleSize.height / 2 - m_backgroundContentSize.height / 2 + m_origin.y);

	m_popupLayer->setPosition(this->m_startPosition);

	m_appearAction = TargetedAction::create(m_popupLayer, MoveTo::create(0.4f, this->m_endPosition));
	m_disappearAction = TargetedAction::create(m_popupLayer, MoveTo::create(0.4f, this->m_startPosition));
	this->m_seq = Sequence::create(m_appearAction->clone(), CallFunc::create(CC_CALLBACK_0(PopUpPause::Pause, this)), nullptr);

	//this->m_seq->retain();
	//m_appearAction->retain();
	//m_disappearAction->retain();

	// Button resume
	auto _labelResume = Label::createWithTTF("Resume", "fonts/retro_computer_personal_use.ttf", 35);
	_labelResume->setColor(Color3B(255, 0, 0));
	_labelResume->enableShadow();
	_labelResume->enableOutline(Color4B::WHITE, 1);
	_labelResume->enableGlow(Color4B::YELLOW);
	auto buttonResume = Button::create();
	buttonResume->setTitleLabel(_labelResume);
	buttonResume->setPosition(Vec2(this->m_backgroundContentSize.width * 5.f / 10.f + m_origin.x,
		this->m_backgroundContentSize.height * 7.75f / 10.f + m_origin.y));
	m_popupLayer->addChild(buttonResume, 15);
	buttonResume->addTouchEventListener(CC_CALLBACK_2(PopUpPause::OnButtonResume, this));

	// Button Restart
	auto _labelRestart = Label::createWithTTF("Restart", "fonts/retro_computer_personal_use.ttf", 35);
	_labelRestart->setColor(Color3B(255, 0, 0));
	_labelRestart->enableShadow();
	_labelRestart->enableOutline(Color4B::WHITE, 1);
	_labelRestart->enableGlow(Color4B::YELLOW);
	auto buttonRestart = Button::create();
	buttonRestart->setTitleLabel(_labelRestart);
	buttonRestart->setPosition(Vec2(this->m_backgroundContentSize.width * 5.f / 10.f + m_origin.x,
		this->m_backgroundContentSize.height * 6.25f / 10.f + m_origin.y));
	m_popupLayer->addChild(buttonRestart, 15);
	buttonRestart->addTouchEventListener(CC_CALLBACK_2(PopUpPause::OnButtonRestart, this));

	// Exit
	auto _labelExit = Label::createWithTTF("Exit and save", "fonts/retro_computer_personal_use.ttf", 35);
	_labelExit->setColor(Color3B(255, 0, 0));
	_labelExit->enableShadow();
	_labelExit->enableOutline(Color4B::WHITE, 1);
	_labelExit->enableGlow(Color4B::YELLOW);
	auto buttonExit = Button::create();
	buttonExit->setTitleLabel(_labelExit);
	buttonExit->setPosition(Vec2(this->m_backgroundContentSize.width * 5.f / 10.f + m_origin.x,
		this->m_backgroundContentSize.height * 4.75f / 10.f + m_origin.y));
	m_popupLayer->addChild(buttonExit, 15);
	buttonExit->addTouchEventListener(CC_CALLBACK_2(PopUpPause::OnButtonExit, this));

	// Sound
	if (SoundMgr::getInstance()->isMuteBgMusic())
		m_buttonSound = Button::create("Images/sound_off.png", "Images/sound_off1.png");
	else
		m_buttonSound = Button::create("Images/sound.png", "Images/sound1.png");
	m_buttonSound->setScale(0.325);
	m_buttonSound->setPosition(Vec2(this->m_backgroundContentSize.width * 2.f / 10.f + m_origin.x,
		this->m_backgroundContentSize.height * 3.f / 10.f + m_origin.y));
	m_popupLayer->addChild(m_buttonSound, 15);
	m_buttonSound->addTouchEventListener(CC_CALLBACK_2(PopUpPause::OnButtonSound, this));

	// Music
	if (SoundMgr::getInstance()->isMusteEffectMusic())
		m_buttonMusic = Button::create("Images/music_off.png", "Images/music_off1.png");
	else
		m_buttonMusic = Button::create("Images/misic.png", "Images/misic1.png");
	m_buttonMusic->setScale(0.325);
	m_buttonMusic->setPosition(Vec2(this->m_backgroundContentSize.width * 4.f / 10.f + m_origin.x,
		this->m_backgroundContentSize.height * 3.f / 10.f + m_origin.y));
	m_popupLayer->addChild(m_buttonMusic, 15);
	m_buttonMusic->addTouchEventListener(CC_CALLBACK_2(PopUpPause::OnButtonMusic, this));

	return true;
}

void PopUpPause::disappear()
{
	if (!this->m_close)
		this->runAction(m_disappearAction->clone());
	this->m_close = true;
}

void PopUpPause::appear()
{
	if (this->m_close)
		this->runAction(this->m_seq->clone());
	this->m_close = false;
}

void PopUpPause::setTitlePopup(std::string _titlePopup)
{
	auto _title = Label::createWithTTF(_titlePopup, "fonts/ARCADECLASSIC.TTF", 29);

	_title->setAdditionalKerning(7.0f);
	_title->setPosition(Point(m_backgroundContentSize.width / 2 + m_origin.x, m_backgroundContentSize.height * 9.25 / 10 + m_origin.y));

	_title->setColor(Color3B(255, 255, 128));
	_title->setScale(1.5f);

	m_popupLayer->addChild(_title);
}

void PopUpPause::setTitlePopUpWithSprite(std::string _pathSprite)
{
	auto spriteTitle = Sprite::create(_pathSprite);
	spriteTitle->setAnchorPoint(Vec2::ZERO);
	spriteTitle->setPosition(Vec2(m_backgroundContentSize.width * 3 / 10.f + m_origin.x, m_backgroundContentSize.height * 8.5 / 10 + m_origin.y));
	spriteTitle->setScale(0.25);
	m_popupLayer->addChild(spriteTitle);
}

void PopUpPause::OnButtonSound(Ref* sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		if (SoundMgr::getInstance()->isMuteBgMusic())
		{
			m_buttonSound->loadTextures("Images/sound.png", "Images/sound1.png");
			SoundMgr::getInstance()->SetMuteBgMusic(false);
		}
		else
		{
			m_buttonSound->loadTextures("Images/sound_off.png", "Images/sound_off1.png");
			SoundMgr::getInstance()->SetMuteBgMusic(true);
		}
		break;
	default:
		break;
	}
}

void PopUpPause::OnButtonMusic(Ref* sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		if (SoundMgr::getInstance()->isMusteEffectMusic())
		{
			m_buttonMusic->loadTextures("Images/misic.png", "Images/misic1.png");
			SoundMgr::getInstance()->SetMuteEffectMusic(false);
		}
		else
		{
			m_buttonMusic->loadTextures("Images/music_off.png", "Images/music_off1.png");
			SoundMgr::getInstance()->SetMuteEffectMusic(true);
		}
		break;
	default:
		break;
	}
}

void PopUpPause::OnButtonResume(Ref* sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		Director::getInstance()->resume();
		this->m_bResume = true;
		this->disappear();
		break;
	default:
		break;
	}
}

void PopUpPause::OnButtonRestart(Ref* sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		Director::getInstance()->resume();
		GameValue::getInstance()->Reset();
		Director::getInstance()->replaceScene(LoadGameScene::createScene(false));
		break;
	default:
		break;
	}
}

void PopUpPause::OnButtonExit(Ref* sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		Director::getInstance()->resume();
		GameValue::getInstance()->SetIsLoadGame(true);
		GameValue::getInstance()->SaveGameValue();
		GameValue::getInstance()->SaveHighScore();
		GameValue::getInstance()->SaveIsLoadGame();
		SoundMgr::getInstance()->StopAll();

		Director::getInstance()->replaceScene(MainMenuScene::createScene());
		break;
	default:
		break;
	}
}

void PopUpPause::OnButtonSave(Ref* sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		break;
	default:
		break;
	}
}

void PopUpPause::onExit()
{
	//m_appearAction->release();
	//m_disappearAction->release();
	//this->m_seq->release();
	Node::onExit();
}