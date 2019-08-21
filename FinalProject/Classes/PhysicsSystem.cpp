#include "PhysicsSystem.h"
#include "cocos2d.h"
#include "GameObject.h"
#include "Utils.h"
#include "Config.h"
#include "Player.h"

using namespace cocos2d;

PhysicsSystem::PhysicsSystem() : fixedTimestepAccumulator_(0), fixedTimestepAccumulatorRatio_(0), 
	velocityIterations_(8), positionIterations_(8)
{
	this->world = new b2World(gravity);
	this->world->SetAutoClearForces(false);
}

void PhysicsSystem::update(const float deltaTime)
{
	this->world->Step(FIXED_TIMESTEP, 8, 1);
	for (b2Body* body = world->GetBodyList(); body != NULL; body = body->GetNext())
	{
		if (body->GetType() != b2_staticBody && body->GetUserData())
		{
			bool isEnemy = false;
			for (b2Fixture* fixture = body->GetFixtureList(); fixture != NULL; fixture = fixture->GetNext())
			{
				TypeObject* oT = (TypeObject*)fixture->GetUserData();
				if (oT != nullptr && (oT->idObject == IdEnemy || oT->idObject == IdBoss || oT->idObject == IdStone))
				{
					isEnemy = true;
					break;
				}
				if (oT != nullptr && (oT->idObject == IdBodyPlayer))
				{
					Player *player = (Player *)oT->ptr;
					if (player->m_movePositionPlayer == true)
						isEnemy = true;
					else 
						isEnemy = false;
				}
			}
			Node* sprite = (Node*)body->GetUserData();
			if (isEnemy)
				body->SetTransform(Vec2ToB2Vec2(sprite->getPosition()), 0);
			else
				sprite->setPosition(b2VecToVec2(body->GetPosition()));
		}
		else if (body->GetType() == b2_staticBody)
		{
			bool isEnemy = false;
			for (b2Fixture* fixture = body->GetFixtureList(); fixture != NULL; fixture = fixture->GetNext())
			{
				TypeObject* oT = (TypeObject*)fixture->GetUserData();
				if (oT != nullptr && (oT->idObject == IdMovingPlatfrom || oT->idObject == IdButtonElevator /*|| oT->idObject == IdCheckPoint*/))
				{
					isEnemy = true;
					break;
				}
			}
			Node* sprite = (Node*)body->GetUserData();
			if (isEnemy)
				body->SetTransform(Vec2ToB2Vec2(sprite->getPosition()), 0);
		}
	}
	world->ClearForces();
	world->DrawDebugData();
}

void PhysicsSystem::newUpdate(const float dt)
{
	// Maximum number of steps, to avoid degrading to an halt.
	const int MAX_STEPS = 5;

	fixedTimestepAccumulator_ += dt;
	const int nSteps = static_cast<int> (
		std::floor(fixedTimestepAccumulator_ / FIXED_TIMESTEP)
		);
	// To avoid rounding errors, touches fixedTimestepAccumulator_ only
	// if needed.
	if (nSteps > 0)
	{
		fixedTimestepAccumulator_ -= nSteps * FIXED_TIMESTEP;
	}

	assert(
		"Accumulator must have a value lesser than the fixed time step" &&
		fixedTimestepAccumulator_ < FIXED_TIMESTEP + FLT_EPSILON
	);
	fixedTimestepAccumulatorRatio_ = fixedTimestepAccumulator_ / FIXED_TIMESTEP;

	// This is similar to clamp "dt":
	//	dt = std::min (dt, MAX_STEPS * FIXED_TIMESTEP)
	// but it allows above calculations of fixedTimestepAccumulator_ and
	// fixedTimestepAccumulatorRatio_ to remain unchanged.
	const int nStepsClamped = std::min(nSteps, MAX_STEPS);
	for (int i = 0; i < nStepsClamped; ++i)
	{
		// In singleStep_() the CollisionManager could fire custom
		// callbacks that uses the smoothed states. So we must be sure
		// to reset them correctly before firing the callbacks.
		resetSmoothStates_();
		singleStep_(FIXED_TIMESTEP);
	}

	this->world->ClearForces();

	// We "smooth" positions and orientations using
	// fixedTimestepAccumulatorRatio_ (alpha).
	smoothStates_();
}

void PhysicsSystem::singleStep_(float dt)
{
	// ...

	// updateControllers_(dt);
	this->world->Step(dt, velocityIterations_, positionIterations_);
	// consumeContacts_();

	// ...
}

void PhysicsSystem::smoothStates_()
{
	const float oneMinusRatio = 1.f - fixedTimestepAccumulatorRatio_;

	for (b2Body* b = this->world->GetBodyList(); b != NULL; b = b->GetNext())
	{
		if (b->GetType() == b2_staticBody)
		{
			continue;
		}
		//DynamicObject* object = (DynamicObject*)b->GetUserData();
		//object->GetPhysicBody()->smoothedPosition_ =
		//	fixedTimestepAccumulatorRatio_ * b->GetPosition() +
		//	oneMinusRatio * object->GetPhysicBody()->previousPosition_;
		//object->GetPhysicBody()->smoothedAngle_ =
		//	fixedTimestepAccumulatorRatio_ * b->GetAngle() +
		//	oneMinusRatio * object->GetPhysicBody()->previousAngle_;
	}
}

void PhysicsSystem::resetSmoothStates_()
{
	for (b2Body* b = this->world->GetBodyList(); b != NULL; b = b->GetNext())
	{
		if (b->GetType() == b2_staticBody)
		{
			continue;
		}

		//DynamicObject* object = (DynamicObject*)b->GetUserData();
		//object->GetPhysicBody()->smoothedPosition_ = object->GetPhysicBody()->previousPosition_ = b->GetPosition();
		//object->GetPhysicBody()->smoothedAngle_ = object->GetPhysicBody()->previousAngle_ = b->GetAngle();
	}
}

