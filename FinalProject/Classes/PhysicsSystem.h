#pragma once
#include "Box2D/Box2D.h"
#include "PhysicsComponent.h"
#include "DynamicObject.h"

static const float PTM = 32.0f;
static const float FIXED_TIMESTEP = 1.0f / 60.0f;

class PhysicsSystem {
public:
	PhysicsSystem();
	//virtual ~PhysicsSystem(void);
	b2World* getWorld() { return this->world; }
	void update(const float deltaTime);
	void newUpdate(const float deltaTime);
	virtual void singleStep_(float dt);
	virtual void resetSmoothStates_();
	virtual void smoothStates_();
	b2Vec2 GetGravity() { return this->gravity; }
private:
	b2Vec2 gravity = b2Vec2(0.0f, -9.8f);
	b2World* world = nullptr;
	float fixedTimestepAccumulator_;
	float fixedTimestepAccumulatorRatio_;
	float velocityIterations_, positionIterations_;
	float _accumulator = 0;
};