#pragma once
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "Player.h"
#include "Config.h"
#include "ObjectPool.h"

class TrajectoryRayCastClosestCallback : public b2RayCastCallback
{
public:
	TrajectoryRayCastClosestCallback(b2Body* ignoreBody) : m_hit(false), m_ignoreBody(ignoreBody) {}

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
	{
		if (fixture->GetBody() == m_ignoreBody)
			return -1;

		m_hit = true;
		m_point = point;
		m_normal = normal;
		return fraction;
	}

	b2Body* m_ignoreBody;
	bool m_hit;
	b2Vec2 m_point;
	b2Vec2 m_normal;
};

class RayCastClosestCallback : public b2RayCastCallback
{
public:
	RayCastClosestCallback()
	{
		m_hit = false;
	}

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
	{
		//b2Body* body = fixture->GetBody();
		//void* userData = body->GetUserData();
		//if (userData)
		//{
		//	int32 index = *(int32*)userData;
		//	if (index == 0)
		//	{
		//		return -1.0f;
		//	}
		//}

		m_hit = true;
		m_point = point;
		m_normal = normal;
		return fraction;
	}

	bool m_hit;
	b2Vec2 m_point;
	b2Vec2 m_normal;
};

class RayCastMultipleCallback : public b2RayCastCallback
{
public:
	enum
	{
		e_maxCount = 3
	};

	RayCastMultipleCallback()
	{
		m_count = 0;
	}

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
	{
		b2Body* body = fixture->GetBody();
		void* userData = body->GetUserData();
		if (userData)
		{
			int32 index = *(int32*)userData;
			if (index == 0)
			{

				return -1.0f;
			}
		}

		b2Assert(m_count < e_maxCount);

		m_points[m_count] = point;
		m_normals[m_count] = normal;
		++m_count;

		if (m_count == e_maxCount)
		{
			return 0.0f;
		}

		return 1.0f;
	}

	b2Vec2 m_points[e_maxCount];
	b2Vec2 m_normals[e_maxCount];
	int32 m_count;
};