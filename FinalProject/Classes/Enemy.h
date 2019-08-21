#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "Box2D\Box2D.h"
#include "PhysicsComponent.h"
#include "DynamicObject.h"
#include "Config.h"
#include "Utils.h"

USING_NS_CC;

class Enemy :public DynamicObject
{
public:
	bool init() override;
	CREATE_FUNC(Enemy);
	bool InitWithType(TypeEnemy ty);
	static Enemy* createWithType(TypeEnemy ty);

	Size GetPlayerSize();
	Sprite *GetSprite();
	void CreateBody(b2World *world);
	bool RunAttackAniamtion(bool repeatForever);
	bool RunDeadAnimation();
	bool RunIdleAniamtion(bool repeatForever);
	bool RunWalkAnimation(bool repeatForever);
	bool RunFlyAnimation(bool repeatForever);
	void RunActionMoveTo(int xc);
	void Dead();
public:
	std::vector<Vec2> m_movePosition;
	float m_timeRun = 0;
	float m_timeDelay = 0;
private:
	void BeginRun() {
		this->setScaleX(-this->getScaleX());
		if (m_type == TypeEnemy::ENEMY_1 || m_type == TypeEnemy::ENEMY_2 || m_type == TypeEnemy::ENEMY_4)
		{	
			this->m_sprite->stopAllActions();
			this->RunWalkAnimation(true);
		}
	}
	void EndRun() {
		if (m_type == TypeEnemy::ENEMY_1 || m_type == TypeEnemy::ENEMY_2 || m_type == TypeEnemy::ENEMY_4)
		{
			this->m_sprite->stopAllActions();
			this->RunIdleAniamtion(true);
		}
	}
protected:
	Animate *m_AnimateAttack = nullptr;
	Animation *m_AnimationAttack = nullptr;

	Animate *m_AnimateDead = nullptr;
	Animation *m_AnimationDead = nullptr;

	Animate *m_AnimateIdle = nullptr;
	Animation *m_AnimationIdle = nullptr;

	Animate *m_AnimateWalk = nullptr;
	Animation *m_AnimationWalk = nullptr;

	Animate *m_AnimateFly = nullptr;
	Animation *m_AnimationFly = nullptr;
	TypeEnemy m_type;
	b2PolygonShape m_bodyShape;
protected:
	void AddAttackAnimation(int tyEnemy, int numFrame);
	void AddDeadAnimation(int tyEnemy, int numFrame);
	void AddIdleAnimation(int tyEnemy, int numFrame);
	void AddWalkAnimation(int tyEnemy, int numFrame);
	void AddFlyAnimation(int tyEnemy, int numFrame);
};
