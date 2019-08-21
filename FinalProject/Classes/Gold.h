#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "Box2D\Box2D.h"

USING_NS_CC;

class Gold :public GameObject
{
public:
	bool init() override;
	CREATE_FUNC(Gold);
	void CreateBody(b2World *world);
	void SetActive(bool active) {
		this->m_b2body->SetActive(active);
	}
private:
	b2Body *m_b2body;
	b2PolygonShape m_bodyShape;
	b2BodyDef m_bodyDef;
	b2FixtureDef m_fixtureDef;
	b2Fixture *m_fixture;
public:
	int m_indexPath = -1;
	int m_numCoinInPath = -1;
};

