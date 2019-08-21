#include "Boss.h"
#include "../libs/GB2ShapeCache-x.h"

bool Boss::init()
{
	if (GameObject::init() == false)
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	this->m_sprite = Sprite::createWithSpriteFrameName("Boss_Idle (1).png");
	this->m_sprite->setScale(0.2);
	this->addChild(this->m_sprite);

	m_bloodBarBG = Sprite::createWithSpriteFrameName("hpBar.png");
	m_bloodBarBG->setScaleX(0.5);
	m_bloodBarBG->setScaleY(0.4);
	m_bloodBarBG->setPosition(Vec2(-this->m_sprite->getBoundingBox().size.width * 0.05,
		this->m_sprite->getBoundingBox().size.height * 0.7));
	this->addChild(this->m_bloodBarBG);

	m_bloodBar = Sprite::createWithSpriteFrameName("hpBarfull.png");
	m_bloodBar->setScaleX(m_bloodBarBG->getBoundingBox().size.width / m_bloodBar->getContentSize().width);
	m_bloodBar->setScaleY(m_bloodBarBG->getBoundingBox().size.height / m_bloodBar->getContentSize().height);
	m_bloodBar->setAnchorPoint(Vec2(0, 0.5));
	m_bloodBar->setPosition(Vec2(-this->m_sprite->getBoundingBox().size.width * 0.05 - m_bloodBar->getBoundingBox().size.width / 2,
		this->m_sprite->getBoundingBox().size.height * 0.7));
	this->addChild(this->m_bloodBar);

	m_spriteTim = Sprite::createWithSpriteFrameName("tim.png");
	m_spriteTim->setPosition(Vec2(-m_bloodBar->getBoundingBox().size.width / 2,
		this->m_sprite->getBoundingBox().size.height * 0.7));
	m_spriteTim->setScale(0.5);
	this->addChild(m_spriteTim);

	this->SetPercent(1);

	this->AddAttackAnimation(7);
	this->AddDeadAnimation(7);
	this->AddHurtAnimation(7);
	this->AddIdleAnimation(7);
	this->AddJumpAnimation(7);
	this->AddRunAnimation(7);
	this->AddWalkAnimation(7);

	this->RunIdleAniamtion();
	return true;
}

void Boss::CreateBody(b2World * world)
{
	b2PolygonShape bodyShape;
	bodyShape.SetAsBox(this->m_sprite->getBoundingBox().size.width / (2 * PTM_RATIO),
		this->m_sprite->getBoundingBox().size.height / (2 * PTM_RATIO));

	b2FixtureDef fixtureDef;
	fixtureDef.density = 10;
	fixtureDef.friction = 0.3;
	fixtureDef.restitution = 0;
	fixtureDef.shape = &bodyShape;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.userData = this;
	bodyDef.position.Set(this->getPosition().x / 32.0f, this->getPosition().y / 32.0f);

	this->m_b2Body = world->CreateBody(&bodyDef);

	this->m_fixture = this->m_b2Body->CreateFixture(&fixtureDef);
	this->m_fixture->SetUserData(new TypeObject(IdBoss, this));

	this->m_b2Body->SetFixedRotation(true);

	this->m_BodyIsDestroy = false;
}

void Boss::RunActionMoveTo()
{
	bool xc;
	if (this->getPosition().distance(this->m_movePosition[0]) >= this->getPosition().distance(this->m_movePosition[this->m_movePosition.size() - 1]))
		xc = true;
	else
		xc = false;

	Vector<FiniteTimeAction*> arrayOfActions;

	if (this->getPosition().x <= this->m_movePosition[(xc) ? 0 : (this->m_movePosition.size() - 1)].x)
		this->m_sprite->setScaleX(-this->m_sprite->getScaleX());
	else
		this->m_sprite->setScaleX(this->m_sprite->getScaleX());

	for (int i = 0; i < this->m_movePosition.size(); i++)
	{
		arrayOfActions.pushBack(CallFunc::create(CC_CALLBACK_0(Boss::BeginRun, this)));
		arrayOfActions.pushBack(MoveTo::create(m_timeRun, this->m_movePosition[(xc) ? i : (this->m_movePosition.size() - 1 - i)]));
		arrayOfActions.pushBack(CallFunc::create(CC_CALLBACK_0(Boss::EndRun, this)));
		arrayOfActions.pushBack(DelayTime::create(m_timeDelay));
	}
	m_seq = RepeatForever::create(Sequence::create(arrayOfActions));
	m_seq->setTag(12);
	this->runAction(m_seq);
}

bool Boss::RunAttackAniamtion(bool repeatForever)
{
	if (this->m_AnimateAttack == nullptr)
		return false;
	if (repeatForever)
		this->m_sprite->runAction(RepeatForever::create(this->m_AnimateAttack->clone()));
	else
		this->m_sprite->runAction(this->m_AnimateAttack->clone());
	return true;
}

bool Boss::RunDeadAnimation()
{
	if (this->m_AnimateDead == nullptr)
		return false;
	if (this->m_isDead)
		return true;

	this->m_bloodBarBG->setVisible(false);
	this->m_bloodBar->setVisible(false);
	this->m_spriteTim->setVisible(false);

	this->m_b2Body->SetActive(false);
	this->stopActionByTag(12);
	this->m_sprite->stopAllActions();
	this->m_sprite->runAction(Sequence::create(this->m_AnimateDead->clone(), nullptr));
	this->m_isDead = true;
	return true;
}

