#include "Elevator.h"

bool Elevator::init()
{
	if (DynamicObject::init() == false)
		return false;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->m_sprite = Sprite::createWithSpriteFrameName("Elevator.png");
	this->m_sprite->setScaleY(32.f / this->m_sprite->getContentSize().height);
	this->m_sprite->setScaleX(8 * 16.f / this->m_sprite->getContentSize().width);
	this->addChild(this->m_sprite);

	this->m_spriteLever = Sprite::createWithSpriteFrameName("lever-5122.png");
	this->m_spriteLever->setPosition(0, visibleSize.height * 0.022);
	this->m_spriteLever->setScale(0.15);
	this->setScaleX(-1);
	this->addChild(this->m_spriteLever, -1);
	return true;
}

void Elevator::CreateBody(b2World* world)
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

	fixtureDef.isSensor = true;
	bodyShape.SetAsBox(this->m_sprite->getBoundingBox().size.width * 0.2 / (2 * PTM_RATIO), 0.2, 
		b2Vec2(0, (this->m_sprite->getBoundingBox().size.height / (2 * PTM_RATIO) + 0.01)), 0);

	b2Fixture* footSensorFixture = this->m_b2Body->CreateFixture(&fixtureDef);
	footSensorFixture->SetUserData(new TypeObject(IdButtonElevator, this));

	this->m_BodyIsDestroy = false;
}

void Elevator::RunActionMoveTo()
{
	this->setScaleX(1);
	this->runAction(MoveTo::create(m_timeRun, m_movePosition[0]));
}

void Elevator::RunActionMoveToEnd1()
{
	this->setScaleX(1);
	this->runAction(MoveTo::create(m_timeRun, m_movePosition[1]));
}

void Elevator::RunActionMoveToEnd2()
{
	this->setScaleX(1);
	this->runAction(MoveTo::create(m_timeRun, m_movePosition[1]));
}
