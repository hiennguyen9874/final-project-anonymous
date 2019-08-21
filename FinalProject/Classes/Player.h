#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "Box2D\Box2D.h"
#include "PhysicsComponent.h"
#include "DynamicObject.h"
#include "Config.h"

USING_NS_CC;

class Player :public DynamicObject
{
public:
	bool init() override;
	CREATE_FUNC(Player);
	Size GetPlayerSize();
	void CreateBody(b2World* world, bool isGravity);

	void RunIdleAnimation() {
		this->m_sprite->stopAllActions();
		this->m_sprite->runAction(RepeatForever::create(this->m_animate));
	}
	void RunFlyAnimation() {
		this->m_sprite->stopAllActions();
		this->m_sprite->runAction(RepeatForever::create(this->m_animateFly));
	}
	bool m_movePositionPlayer = false;
private:
	int m_iNumberFrameFly;
	RefPtr<Animation> m_animationFly;
	RefPtr<Animate> m_animateFly;

};
