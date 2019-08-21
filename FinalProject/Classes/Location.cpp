#include "Location.h"

bool Location::init()
{
	if (Node::init() == false)
		return false;

	this->m_spriteCircle = Sprite::createWithSpriteFrameName("icons8-circle-64.png");
	this->m_spriteCircle->setScale(1.5);
	this->addChild(this->m_spriteCircle);
	this->m_spriteCircle->setVisible(false);
	
	this->m_cancleCircle = Sprite::createWithSpriteFrameName("icons8-cancel-64.png");
	this->m_cancleCircle->setScale(1.5);
	this->addChild(this->m_cancleCircle);
	this->m_cancleCircle->setVisible(true);


	this->m_spriteArrow = Sprite::createWithSpriteFrameName("canva-arrow-icon-direction-button-pointer--MAB_Of-JV5A.png");
	this->m_spriteArrow->setOpacity(80);
	this->m_spriteArrow->setAnchorPoint(Vec2(0, 0.5));

	this->m_spriteArrow->setPosition(this->m_spriteCircle->getPosition().x + this->m_spriteCircle->getContentSize().width / 2, 0);

	this->m_spriteArrow->setScale(this->m_spriteCircle->getContentSize().width / this->m_spriteArrow->getContentSize().width);
	this->m_spriteArrow->setVisible(false);

	this->addChild(this->m_spriteArrow);
	return true;
}


void Location::SetScaleX(float scale)
{
	this->m_spriteArrow->setVisible(true);
	this->m_spriteArrow->setScaleX(scale);
}

void Location::ShowCancleCircle()
{
	this->m_spriteCircle->setVisible(false);
	this->m_spriteArrow->setVisible(false);
	this->m_cancleCircle->setVisible(true);
}

void Location::ShowCircle()
{
	this->m_cancleCircle->setVisible(false);
	this->m_spriteCircle->setVisible(true);
}
