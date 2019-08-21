#include "HUDLayer.h"
#include "GameValue.h"

bool HUDLayer::init()
{
	if (LayerColor::initWithColor(Color4B(0, 0, 0, 70), Director::getInstance()->getVisibleSize().width,
		Director::getInstance()->getVisibleSize().height * 4.0 / 100) == false)
		return false;

	this->m_VisibleSize = Director::getInstance()->getVisibleSize();
	this->m_VisibleOrigin = Director::getInstance()->getVisibleOrigin();

	// Diamond
	this->m_spriteDiamond = Sprite::createWithSpriteFrameName("Coin.png");
	this->m_spriteDiamond->setPosition(this->RetPosition(0.19));
	this->m_spriteDiamond->setScale(0.15);
	this->addChild(this->m_spriteDiamond);

	this->m_strDiamond = std::to_string((int)GameValue::getInstance()->cornScore);
	this->m_LabelDiamond = Label::createWithTTF(this->m_strDiamond, "fonts/retro_computer_personal_use.ttf", 29);
	this->m_LabelDiamond->setPosition(this->RetPosition(0.275));
	this->addChild(this->m_LabelDiamond);

	// Time
	this->m_spriteTime = Sprite::createWithSpriteFrameName("Time_Saving-512.png");
	this->m_spriteTime->setScale(this->m_spriteDiamond->getContentSize().height * this->m_spriteDiamond->getScaleY() / this->m_spriteTime->getContentSize().height);
	this->m_spriteTime->setPosition(this->RetPosition(0.835));
	this->addChild(this->m_spriteTime);

	this->m_strTime = std::to_string((int)GameValue::getInstance()->m_fTime);
	this->m_LabelTime = Label::createWithTTF(this->m_strTime, "fonts/retro_computer_personal_use.ttf", 29);
	this->m_LabelTime->setPosition(this->RetPosition(0.92));
	this->addChild(this->m_LabelTime);
	
	// Dead
	this->m_spriteNumDead = Sprite::createWithSpriteFrameName("chicken-512.png");
	this->m_spriteNumDead->setScale(this->m_spriteDiamond->getContentSize().height * this->m_spriteDiamond->getScaleY() / this->m_spriteNumDead->getContentSize().height);
	this->m_spriteNumDead->setPosition(this->RetPosition(0.35));
	this->addChild(this->m_spriteNumDead);

	this->m_strDead = std::to_string((int)GameValue::getInstance()->m_numDead);
	this->m_LabeDead = Label::createWithTTF(this->m_strDead, "fonts/retro_computer_personal_use.ttf", 29);
	this->m_LabeDead->setPosition(this->RetPosition(0.35 + 0.075));
	this->addChild(this->m_LabeDead);

	// Wind
	this->m_windDirectionSprite = Sprite::createWithSpriteFrameName("icons8-paper-plane-64.png");
	this->m_windDirectionSprite->setScale(0.6);
	this->m_windDirectionSprite->setVisible(false);
	this->addChild(this->m_windDirectionSprite);

	// Score
	this->m_spriteScore = Sprite::createWithSpriteFrameName("icons8-wow-button-64.png");
	this->m_spriteScore->setScale(this->m_spriteDiamond->getContentSize().height * this->m_spriteDiamond->getScaleY() / this->m_spriteScore->getContentSize().height);
	this->m_spriteScore->setPosition(this->RetPosition(0.62));
	this->addChild(this->m_spriteScore);

	this->m_LabelScore = Label::createWithTTF("0", "fonts/retro_computer_personal_use.ttf", 29);
	this->m_LabelScore->setPosition(this->RetPosition(0.7));
	this->addChild(this->m_LabelScore);

	// Pause button
	m_buttonPause = Button::create("Images/pause.png", "Images/pause1.png");
	m_buttonPause->setScale(this->m_spriteDiamond->getContentSize().height * 1.1 * this->m_spriteDiamond->getScaleY() / this->m_buttonPause->getContentSize().height);
	this->m_buttonPause->setPosition(this->RetPosition(0.05));
	this->addChild(this->m_buttonPause);

	m_buttonPause->addTouchEventListener(CC_CALLBACK_2(HUDLayer::OnButtonPause, this));

	this->m_spriteDiamond->setScale(0.13);
	return true;
}

