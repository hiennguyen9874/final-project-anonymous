#include "PopUp.h"

bool PopUp::init()
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
	_background->setScale(0.55);
	m_popupLayer->addChild(_background);

	auto _background1 = Sprite::createWithSpriteFrameName("table_settings.png");
	_background1->setAnchorPoint(Vec2::ZERO);
	_background1->setPosition(Vec2(_background->getPositionX() + m_visibleSize.width * 0.04,
		_background->getPositionY() + m_visibleSize.height * 0.035));
	_background1->setScaleX(0.56);
	_background1->setScaleY(0.52);
	m_popupLayer->addChild(_background1);

	m_backgroundContentSize = _background->getBoundingBox().size;

	Vec2 StartPosition = Vec2(m_visibleSize.width + m_origin.x,
		m_visibleSize.height / 2 - m_backgroundContentSize.height / 2 + m_origin.y);
	m_popupLayer->setPosition(StartPosition);

	m_appearAction = TargetedAction::create(m_popupLayer, MoveTo::create(0.35f,
		Vec2(m_visibleSize.width / 2 - m_backgroundContentSize.width / 2 + m_origin.x,
			m_visibleSize.height / 2 - m_backgroundContentSize.height / 2 + m_origin.y)));

	m_disappearAction = TargetedAction::create(m_popupLayer, MoveTo::create(0.35f, StartPosition));

	m_appearAction->retain();
	m_disappearAction->retain();

	auto buttonClose = Button::create("Images/close.png", "Images/close1.png");
	buttonClose->setPosition(Point(m_backgroundContentSize.width * 9.2f / 10.0f + m_origin.x,
		m_backgroundContentSize.height * 9.25 / 10 + m_origin.y));
	buttonClose->setScale(0.25);
	m_popupLayer->addChild(buttonClose);
	buttonClose->addTouchEventListener(CC_CALLBACK_2(PopUp::OnButtonClose, this));

	return true;
}

void PopUp::disappear()
{
	if (!this->m_close)
		this->runAction(m_disappearAction->clone());
	this->m_close = true;
}

void PopUp::appear()
{
	if (this->m_close)
		this->runAction(m_appearAction->clone());
	this->m_close = false;
}

void PopUp::setTitlePopup(std::string _titlePopup)
{
	auto _title = Label::createWithTTF(_titlePopup, "fonts/ARCADECLASSIC.TTF", 29);

	_title->setAdditionalKerning(7.0f);
	_title->setPosition(Point(m_backgroundContentSize.width / 2 + m_origin.x,
		m_backgroundContentSize.height * 9.25 / 10 + m_origin.y));

	_title->setColor(Color3B(255, 255, 128));
	_title->setScale(1.5f);

	m_popupLayer->addChild(_title);
}

void PopUp::setTitlePopUpWithSprite(std::string _pathSprite)
{
	auto spriteTitle = Sprite::createWithSpriteFrameName(_pathSprite);
	spriteTitle->setAnchorPoint(Vec2::ZERO);
	spriteTitle->setPosition(Vec2(m_backgroundContentSize.width * 3 / 10.f + m_origin.x,
		m_backgroundContentSize.height * 8.5 / 10 + m_origin.y));
	spriteTitle->setScale(0.25);
	m_popupLayer->addChild(spriteTitle);
}

void PopUp::OnButtonClose(Ref* sender, Widget::TouchEventType type)
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

void PopUp::onExit()
{
	m_appearAction->release();
	m_disappearAction->release();
	Node::onExit();
}