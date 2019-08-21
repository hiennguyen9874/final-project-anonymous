#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "Box2D\Box2D.h"
#include "PhysicsComponent.h"
#include "DynamicObject.h"
#include "Config.h"
#include "Utils.h"

USING_NS_CC;

class Elevator :public DynamicObject
{
public:
	bool init() override;
	CREATE_FUNC(Elevator);

	void CreateBody(b2World *world);
	void RunActionMoveTo();
	void RunActionMoveToEnd1();
	void RunActionMoveToEnd2();

	//bool GetScheduleUpdate() {
	//	return this->m_bScheduleUpdate;
	//}
	//void SetScheduleUpdateToTrue() {
	//	this->m_bScheduleUpdate = true;
	//}
	float GetTimeRun() {
		return this->m_timeRun;
	}
public:
	std::vector<Vec2> m_movePosition;
	float m_timeRun = 0;
	bool m_bool = false;
protected:
	RefPtr<Sprite> m_spriteLever;
};
