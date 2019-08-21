#include "EndLayer.h"

bool EndLayer::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (LayerColor::initWithColor(Color4B(0, 0, 0, 255), visibleSize.width, visibleSize.height) == false)
		return false;

	this->m_sprite = Sprite::createWithSpriteFrame(GameValue::getInstance()->GetEnd(i)->getSpriteFrame());
	this->m_sprite->setPosition(visibleSize/2);
	this->addChild(this->m_sprite);
	i++;

	this->PlayPlot();

	this->SkipButton = Button::create("Images/skip.png", "Images/skip1.png");
	this->SkipButton->setScale(0.4);
	this->SkipButton->setPosition(Vec2(visibleSize.width - visibleSize.width*0.1, visibleSize.height *0.95));
	this->addChild(this->SkipButton);
	this->SkipButton->addTouchEventListener(CC_CALLBACK_2(EndLayer::OnButtonSkipTouch, this));

	return true;
}

void EndLayer::OnButtonSkipTouch(Ref * sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		auto *scene = MainMenuScene::create();
		Director::getInstance()->replaceScene(TransitionFade::create(0.3,scene));
	}
	break;
	}
}

void EndLayer::PlayPlot()
{
	this->m_sprite->runAction(Sequence::create(FadeIn::create(0.5), DelayTime::create(2), FadeOut::create(0.5), CallFunc::create(CC_CALLBACK_0(EndLayer::NextPic, this)), nullptr));
}

void EndLayer::NextPic()
{
	if (i <= EndLayerImages - 1)
	{
		this->m_sprite->setSpriteFrame(GameValue::getInstance()->GetEnd(i)->getSpriteFrame());
		this->PlayPlot();
		i++;
	}
	else
	{
		auto *scene = MainMenuScene::create();
		Director::getInstance()->replaceScene(TransitionFade::create(0.3, scene));
	}

}

