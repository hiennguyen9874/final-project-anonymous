#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "Box2D\Box2D.h"
#include "PhysicsComponent.h"
#include "DynamicObject.h"
#include "Config.h"
#include "Utils.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class Boss :public DynamicObject
{
public:
	bool init() override;
	CREATE_FUNC(Boss);
	void CreateBody(b2World *world);
	void RunActionMoveTo();
	void Dead() {
		this->setVisible(false);
	}
public:
	bool RunAttackAniamtion(bool repeatForever);
	bool RunDeadAnimation();
	bool RunHurtAniamtion(bool repeatForever);
	bool RunIdleAniamtion();
	bool RunJumpAnimation(bool repeatForever);
	bool RunRunAnimation(bool repeatForever);
	bool RunWalkAnimation(bool repeatForever);
	void BeginRun() {
		this->m_sprite->setScaleX(-this->m_sprite->getScaleX());
		this->m_sprite->stopAllActions();
		this->RunWalkAnimation(true);
	}
	void EndRun() {
		this->m_sprite->stopAllActions();
		this->RunIdleAniamtion();
	}

	void SetPercent(float percent) {
		if (percent <= 0)
			this->m_percentHp = 0;
		else
			this->m_percentHp = percent;
		m_bloodBar->setScaleX((0.4 + 0.6 * percent) * m_bloodBarBG->getScaleX());
	}

	float GetPercentHp() {
		return this->m_percentHp;
	}
	void Attack()
	{
		this->m_sprite->setScale(0.2);
		this->stopActionByTag(12);
		this->m_sprite->stopAllActions();
		auto seq = Sequence::create(this->m_AnimateAttack->clone(),
			CallFunc::create(CC_CALLBACK_0(Boss::RunActionMoveTo, this)), nullptr);
		seq->setTag(13);
		this->m_sprite->runAction(seq);
	}

	bool isDead() {
		return this->m_isDead;
	}
public:
	std::vector<Vec2> m_movePosition;
	float m_timeRun = 0;
	float m_timeDelay = 0;
private:
	Animate *m_AnimateAttack = nullptr;
	Animation *m_AnimationAttack = nullptr;

	Animate *m_AnimateDead = nullptr;
	Animation *m_AnimationDead = nullptr;

	Animate *m_AnimateHurt = nullptr;
	Animation *m_AnimationHurt = nullptr;

	Animate *m_AnimateIdle = nullptr;
	Animation *m_AnimationIdle = nullptr;

	Animate *m_AnimateJump = nullptr;
	Animation *m_AnimationJump = nullptr;

	Animate *m_AnimateRun = nullptr;
	Animation *m_AnimationRun = nullptr;

	Animate *m_AnimateWalk = nullptr;
	Animation *m_AnimationWalk = nullptr;

private:
	b2PolygonShape m_bodyShape;

	RefPtr<Sprite> m_bloodBarBG;
	RefPtr<Sprite> m_bloodBar;
	RefPtr<Sprite> m_spriteTim;
	float m_percentHp = 1;

	RepeatForever *m_seq;
	bool m_isDead = false;
protected:
	void AddAttackAnimation(int numFrame);
	void AddDeadAnimation(int numFrame);
	void AddHurtAnimation(int numFrame);
	void AddIdleAnimation(int numFrame);
	void AddJumpAnimation(int numFrame);
	void AddRunAnimation(int numFrame);
	void AddWalkAnimation(int numFrame);
};
