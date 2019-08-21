#include "Archievement.h"

bool Archivement::init()
{
	if (GameObject::init() == false)
		return false;

	this->m_sprite = Sprite::createWithSpriteFrameName("Wood_sign.png");
	this->addChild(this->m_sprite);
	this->m_sprite->setScaleY(0.9);
	this->m_label = Label::createWithTTF("", "fonts/retro_computer_personal_use.ttf", 28);
	this->m_label->setAlignment(TextHAlignment::CENTER);
	this->addChild(this->m_label);
	this->m_sprite->setPosition(-500,-500);
	this->m_label->setPosition(-500,-500);
	return true;
}

void Archivement::setStringForLabel(std::string labelString)
{
	this->m_label->setString(labelString);
}

void Archivement::setPositionForAll(Vec2 position)
{
	this->m_sprite->setPosition(position);
	this->m_label->setPosition(position);
}

void Archivement::RunAction()
{
	Sequence* seq1 = Sequence::create(FadeIn::create(0.5),DelayTime::create(1.5),FadeOut::create(1),NULL);
	this->m_sprite->runAction(seq1);
	Sequence* seq2 = Sequence::create(FadeIn::create(0.5), DelayTime::create(1.5), FadeOut::create(1), NULL);
	this->m_label->runAction(seq2);
}


