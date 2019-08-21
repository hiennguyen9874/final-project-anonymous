#include "CheckPoint.h"
#include "Config.h"

bool CheckPoint::init()
{
	if (GameObject::init() == false)
		return false;

	this->m_sprite = Sprite::createWithSpriteFrameName("CheckPoint.png");
	//this->m_sprite->setAnchorPoint(Vec2(0, 0.25));
	this->m_sprite->setScale(0.25);

	//const int numFrame = 9;
	//Vector<SpriteFrame*> animFrames;
	//animFrames.reserve(numFrame);

	//for (int i = 1; i <= numFrame; i++)
	//{
	//	std::string name = "Flags (" + std::to_string(i) + ").png";
	//	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	//}

	//this->m_animation = Animation::createWithSpriteFrames(animFrames, 0.15f);
	//this->m_animate = Animate::create(this->m_animation);
	//this->m_sprite->runAction(RepeatForever::create(this->m_animate));

	this->addChild(this->m_sprite);

	return true;
}

void CheckPoint::CreateBody(b2World * world)
{
	this->m_bodyShape.SetAsBox(this->m_sprite->getBoundingBox().size.width / (2 * PTM_RATIO),
		this->m_sprite->getBoundingBox().size.height / (2 * PTM_RATIO));

	this->m_bodyDef.type = b2_staticBody;
	this->m_bodyDef.userData = this;
	this->m_bodyDef.position.Set(this->getPosition().x / 32.0f,
		this->getPosition().y / 32.0f);

	this->m_fixtureDef.shape = &this->m_bodyShape;
	this->m_fixtureDef.isSensor = true;

	this->m_b2body = world->CreateBody(&m_bodyDef);
	this->m_fixture = m_b2body->CreateFixture(&m_fixtureDef);
	this->m_fixture->SetUserData(new TypeObject(IdCheckPoint, this));
}

