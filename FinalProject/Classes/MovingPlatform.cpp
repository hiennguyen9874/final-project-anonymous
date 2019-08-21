#include "MovingPlatform.h"

bool MovingPlatform::init()
{
	if (DynamicObject::init() == false)
		return false;
	this->m_sprite = Sprite::createWithSpriteFrameName("MovingPlatform.png");
	this->addChild(this->m_sprite);
	return true;
}

void MovingPlatform::CreateBody(b2World* world)
{
	b2PolygonShape bodyShape;
	bodyShape.SetAsBox(this->GetSizeBodyShape().x, this->GetSizeBodyShape().y);

	b2FixtureDef fixtureDef;
	fixtureDef.density = Density_Collision;
	fixtureDef.friction = Friction_Collision;
	fixtureDef.restitution = 0.01;
	fixtureDef.shape = &bodyShape;

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.userData = this;
	bodyDef.position.Set(this->getPosition().x / 32.0f, this->getPosition().y / 32.0f);

	this->m_b2Body = world->CreateBody(&bodyDef);
	this->m_fixture = this->m_b2Body->CreateFixture(&fixtureDef);
	this->m_fixture->SetUserData(new TypeObject(IdMovingPlatfrom, this));

	this->m_BodyIsDestroy = false;
}

void MovingPlatform::RunActionMoveTo()
{
	Vector<FiniteTimeAction*> arrayOfActions;
	for (int i = 0; i < this->m_movePosition.size(); i++)
	{
		arrayOfActions.pushBack(MoveTo::create(m_timeRun, this->m_movePosition[i]));
		arrayOfActions.pushBack(DelayTime::create(m_timeDelay));
	}
	auto sequence = RepeatForever::create(Sequence::create(arrayOfActions));
	this->runAction(sequence);
}