bool Boss::RunHurtAniamtion(bool repeatForever)
{
	this->m_sprite->stopAllActions();
	if (this->m_AnimateHurt == nullptr)
		return false;
	if (repeatForever)
		this->m_sprite->runAction(RepeatForever::create(this->m_AnimateHurt->clone()));
	else
		this->m_sprite->runAction(Sequence::create(this->m_AnimateHurt->clone(),
			CallFunc::create(CC_CALLBACK_0(Boss::RunIdleAniamtion, this)), nullptr));
	return true;
}

bool Boss::RunIdleAniamtion()
{
	this->m_sprite->stopAllActions();
	if (this->m_AnimateIdle == nullptr)
		return false;
	this->m_sprite->runAction(RepeatForever::create(this->m_AnimateIdle->clone()));
	return true;
}

bool Boss::RunJumpAnimation(bool repeatForever)
{
	if (this->m_AnimateJump == nullptr)
		return false;
	if (repeatForever)
		this->m_sprite->runAction(RepeatForever::create(this->m_AnimateJump->clone()));
	else
		this->m_sprite->runAction(this->m_AnimateJump->clone());
	return true;
}

bool Boss::RunRunAnimation(bool repeatForever)
{
	if (this->m_AnimateRun == nullptr)
		return false;
	if (repeatForever)
		this->m_sprite->runAction(RepeatForever::create(this->m_AnimateRun->clone()));
	else
		this->m_sprite->runAction(this->m_AnimateRun->clone());
	return true;
}

bool Boss::RunWalkAnimation(bool repeatForever)
{
	if (this->m_AnimateWalk == nullptr)
		return false;
	if (repeatForever)
		this->m_sprite->runAction(RepeatForever::create(this->m_AnimateWalk->clone()));
	else
		this->m_sprite->runAction(this->m_AnimateWalk->clone());
	return true;
}

void Boss::AddAttackAnimation(int numFrame)
{
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numFrame);

	for (int i = 1; i <= numFrame; i++)
	{
		std::string name = "Boss_Attack (" + std::to_string(i) + ").png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	this->m_AnimationAttack = Animation::createWithSpriteFrames(animFrames, 0.15f);
	this->m_AnimateAttack = Animate::create(this->m_AnimationAttack);
	this->m_AnimateAttack->retain();
}

void Boss::AddDeadAnimation(int numFrame)
{
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numFrame);

	for (int i = 1; i <= numFrame; i++)
	{
		std::string name = "Boss_Die (" + std::to_string(i) + ").png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	this->m_AnimationDead = Animation::createWithSpriteFrames(animFrames, 0.15f);
	this->m_AnimateDead = Animate::create(this->m_AnimationDead);
	this->m_AnimateDead->retain();
}

void Boss::AddHurtAnimation(int numFrame)
{
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numFrame);

	for (int i = 1; i <= numFrame; i++)
	{
		std::string name = "Boss_Hurt (" + std::to_string(i) + ").png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	this->m_AnimationHurt = Animation::createWithSpriteFrames(animFrames, 0.15f);
	this->m_AnimateHurt = Animate::create(this->m_AnimationHurt);
	this->m_AnimateHurt->retain();
}

void Boss::AddIdleAnimation(int numFrame)
{
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numFrame);

	for (int i = 1; i <= numFrame; i++)
	{
		std::string name = "Boss_Idle (" + std::to_string(i) + ").png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	this->m_AnimationIdle = Animation::createWithSpriteFrames(animFrames, 0.15f);
	this->m_AnimateIdle = Animate::create(this->m_AnimationIdle);
	this->m_AnimateIdle->retain();
}

void Boss::AddJumpAnimation(int numFrame)
{
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numFrame);

	for (int i = 1; i <= numFrame; i++)
	{
		std::string name = "Boss_Jump (" + std::to_string(i) + ").png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	this->m_AnimationJump = Animation::createWithSpriteFrames(animFrames, 0.15f);
	this->m_AnimateJump = Animate::create(this->m_AnimationJump);
	this->m_AnimateJump->retain();
}

void Boss::AddRunAnimation(int numFrame)
{
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numFrame);

	for (int i = 1; i <= numFrame; i++)
	{
		std::string name = "Boss_Run (" + std::to_string(i) + ").png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	this->m_AnimationRun = Animation::createWithSpriteFrames(animFrames, 0.15f);
	this->m_AnimateRun = Animate::create(this->m_AnimationRun);
	this->m_AnimateRun->retain();
}

void Boss::AddWalkAnimation(int numFrame)
{
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numFrame);

	for (int i = 1; i <= numFrame; i++)
	{
		std::string name = "Boss_Walk (" + std::to_string(i) + ").png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	this->m_AnimationWalk = Animation::createWithSpriteFrames(animFrames, 0.15f);
	this->m_AnimateWalk = Animate::create(this->m_AnimationWalk);
	this->m_AnimateWalk->retain();
}
