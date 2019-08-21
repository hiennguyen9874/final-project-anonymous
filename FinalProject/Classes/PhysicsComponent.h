#pragma once
#include "Box2D/Box2D.h"
#include "cocos2d.h"

class PhysicsComponent
{
public:
	b2Body* m_b2Body;
	b2Vec2 smoothedPosition_;
	float smoothedAngle_;
	b2Vec2 previousPosition_;
	float previousAngle_;
};

