#include "Stone.h"
#include "Config.h"

bool Stone::init()
{
	if (GameObject::init() == false)
		return false;
	this->m_sprite = Sprite::create("Images/Stone.png");
	this->addChild(this->m_sprite);
	return true;
}

void Stone::CreateBody()
{
	m_bodyShape.SetAsBox(this->m_sprite->getBoundingBox().size.width / (2 * PTM_RATIO),
		this->m_sprite->getBoundingBox().size.height / (2 * PTM_RATIO));

	m_fixtureDef.density = 10;
	m_fixtureDef.friction = 0.3;
	m_fixtureDef.restitution = 0;
	m_fixtureDef.shape = &m_bodyShape;

	m_bodyDef.type = b2_kinematicBody;
	m_bodyDef.userData = this;
	m_bodyDef.position.Set(this->getPosition().x / 32.0f, this->getPosition().y / 32.0f);

	this->m_b2body = this->m_world->CreateBody(&m_bodyDef);

	this->m_fixture = this->m_b2body->CreateFixture(&m_fixtureDef);
	this->m_fixture->SetUserData(new TypeObject(IdStone, this));
}

void Stone::CreateBrokenStone()
{
	this->m_b2body->SetActive(false);
	this->setVisible(false);
	this->setPosition(Vec2(this->m_startFall.x, this->m_startFall.y + Director::getInstance()->getVisibleSize().height * 0.1));

	auto brokenStone = Sprite::createWithSpriteFrameName("Explosion_1.png");
	brokenStone->setPosition(this->m_positionBroken);
	brokenStone->setScale(1.2);
	this->m_this->addChild(brokenStone);

	const int iNumberSprite = 7;
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(iNumberSprite);

	for (int i = 1; i <= 7; i++)
	{
		std::string name = "Explosion_" + std::to_string(i) + ".png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	auto animate = Animate::create(animation);
	brokenStone->runAction(Sequence::create(animate, RemoveSelf::create(), nullptr));
}

void Stone::SetStartAndDestinatePosition(Vec2 start, Vec2 destinate)
{
	this->m_startFall = start;
	this->m_destinateFall = destinate;
}

void Stone::CreateAnimate()
{
	this->m_b2body->SetActive(true);
	this->setVisible(true);

	// Cuc da roi xuong
	this->setPosition(Vec2(this->m_startFall.x, this->m_startFall.y + Director::getInstance()->getVisibleSize().height * 0.1));

	this->CreateBody();

	Sequence* myShakeAnimation = Sequence::create(
		MoveBy::create(0.05, Point(0, -10)),
		MoveBy::create(0.05, Point(-10, 0)),
		MoveBy::create(0.05, Point(0, 10)),
		MoveBy::create(0.05, Point(10, 0)),
		MoveBy::create(0.05, Point(0, -10)),
		MoveBy::create(0.05, Point(-10, 0)),
		MoveBy::create(0.05, Point(0, 10)),
		MoveBy::create(0.05, Point(10, 0)),
		MoveBy::create(0.05, Point(0, -10)),
		MoveBy::create(0.05, Point(-10, 0)),
		MoveBy::create(0.05, Point(0, 10)),
		MoveBy::create(0.05, Point(10, 0)),
		MoveBy::create(0.05, Point(0, -10)),
		MoveBy::create(0.05, Point(-10, 0)),
		MoveBy::create(0.05, Point(0, 10)),
		MoveBy::create(0.05, Point(10, 0)),
		MoveBy::create(0.05, Point(10, 0)),
		MoveBy::create(0.05, Point(0, -10)),
		MoveBy::create(0.025, Point(-10, 0)),
		MoveBy::create(0.025, Point(0, 10)),
		MoveBy::create(0.025, Point(10, 0)),
		MoveBy::create(0.025, Point(10, 0)),
		MoveBy::create(0.005, Point(0, -10)),
		MoveBy::create(0.005, Point(-10, 0)),
		MoveBy::create(0.005, Point(0, 10)),
		MoveBy::create(0.005, Point(10, 0)),
		nullptr);
	m_seq = Sequence::create(myShakeAnimation, MoveTo::create(7, Point(this->m_destinateFall.x, this->m_destinateFall.y)), RemoveSelf::create(),
		CallFunc::create(CC_CALLBACK_0(Stone::CreateBrokenStone, this)), nullptr);
	this->runAction(m_seq);
}

void Stone::Setb2World(b2World * world)
{
	this->m_world = world;
}
