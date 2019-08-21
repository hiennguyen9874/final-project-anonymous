#include "Wind.h"

bool Wind::init()
{
	if (Node::init() == false)
		return false;
	this->m_sprite = Sprite::createWithSpriteFrameName("Untitled-1.png");
	this->m_sprite->setOpacity(150);
	this->addChild(this->m_sprite);

	const int numFrame = 11;
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numFrame);

	for (int i = 1; i <= numFrame; i++)
	{
		std::string name = "Untitled-" + std::to_string(i) + ".png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	this->m_animation = Animation::createWithSpriteFrames(animFrames, 1 / 5.0f);
	this->m_animate = Animate::create(this->m_animation);

	this->m_sprite->runAction(RepeatForever::create(this->m_animate));
	return true;
}

