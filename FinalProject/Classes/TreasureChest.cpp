#include "TreasureChest.h"
#include "Config.h"
#include <string.h>

bool TreasureChest::init()
{
	if (GameObject::init() == false)
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// TODO:14-8
	m_typeChest = TypeTreasureChest::CHEST_1;
	this->m_iNumberSprite = 9;

	this->m_sprite = Sprite::createWithSpriteFrameName("Chest_1 (1).png");
	this->addChild(this->m_sprite);

	this->m_sprite->setScale(40 * 0.9 / this->m_sprite->getContentSize().height);
	this->m_sprite->setPosition(this->m_sprite->getPosition().x,
		this->m_sprite->getPosition().y + visibleSize.height * 0.005);

	return true;
}

bool TreasureChest::InitWithType(TypeTreasureChest ty)
{
	// TODO:14-8
	if (GameObject::init() == false)
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->m_typeChest = ty;
	switch (ty)
	{
	case CHEST_1:
		this->m_sprite = Sprite::createWithSpriteFrameName("Chest_1 (1).png");
		this->m_iNumberSprite = 9;
		break;
	case CHEST_2:
		this->m_sprite = Sprite::createWithSpriteFrameName("Chest_2 (1).png");
		this->m_iNumberSprite = 9;
		break;
	case CHEST_3:
		this->m_sprite = Sprite::createWithSpriteFrameName("Chest_3 (1).png");
		this->m_iNumberSprite = 6;
		break;
	default:
		break;
	}
	this->addChild(this->m_sprite);

	this->m_sprite->setScale(40 / this->m_sprite->getContentSize().height);
	this->m_sprite->setPosition(this->m_sprite->getPosition().x,
		this->m_sprite->getPosition().y + visibleSize.height * 0.005);
	return true;
}

TreasureChest* TreasureChest::createWithType(TypeTreasureChest ty)
{
	// TODO:14-8
	TreasureChest* chest = new TreasureChest();
	if (chest && chest->InitWithType(ty))
	{
		chest->autorelease();
		return chest;
	}
	delete chest;
	chest = nullptr;
	return nullptr;
}

void TreasureChest::CreateBody(b2World* world)
{
	this->m_bodyShape.SetAsBox(this->m_sprite->getBoundingBox().size.width / (2 * PTM_RATIO), this->m_sprite->getBoundingBox().size.height / (2 * PTM_RATIO));

	this->m_bodyDef.type = b2_staticBody;
	this->m_bodyDef.position.Set(this->getPosition().x / 32.0f,
		this->getPosition().y / 32.0f);

	this->m_fixtureDef.shape = &this->m_bodyShape;
	this->m_fixtureDef.isSensor = true;

	this->m_b2body = world->CreateBody(&m_bodyDef);
	this->m_fixture = m_b2body->CreateFixture(&m_fixtureDef);

	this->m_fixture->SetUserData(new TypeObject(IdTreasureChest, this));
}

void TreasureChest::RunAction()
{
	// TODO:14-8
	if (!m_isRunAction) {
		Vector<SpriteFrame*> animFrames;
		animFrames.reserve(m_iNumberSprite);

		for (int i = 1; i <= m_iNumberSprite; i++)
		{
			std::string name = "Chest_" + std::to_string((int)m_typeChest) + " (" + std::to_string(i) + ").png";
			animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
		}

		this->m_animation = Animation::createWithSpriteFrames(animFrames, 0.15f);
		this->m_animate = Animate::create(this->m_animation);
		this->m_sprite->runAction(this->m_animate);

		m_isRunAction = true;
	}
}

void TreasureChest::SetTypeItem(std::string typeItem)
{
	if (typeItem == "NORMAL_SLINGSHOT")
		this->m_typeItem = TypeItem::NORMAL_SLINGSHOT;
	else if (typeItem == "TIME_SLINGSHOT")
		this->m_typeItem = TypeItem::TIME_SLINGSHOT;
	else if (typeItem == "FIRE_SLINGSHOT")
		this->m_typeItem = TypeItem::FIRE_SLINGSHOT;
	else if (typeItem == "DIAMOND_SLINGSHOT")
		this->m_typeItem = TypeItem::DIAMOND_SLINGSHOT;
}

void TreasureChest::LoadItem()
{
	this->m_item.LoadItem(this->m_typeItem);
}
