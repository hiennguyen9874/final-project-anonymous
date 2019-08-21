#include "ContacListenerSimulate.h"
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "GameObject.h"
#include "CheckPoint.h"
#include "Player.h"
#include "Gold.h"
#include "TreasureChest.h"
#include "Enemy.h"
#include "GameValue.h"


void ContacListenerSimulate::BeginContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	TypeObject* oA = (TypeObject*)contact->GetFixtureA()->GetUserData();
	TypeObject* oB = (TypeObject*)contact->GetFixtureB()->GetUserData();

	if (oA != nullptr && oA->idObject == FootSensorSimulateBody)
	{
		this->m_numOfContact++;
	}
	if (oB != nullptr && oB->idObject == FootSensorSimulateBody)
	{
		this->m_numOfContact++;
	}

	if ((oA != nullptr && oA->idObject == HandSensorSimulateBody) && !this->CanJump() && fixtureB->GetFilterData().categoryBits == 0x05)
	{
		this->m_isBoucing = true;
	}
	if ((oB != nullptr && oB->idObject == HandSensorSimulateBody) && !this->CanJump() && fixtureA->GetFilterData().categoryBits == 0x05)
	{
		this->m_isBoucing = true;
	}
}

void ContacListenerSimulate::EndContact(b2Contact * contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	TypeObject* oA = (TypeObject*)contact->GetFixtureA()->GetUserData();
	TypeObject* oB = (TypeObject*)contact->GetFixtureB()->GetUserData();

	if (oA != nullptr && oA->idObject == FootSensorSimulateBody)
		this->m_numOfContact--;
	if (oB != nullptr && oB->idObject == FootSensorSimulateBody)
		this->m_numOfContact--;
}

void ContacListenerSimulate::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if ((fixtureA->GetFilterData().categoryBits == 0x99 && fixtureB->GetFilterData().categoryBits == 0x05))
		this->m_linearVelocityPlayer = fixtureA->GetBody()->GetLinearVelocity();

	if ((fixtureB->GetFilterData().categoryBits == 0x99 && fixtureA->GetFilterData().categoryBits == 0x05) ||
		(fixtureB->GetFilterData().categoryBits == 0x99 && fixtureA->GetFilterData().categoryBits == 0x06))
		this->m_linearVelocityPlayer = fixtureB->GetBody()->GetLinearVelocity();
}

bool ContacListenerSimulate::CheckBoucing()
{
	return this->m_isBoucing;
}

void ContacListenerSimulate::ReFalseIsBoucing()
{
	this->m_isBoucing = false;
}

bool ContacListenerSimulate::CanJump()
{
	if (this->m_numOfContact < 1)
		return false;
	return true;
}
