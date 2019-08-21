#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "Box2D\Box2D.h"

USING_NS_CC;

class Stone :public GameObject
{
public:
	bool init() override;
	CREATE_FUNC(Stone);
	void CreateBody();
	void CreateBrokenStone();

	void SetStartAndDestinatePosition(Vec2 start, Vec2 destinate);
	void CreateAnimate();
	void Setb2World(b2World *world);
	void SetVisible() {
		this->setVisible(false);
	}
	void StopActionDrop() {
		this->stopAction(m_seq);
	}
	void SetParent(Node *node, Vec2 Position) {
		this->m_this = node;
		this->m_positionBroken = Position;
	}
	Vec2 GetStartFall() {
		return this->m_startFall;
	}
	Vec2 GetEndFall() {
		return this->m_destinateFall;
	}

	void RemoveStone() {
		this->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, 
			this->m_startFall.y + Director::getInstance()->getVisibleSize().height * 0.5));
	}
private:
	b2World *m_world;
	Vec2 m_startFall;
	Vec2 m_destinateFall;
	b2Body *m_b2body;
	b2PolygonShape m_bodyShape;
	b2BodyDef m_bodyDef;
	b2FixtureDef m_fixtureDef;
	b2Fixture *m_fixture;

	Sequence *m_seq;

	Node *m_this;
	Vec2 m_positionBroken;
};

