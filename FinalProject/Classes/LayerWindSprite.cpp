#include "LayerWindSprite.h"

bool LayerWindSprite::init()
{
	if (LayerColor::initWithColor(Color4B(0, 0, 0, 0), Director::getInstance()->getVisibleSize().width,1555) == false)
		return false;
		this->m_windSprite = Sprite::createWithSpriteFrameName("Wind1.png");
		this->m_windSprite->setAnchorPoint(Vec2(0, 0));
		this->addChild(this->m_windSprite);

	return true;
}

