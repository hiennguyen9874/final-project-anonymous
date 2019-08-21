#include "Enemy.h"

bool Enemy::init()
{
	if (GameObject::init() == false)
		return false;
	return true;
}

bool Enemy::InitWithType(TypeEnemy ty)
{
	switch (ty)
	{
	case ENEMY_1:
		this->m_sprite = Sprite::createWithSpriteFrameName("Enemy1_Idle (1).png");
		this->m_sprite->setScale(0.12);
		m_bodyShape.SetAsBox(this->m_sprite->getBoundingBox().size.width * 0.65 / (2 * PTM_RATIO),
			this->m_sprite->getBoundingBox().size.height * 0.6 / (2 * PTM_RATIO), b2Vec2(-0.1, -0.37), 0);
		this->addChild(this->m_sprite);
		Enemy::AddAttackAnimation(1, 7);
		Enemy::AddDeadAnimation(1, 5);
		Enemy::AddIdleAnimation(1, 6);
		Enemy::AddWalkAnimation(1, 9);
		this->RunIdleAniamtion(true);
		m_type = ty;
		return true;
	case ENEMY_2:
		this->m_sprite = Sprite::createWithSpriteFrameName("Enemy2_Idle (1).png");
		this->m_sprite->setScale(0.25);
		m_bodyShape.SetAsBox(this->m_sprite->getBoundingBox().size.width / (2 * PTM_RATIO),
			this->m_sprite->getBoundingBox().size.height * 0.8 / (2 * PTM_RATIO), b2Vec2(0, 0.3), 0);
		this->addChild(this->m_sprite);
		Enemy::AddDeadAnimation(2, 7);
		Enemy::AddIdleAnimation(2, 6);
		Enemy::AddWalkAnimation(2, 6);
		this->RunIdleAniamtion(true);
		m_type = ty;
		return true;
	case ENEMY_3:
		this->m_sprite = Sprite::createWithSpriteFrameName("Enemy3_Fly (1).png");
		this->addChild(this->m_sprite);
		this->m_sprite->setScale(0.25);
		m_bodyShape.SetAsBox(this->m_sprite->getBoundingBox().size.width / (2 * PTM_RATIO),
			this->m_sprite->getBoundingBox().size.height / (2 * PTM_RATIO));
		Enemy::AddDeadAnimation(3, 6);
		Enemy::AddFlyAnimation(3, 4);
		this->RunFlyAnimation(true);
		m_type = ty;
		return true;
	case ENEMY_4:
		this->m_sprite = Sprite::createWithSpriteFrameName("Enemy4_Idle (1).png");
		this->addChild(this->m_sprite);
		this->m_sprite->setScale(0.25);
		m_bodyShape.SetAsBox(this->m_sprite->getBoundingBox().size.width * 0.65 / (2 * PTM_RATIO),
			this->m_sprite->getBoundingBox().size.height * 0.5 / (2 * PTM_RATIO), b2Vec2(0, -0.2), 0);
		Enemy::AddAttackAnimation(4, 6);
		Enemy::AddDeadAnimation(4, 7);
		Enemy::AddIdleAnimation(4, 6);
		Enemy::AddWalkAnimation(4, 8);
		this->RunIdleAniamtion(true);
		m_type = ty;
		return true;
	case ENEMY_5:
		this->m_sprite = Sprite::createWithSpriteFrameName("Enemy5_Fly (1).png");
		this->m_sprite->setScale(0.2);
		m_bodyShape.SetAsBox(this->m_sprite->getBoundingBox().size.width * 0.8 / (2 * PTM_RATIO),
			this->m_sprite->getBoundingBox().size.height * 0.8 / (2 * PTM_RATIO));
		this->addChild(this->m_sprite);
		Enemy::AddAttackAnimation(5, 7);
		Enemy::AddDeadAnimation(5, 5);
		Enemy::AddFlyAnimation(5, 8);
		this->RunFlyAnimation(true);
		m_type = ty;
		return true;
	default:
		return false;
	}
	return false;
}

Enemy * Enemy::createWithType(TypeEnemy ty)
{
	Enemy *enemy = new Enemy();
	if (enemy && enemy->InitWithType(ty))
	{
		enemy->autorelease();
		return enemy;
	}
	delete enemy;
	enemy = nullptr;
	return nullptr;
}

Size Enemy::GetPlayerSize()
{
	return this->m_sprite->getBoundingBox().size;
}

Sprite * Enemy::GetSprite()
{
	return this->m_sprite;
}

void Enemy::CreateBody(b2World * world)
{
	b2FixtureDef fixtureDef;
	fixtureDef.density = 10;
	fixtureDef.friction = 0.3;
	fixtureDef.restitution = 0;
	fixtureDef.shape = &m_bodyShape;

	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.userData = this;
	bodyDef.position.Set(this->getPosition().x / 32.0f, this->getPosition().y / 32.0f);

	this->m_b2Body = world->CreateBody(&bodyDef);
	this->m_fixture = this->GetB2Body()->CreateFixture(&fixtureDef);
	this->m_fixture->SetUserData(new TypeObject(IdEnemy, this));

	this->m_b2Body->SetFixedRotation(true);

	this->m_BodyIsDestroy = false;
}

