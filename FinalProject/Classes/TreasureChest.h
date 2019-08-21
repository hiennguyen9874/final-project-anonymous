#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "Box2D\Box2D.h"
#include "Item.h"
#include <string.h>
USING_NS_CC;

class TreasureChest :public GameObject
{
public:
	bool init() override;
	CREATE_FUNC(TreasureChest);

	// TODO:14-8
	bool InitWithType(TypeTreasureChest ty);
	static TreasureChest* createWithType(TypeTreasureChest ty);

	void CreateBody(b2World *world);
	void SetActive(bool active) { this->m_b2body->SetActive(active); }
	void RunAction();
	void SetTypeItem(std::string typeItem);
	void LoadItem();
	Item GetItem() { return this->m_item; }
private:
	b2Body *m_b2body;
	b2PolygonShape m_bodyShape;
	b2BodyDef m_bodyDef;
	b2FixtureDef m_fixtureDef;
	b2Fixture *m_fixture;
	bool m_isRunAction = false;
	Item m_item;
	TypeItem m_typeItem;
	RefPtr<Sprite> m_spriteItemFromTreasureChest = nullptr;

	TypeTreasureChest m_typeChest;
};

