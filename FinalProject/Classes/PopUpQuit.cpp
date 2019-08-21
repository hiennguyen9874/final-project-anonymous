#include "PopUpQuit.h"
#include "GameValue.h"

bool PopUpQuit::init()
{
	if (!Node::init())
		return false;

	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();

	m_popupLayer = Layer::create();
	m_popupLayer->setAnchorPoint(Vec2::ZERO);
	addChild(m_popupLayer);

	auto _background = Sprite::createWithSpriteFrameName("bg_settings.png");
	_background->setAnchorPoint(Vec2::ZERO);
	_background->setPosition(Point::ZERO);
	_background->setScaleX(0.55);
	_background->setScaleY(0.25);
	m_popupLayer->addChild(_background);

	auto _background1 = Sprite::createWithSpriteFrameName("table_settings.png");
	_background1->setAnchorPoint(Vec2::ZERO);
	_background1->setPosition(Vec2(_background->getPositionX() + m_visibleSize.width * 0.04, _background->getPositionY() + m_visibleSize.height * 0.02));
	_background1->setScaleX(0.565);
	_background1->setScaleY(0.25);
	m_popupLayer->addChild(_background1);

	m_backgroundContentSize = _background->getBoundingBox().size;

	auto _title1 = Label::createWithTTF("Are you sure you want to quit", "fonts/retro_computer_personal_use.ttf", 27);
	_title1->setPosition(Point(m_backgroundContentSize.width * 5.f / 10.0f + m_origin.x, m_backgroundContentSize.height * 7.35f / 10 + m_origin.y));
	_title1->setColor(Color3B(255, 0, 0));
	m_popupLayer->addChild(_title1);

	auto _title2 = Label::createWithTTF("this awesome game?", "fonts/retro_computer_personal_use.ttf", 27);
	_title2->setPosition(Point(m_backgroundContentSize.width * 5.f / 10.0f + m_origin.x, m_backgroundContentSize.height * 5.85f / 10 + m_origin.y));
	_title2->setColor(Color3B(255, 0, 0));
	m_popupLayer->addChild(_title2);

	auto _labelYes = Label::createWithTTF("Yes", "fonts/retro_computer_personal_use.ttf", 35);
	_labelYes->setColor(Color3B(255, 0, 0));
	_labelYes->enableShadow();
	_labelYes->enableOutline(Color4B::WHITE, 1);
	_labelYes->enableGlow(Color4B::YELLOW);
	auto buttonYes = Button::create();
	buttonYes->setTitleLabel(_labelYes);
	buttonYes->setPosition(Vec2(this->m_backgroundContentSize.width * 3.f / 10.f + m_origin.x, this->m_backgroundContentSize.height * 3.5f / 10.f + m_origin.y));
	m_popupLayer->addChild(buttonYes);
	buttonYes->addTouchEventListener(CC_CALLBACK_2(PopUpQuit::OnButtonYes, this));

	auto _labelNo = Label::createWithTTF("No", "fonts/retro_computer_personal_use.ttf", 35);
	_labelNo->setColor(Color3B(255, 0, 0));
	_labelNo->enableShadow();
	_labelNo->enableOutline(Color4B::WHITE, 1);
	_labelNo->enableGlow(Color4B::YELLOW);
	auto buttonNo = Button::create();
	buttonNo->setTitleLabel(_labelNo);
	buttonNo->setPosition(Vec2(this->m_backgroundContentSize.width * 7.f / 10.f + m_origin.x, this->m_backgroundContentSize.height * 3.5f / 10.f + m_origin.y));
	m_popupLayer->addChild(buttonNo);
	buttonNo->addTouchEventListener(CC_CALLBACK_2(PopUpQuit::OnButtonNo, this));

	Vec2 StartPosition = Vec2(m_visibleSize.width + m_origin.x, m_visibleSize.height / 2 - m_backgroundContentSize.height / 2 + m_origin.y);
	m_popupLayer->setPosition(StartPosition);

	m_appearAction = TargetedAction::create(m_popupLayer, MoveTo::create(0.35f, Vec2(m_visibleSize.width / 2 - m_backgroundContentSize.width / 2 + m_origin.x,
		m_visibleSize.height / 2 - m_backgroundContentSize.height / 2 + m_origin.y)));

	m_disappearAction = TargetedAction::create(m_popupLayer, MoveTo::create(0.35f, StartPosition));

	m_appearAction->retain();
	m_disappearAction->retain();

	return true;
}

void PopUpQuit::disappear()
{
	if (!this->m_close)
		this->runAction(m_disappearAction->clone());
	this->m_close = true;
}

void PopUpQuit::appear()
{
	if (this->m_close)
		this->runAction(m_appearAction->clone());
	this->m_close = false;
}

void PopUpQuit::setTitlePopup(std::string _titlePopup)
{
	auto _title = Label::createWithTTF(_titlePopup, "fonts/ARCADECLASSIC.TTF", 29);

	_title->setAdditionalKerning(7.0f);
	_title->setPosition(Point(m_backgroundContentSize.width / 2 + m_origin.x, m_backgroundContentSize.height * 9.25 / 10 + m_origin.y));

	_title->setColor(Color3B(255, 255, 128));
	_title->setScale(1.5f);

	m_popupLayer->addChild(_title);
}

void PopUpQuit::setTitlePopUpWithSprite(std::string _pathSprite)
{
	auto spriteTitle = Sprite::create(_pathSprite);
	spriteTitle->setAnchorPoint(Vec2::ZERO);
	spriteTitle->setPosition(Vec2(m_backgroundContentSize.width * 3 / 10.f + m_origin.x, m_backgroundContentSize.height * 8.5 / 10 + m_origin.y));
	spriteTitle->setScale(0.25);
	m_popupLayer->addChild(spriteTitle);
}

void PopUpQuit::OnButtonYes(Ref * sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		GameValue::getInstance()->SaveGameValue();
		GameValue::getInstance()->SaveHighScore();
		Director::getInstance()->end(); 
		break;
	default:
		break;
	}
}

void PopUpQuit::OnButtonNo(Ref * sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		this->disappear();
		break;
	default:
		break;
	}
}

void PopUpQuit::onExit()
{
	m_appearAction->release();
	m_disappearAction->release();
	Node::onExit();
}