bool Enemy::RunAttackAniamtion(bool repeatForever)
{
	if (this->m_AnimateAttack == nullptr)
		return false;
	if (repeatForever)
		this->m_sprite->runAction(RepeatForever::create(this->m_AnimateAttack->clone()));
	else
		this->m_sprite->runAction(this->m_AnimateAttack->clone());
	return true;
}

bool Enemy::RunDeadAnimation()
{
	if (this->m_AnimateDead == nullptr)
		return false;
	this->stopActionByTag(12);
	this->m_sprite->stopAllActions();
	this->m_sprite->runAction(Sequence::create(this->m_AnimateDead->clone(), CallFunc::create(CC_CALLBACK_0(Enemy::Dead, this)), nullptr));
	return true;
}
	
bool Enemy::RunIdleAniamtion(bool repeatForever)
{
	if (this->m_AnimateIdle == nullptr)
		return false;
	if (repeatForever)
		this->m_sprite->runAction(RepeatForever::create(this->m_AnimateIdle->clone()));
	else
		this->m_sprite->runAction(this->m_AnimateIdle->clone());
	return true;
}

bool Enemy::RunWalkAnimation(bool repeatForever)
{
	if (this->m_AnimateWalk == nullptr)
		return false;
	if (repeatForever)
		this->m_sprite->runAction(RepeatForever::create(this->m_AnimateWalk->clone()));
	else
		this->m_sprite->runAction(this->m_AnimateWalk->clone());
	return true;
}

bool Enemy::RunFlyAnimation(bool repeatForever)
{
	if (this->m_AnimateFly == nullptr)
		return false;
	if (repeatForever)
		this->m_sprite->runAction(RepeatForever::create(this->m_AnimateFly->clone()));
	else
		this->m_sprite->runAction(this->m_AnimateFly->clone());
	return true;
}

void Enemy::RunActionMoveTo(int xc)
{
	Vector<FiniteTimeAction*> arrayOfActions;
	if (this->getPosition().x <= this->m_movePosition[(xc) ? 0 : (this->m_movePosition.size() - 1)].x)
		this->setScaleX(-1);
	else
		this->setScaleX(1);
	for (int i = 0; i < this->m_movePosition.size(); i++)
	{
		arrayOfActions.pushBack(CallFunc::create(CC_CALLBACK_0(Enemy::BeginRun, this)));
		arrayOfActions.pushBack(MoveTo::create(m_timeRun, this->m_movePosition[(xc) ? i : (this->m_movePosition.size() - 1 - i)]));
		arrayOfActions.pushBack(CallFunc::create(CC_CALLBACK_0(Enemy::EndRun, this)));
		arrayOfActions.pushBack(DelayTime::create(m_timeDelay));
	}
	auto seq = RepeatForever::create(Sequence::create(arrayOfActions));
	seq->setTag(12);
	this->runAction(seq);
}

void Enemy::Dead()
{
	this->setVisible(false);
}

void Enemy::AddAttackAnimation(int tyEnemy, int numFrame)
{
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numFrame);

	for (int i = 1; i <= numFrame; i++)
	{
		std::string name = "Enemy" + std::to_string(tyEnemy) + "_Attack (" + std::to_string(i) + ").png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	this->m_AnimationAttack = Animation::createWithSpriteFrames(animFrames, 0.15f);
	this->m_AnimateAttack = Animate::create(this->m_AnimationAttack);
	this->m_AnimateAttack->retain();
}

void Enemy::AddDeadAnimation(int tyEnemy, int numFrame)
{
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numFrame);

	for (int i = 1; i <= numFrame; i++)
	{
		std::string name = "Enemy" + std::to_string(tyEnemy) + "_Dead (" + std::to_string(i) + ").png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	this->m_AnimationDead = Animation::createWithSpriteFrames(animFrames, 0.2f);
	this->m_AnimateDead = Animate::create(this->m_AnimationDead);
	this->m_AnimateDead->retain();
}

void Enemy::AddIdleAnimation(int tyEnemy, int numFrame)
{
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numFrame);

	for (int i = 1; i <= numFrame; i++)
	{
		std::string name = "Enemy" + std::to_string(tyEnemy) + "_Idle (" + std::to_string(i) + ").png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	this->m_AnimationIdle = Animation::createWithSpriteFrames(animFrames, 0.15f);
	this->m_AnimateIdle = Animate::create(this->m_AnimationIdle);
	this->m_AnimateIdle->retain();
}

void Enemy::AddWalkAnimation(int tyEnemy, int numFrame)
{
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numFrame);

	for (int i = 1; i <= numFrame; i++)
	{
		std::string name = "Enemy" + std::to_string(tyEnemy) + "_Walk (" + std::to_string(i) + ").png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	this->m_AnimationWalk = Animation::createWithSpriteFrames(animFrames, 0.15f);
	this->m_AnimateWalk = Animate::create(this->m_AnimationWalk);
	this->m_AnimateWalk->retain();
}

void Enemy::AddFlyAnimation(int tyEnemy, int numFrame)
{
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numFrame);

	for (int i = 1; i <= numFrame; i++)
	{
		std::string name = "Enemy" + std::to_string(tyEnemy) + "_Fly (" + std::to_string(i) + ").png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	this->m_AnimationFly = Animation::createWithSpriteFrames(animFrames, 0.15f);
	this->m_AnimateFly = Animate::create(this->m_AnimationFly);
	this->m_AnimateFly->retain();
}
