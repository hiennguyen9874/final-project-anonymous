#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "Box2D\Box2D.h"
#include "Elevator.h"

USING_NS_CC;

class CheckPoint :public GameObject
{
public:
	bool init() override;
	CREATE_FUNC(CheckPoint);
	void CreateBody(b2World *world);
	void SetActive(bool active) { this->m_b2body->SetActive(active); }

	void SetElevator(Elevator *elevator) {
		this->m_ptrElevator = elevator;
	}
	Elevator *GetElevator() {
		return this->m_ptrElevator;
	}
private:
	b2Body *m_b2body;
	b2PolygonShape m_bodyShape;
	b2BodyDef m_bodyDef;
	b2FixtureDef m_fixtureDef;
	b2Fixture *m_fixture;

	RefPtr<Elevator> m_ptrElevator = nullptr;
};

