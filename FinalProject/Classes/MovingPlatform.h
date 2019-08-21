#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "Box2D\Box2D.h"
#include "PhysicsComponent.h"
#include "DynamicObject.h"
#include "Config.h"
#include "Utils.h"

USING_NS_CC;

class MovingPlatform :public DynamicObject
{
public:
	bool init() override;
	CREATE_FUNC(MovingPlatform);

	void CreateBody(b2World *world);
	void RunActionMoveTo();
public:
	std::vector<Vec2> m_movePosition;
	float m_timeRun = 0;
	float m_timeDelay = 0;
protected:
};
