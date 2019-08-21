#include "SlingShot.h"

bool SlingShot::init()
{
	if (GameObject::init() == false)
		return false;

	this->m_sprite = Sprite::createWithSpriteFrameName("slingshot0-2.png");
	this->m_sprite->setScale(0.05);
	this->m_sprite->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(this->m_sprite);

	return true;
}

void SlingShot::SetImageSlingShot(int indexSlingshot)
{
	if (indexSlingshot == 0)
		this->m_sprite->setSpriteFrame("slingshot0-2.png");
	else if (indexSlingshot == 1)
		this->m_sprite->setSpriteFrame("slingshot1-2.png");
	else if (indexSlingshot == 2)
		this->m_sprite->setSpriteFrame("slingshot2-2.png");
	else if (indexSlingshot == 3)
		this->m_sprite->setSpriteFrame("slingshot3-2.png");
	this->m_sprite->setScale(0.05);
	this->m_sprite->setAnchorPoint(Vec2(0.5, 0));
}



