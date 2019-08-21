#include "Gold.h"
#include "Config.h"

bool Gold::init()
{
	if (GameObject::init() == false)
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// TODO:14-8
	this->m_sprite = Sprite::createWithSpriteFrameName("Coin (1).png");
	//this->m_sprite->setPosition(0, visibleSize.height * 0.007);
	this->m_sprite->setScale(40 / this->m_sprite->getContentSize().height);

	const int numFrame = 16;
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numFrame);

	for (int i = 1; i <= numFrame; i++)
	{
		std::string name = "Coin (" + std::to_string(i) + ").png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	this->m_animation = Animation::createWithSpriteFrames(animFrames, 0.15f);
	this->m_animate = Animate::create(this->m_animation);
	this->m_sprite->runAction(RepeatForever::create(this->m_animate));

	this->addChild(this->m_sprite);
	return true;
}

void Gold::CreateBody(b2World * world)
{
	this->m_bodyShape.SetAsBox(this->m_sprite->getBoundingBox().size.width / (2 * PTM_RATIO), this->m_sprite->getBoundingBox().size.height / (2 * PTM_RATIO));

	this->m_bodyDef.type = b2_staticBody;
	this->m_bodyDef.position.Set(this->getPosition().x / 32.0f,
		this->getPosition().y / 32.0f);

	this->m_fixtureDef.shape = &this->m_bodyShape;
	this->m_fixtureDef.isSensor = true;

	this->m_b2body = world->CreateBody(&m_bodyDef);
	this->m_fixture = m_b2body->CreateFixture(&m_fixtureDef);
	this->m_fixture->SetUserData(new TypeObject(IdGold, this));
}

