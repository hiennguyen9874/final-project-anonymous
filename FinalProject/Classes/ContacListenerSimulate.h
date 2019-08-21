#pragma once
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "GameObject.h"

USING_NS_CC;
using namespace std;

class ContacListenerSimulate : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	bool CheckBoucing();
	void ReFalseIsBoucing();
	b2Vec2 GetLinearVelocity() { return this->m_linearVelocityPlayer; }
	bool CanJump();

private:
	bool m_isBoucing = false;
	b2Vec2 m_linearVelocityPlayer;
	int m_numOfContact;
};

