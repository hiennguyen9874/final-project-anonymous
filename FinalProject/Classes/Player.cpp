#include "Player.h"
#include "../libs/GB2ShapeCache-x.h"

bool Player::init()
{
	if (GameObject::init() == false)
		return false;

	this->m_sprite = Sprite::createWithSpriteFrameName("character_idle (1).png");
	this->m_sprite->setScale(0.3);
	this->addChild(this->m_sprite);

	this->m_iNumberSprite = 20;
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(this->m_iNumberSprite);
	for (int i = 1; i < this->m_iNumberSprite; i++)
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("character_idle (" + std::to_string(i) + ").png"));
	this->m_animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
	this->m_animate = Animate::create(this->m_animation);

	this->m_iNumberFrameFly = 10;
	Vector<SpriteFrame*> animFramesFly;
	animFramesFly.reserve(this->m_iNumberFrameFly);
	for (int i = 1; i < this->m_iNumberFrameFly; i++)
		animFramesFly.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("character_fly (" + std::to_string(i) + ").png"));
	this->m_animationFly = Animation::createWithSpriteFrames(animFramesFly, 0.05f);
	this->m_animateFly = Animate::create(this->m_animationFly);
	
	this->RunIdleAnimation();
	return true;
}

Size Player::GetPlayerSize()
{
	return this->m_sprite->getBoundingBox().size;
}

void Player::CreateBody(b2World * world, bool isGravity)
{
	b2PolygonShape bodyShape;
	bodyShape.SetAsBox(this->m_sprite->getBoundingBox().size.width / (2 * PTM_RATIO),
		this->m_sprite->getBoundingBox().size.height / (2 * PTM_RATIO));

	b2FixtureDef fixtureDef;			
	fixtureDef.density = 10;			
	fixtureDef.friction = 0.3;
	fixtureDef.restitution = 0;
	fixtureDef.shape = &bodyShape;
	fixtureDef.filter.categoryBits = 0x98;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.userData = this;
	bodyDef.position.Set(this->getPosition().x / PTM_RATIO, this->getPosition().y / PTM_RATIO);

	this->m_b2Body = world->CreateBody(&bodyDef);

	this->m_b2Body->SetFixedRotation(true);
	if (isGravity == true)
		this->m_b2Body->SetGravityScale(10);

	this->m_fixture = this->GetB2Body()->CreateFixture(&fixtureDef);
	this->m_fixture->SetUserData(new TypeObject(IdBodyPlayer, this));

	// Chan cua character
	fixtureDef.isSensor = true;
	bodyShape.SetAsBox(this->m_sprite->getBoundingBox().size.width * 0.9 / (2 * PTM_RATIO), 0.2, b2Vec2(0, -(this->m_sprite->getBoundingBox().size.height / (2 * PTM_RATIO) + 0.01)), 0);
	b2Fixture* footSensorFixture = this->m_b2Body->CreateFixture(&fixtureDef);
	footSensorFixture->SetUserData(new TypeObject(IdChanPlayer, this));

	// Tay trai
	bodyShape.SetAsBox(0.1, 0.46, b2Vec2(this->m_sprite->getBoundingBox().size.width / (2 * PTM_RATIO) + 0.04, 0), 0);
	b2Fixture* leftHandSensorFixture = this->m_b2Body->CreateFixture(&fixtureDef);
	leftHandSensorFixture->SetUserData(new TypeObject(IdTayPlayer, this));

	// Tay phai
	bodyShape.SetAsBox(0.1, 0.46, b2Vec2(-(this->m_sprite->getBoundingBox().size.width / (2 * PTM_RATIO) + 0.04), 0), 0);
	b2Fixture* rightHandSensorFixture = this->m_b2Body->CreateFixture(&fixtureDef);
	rightHandSensorFixture->SetUserData(new TypeObject(IdTayPlayer, this));

	// Dau cua character
	fixtureDef.isSensor = true;
	bodyShape.SetAsBox(this->m_sprite->getBoundingBox().size.width * 0.9 / (2 * PTM_RATIO), 0.2, b2Vec2(0, (this->m_sprite->getBoundingBox().size.height / (2 * PTM_RATIO) + 0.01)), 0);
	b2Fixture* DSensorFixture = this->m_b2Body->CreateFixture(&fixtureDef);
	DSensorFixture->SetUserData(new TypeObject(IdDauPlayer, this));

	this->m_BodyIsDestroy = false;
}


