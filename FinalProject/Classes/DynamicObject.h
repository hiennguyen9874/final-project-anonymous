#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "Box2D\Box2D.h"
#include "PhysicsComponent.h"
#include "Config.h"

USING_NS_CC;

class DynamicObject :public GameObject
{
public:
	bool init() override;
	CREATE_FUNC(DynamicObject);
	
	virtual void CreateBody(b2World* world) {
		this->m_BodyIsDestroy = false;
	}

	virtual void DestroyBody(b2World *world) {
		if (this->m_BodyIsDestroy == true)
			return;
		world->DestroyBody(this->m_b2Body);
		this->m_BodyIsDestroy = true;
	}
	Vec2 GetSizeBodyShape() {
		return Vec2(this->m_sprite->getBoundingBox().size.width / (2 * PTM_RATIO),
			this->m_sprite->getBoundingBox().size.height / (2 * PTM_RATIO));
	}
	b2Body* GetB2Body() {
		return this->m_b2Body;
	}
protected:
	b2Fixture *m_fixture;
	b2Body* m_b2Body;
	bool m_BodyIsDestroy = false;
};