void HUDLayer::SetPositionForHub(Vec2 positionPlayer, bool startBoolean)
{
	Vec2 position;
	if (startBoolean)
		position = Vec2(0, this->m_VisibleSize.height * 96.0f / 100);
	else
		position = Vec2(0, positionPlayer.y + this->m_VisibleSize.height * 46.0f / 100);
	this->setPosition(position);
}

void HUDLayer::SetPositionForHub(Vec2 PositionCamera)
{
	this->setPosition(Vec2(0, PositionCamera.y + this->m_VisibleSize.height * 46.0f / 100));
}

void HUDLayer::SetTime(float time)
{
	GameValue::getInstance()->m_fTime = time;
	//this->m_strTime = "Time: " + std::to_string((int)this->m_fTimeGame);
	this->m_strTime = std::to_string((int)GameValue::getInstance()->m_fTime);
	this->m_LabelTime->setString(this->m_strTime);
}

void HUDLayer::AddTime(float deltaTime)
{
	GameValue::getInstance()->m_fTime += deltaTime;
	this->m_strTime = std::to_string((int)GameValue::getInstance()->m_fTime);
	this->m_LabelTime->setString(this->m_strTime);
}

void HUDLayer::SetDiamond(int numDiamond)
{
	GameValue::getInstance()->cornScore = numDiamond;
	this->m_strDiamond = std::to_string((int)GameValue::getInstance()->cornScore);
	this->m_LabelDiamond->setString(this->m_strDiamond);
}

void HUDLayer::SetNumDead(int numDead)
{
	GameValue::getInstance()->m_numDead = numDead;
	this->m_strDead = std::to_string((int)GameValue::getInstance()->m_numDead);
	this->m_LabeDead->setString(this->m_strDead);
}

void HUDLayer::Dead()
{
	GameValue::getInstance()->m_numDead += 1;
	this->m_strDead = std::to_string((int)GameValue::getInstance()->m_numDead);
	this->m_LabeDead->setString(this->m_strDead);
}

void HUDLayer::ShowWindDirectionSprite()
{
	this->m_windDirectionSprite->setVisible(true);
}

void HUDLayer::ChangeWindDirection(bool i)
{
	if (i % 2 == 1)
	{
		this->m_windDirectionSprite->setScaleX(-1);
		this->m_windDirectionSprite->setPosition(this->RetPosition(0.5));
	}
	else
	{
		this->m_windDirectionSprite->setScaleX(1);
		this->m_windDirectionSprite->setPosition(this->RetPosition(0.5));
	}
}

void HUDLayer::HideWindDirectionSprite()
{
	this->m_windDirectionSprite->setVisible(false);
}

void HUDLayer::SetScore(int score)
{
	this->m_LabelScore->setString(std::to_string(score));
}

void HUDLayer::OnButtonPause(Ref * sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		if (!this->m_pauseGame)
		{
			m_buttonPause->loadTextures("Images/resume.png", "Images/resume1.png");
			this->m_pauseGame = true;
			this->m_popUpPauseGame->appear();
			//Director::getInstance()->pause();
		}
		else
		{
			m_buttonPause->loadTextures("Images/pause.png", "Images/pause1.png");
			this->m_pauseGame = false;
			this->m_popUpPauseGame->disappear();
			Director::getInstance()->resume();
		}
		break;
	default:
		break;
	}
}

void HUDLayer::SetStatusPause(bool enable)
{
	if (enable)
	{
		m_buttonPause->loadTextures("Images/resume.png", "Images/resume1.png");
		this->m_pauseGame = true;
	}
	else
	{
		m_buttonPause->loadTextures("Images/pause.png", "Images/pause1.png");
		this->m_pauseGame = false;
	}
}

Vec2 HUDLayer::RetPosition(float percent)
{
	return Vec2(this->m_VisibleSize.width * percent, this->m_VisibleSize.height * 2 / 100);
}
