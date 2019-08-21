#include "PlotLayer2.h"

bool PlotLayer2::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (LayerColor::initWithColor(Color4B(0, 0, 0, 255), visibleSize.width, visibleSize.height) == false)
		return false;

	this->m_sprite = Sprite::createWithSpriteFrame(GameValue::getInstance()->GetPlot2(i)->getSpriteFrame());
	this->m_sprite->setPosition(visibleSize/2);
	this->m_sprite->setScale(0.9);
	this->addChild(this->m_sprite);

	i++;
	this->PlayPlot();

	this->SkipButton = Button::create("Images/skip.png", "Images/skip1.png");
	this->SkipButton->setScale(0.4);
	this->SkipButton->setPosition(Vec2(visibleSize.width - visibleSize.width*0.1, visibleSize.height *0.95));
	this->addChild(this->SkipButton);
	this->SkipButton->addTouchEventListener(CC_CALLBACK_2(PlotLayer2::OnButtonSkipTouch, this));

	return true;
}

void PlotLayer2::OnButtonSkipTouch(Ref * sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		Director::getInstance()->popScene();
	}
	break;
	}
}
void PlotLayer2::PlayPlot()
{
	this->m_sprite->runAction(Sequence::create(FadeIn::create(0.5), DelayTime::create(2), FadeOut::create(0.5), CallFunc::create(CC_CALLBACK_0(PlotLayer2::NextPic, this)), nullptr));
}

void PlotLayer2::NextPic()
{
	if (i <= Plot2 - 1)
	{
		this->m_sprite->setSpriteFrame(GameValue::getInstance()->GetPlot2(i)->getSpriteFrame());
		this->m_sprite->setScale(0.9);
		this->PlayPlot();
		i++;
	}
	else
	{
		Director::getInstance()->popScene();
	}

}
