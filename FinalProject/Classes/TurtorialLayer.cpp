#include "TurtorialLayer.h"

bool TurtorialLayer::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (LayerColor::initWithColor(Color4B(0, 0, 0, 255), visibleSize.width, visibleSize.height) == false)
		return false;

	this->m_sprite = Sprite::createWithSpriteFrame(GameValue::getInstance()->GetTurtorial(i)->getSpriteFrame());
	this->m_sprite->setPosition(visibleSize/2);
	this->addChild(this->m_sprite);

	this->PrevButton = Button::create("Images/prev.png","Images/prev1.png");
	this->PrevButton->setScale(0.4);
	this->PrevButton->setPosition(Vec2(visibleSize.width*0.0645 , visibleSize.height / 2 ));
	this->addChild(this->PrevButton);
	this->PrevButton->addTouchEventListener(CC_CALLBACK_2(TurtorialLayer::OnButtonPrevTouch, this));

	this->NextButton = Button::create("Images/next.png", "Images/next1.png");
	this->NextButton->setScale(0.4);
	this->NextButton->setPosition(Vec2(visibleSize.width-visibleSize.width*0.0645, visibleSize.height / 2));
	this->addChild(this->NextButton);
	this->NextButton->addTouchEventListener(CC_CALLBACK_2(TurtorialLayer::OnButtonNextTouch, this));

	this->SkipButton = Button::create("Images/skip.png", "Images/skip1.png");
	this->SkipButton->setScale(0.4);
	this->SkipButton->setPosition(Vec2(visibleSize.width - visibleSize.width*0.1, visibleSize.height *0.95));
	this->addChild(this->SkipButton);
	this->SkipButton->addTouchEventListener(CC_CALLBACK_2(TurtorialLayer::OnButtonSkipTouch, this));

	return true;
}

void TurtorialLayer::OnButtonPrevTouch(Ref * sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		if (i > 1)
		{
			i--;
			this->m_sprite->setSpriteFrame(GameValue::getInstance()->GetTurtorial(i)->getSpriteFrame());
		}
	}
	break;
	}
}

void TurtorialLayer::OnButtonNextTouch(Ref * sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		if (i < TurtorialNum - 1)
		{
			i++;
			this->m_sprite->setSpriteFrame(GameValue::getInstance()->GetTurtorial(i)->getSpriteFrame());
		}
	}
	break;
	}
}

void TurtorialLayer::OnButtonSkipTouch(Ref * sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		Director::getInstance()->replaceScene(MiddleScene::createScene(false));
	}
	break;
	}
}

