#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "Box2D\Box2D.h"
#include "Item.h"
#include <string.h>
USING_NS_CC;

class ItemLoot :public Node
{
public:
	ItemLoot() : m_spriteItem(nullptr), m_animation(nullptr), m_animate(nullptr), m_iNumberSprite(0) {}
	~ItemLoot() {}
	bool initWithTypeItem(Item item);
	static ItemLoot* createWithTypeItem(Item item);
private:
	RefPtr<Sprite> m_spriteItem;
	RefPtr<Sprite> m_spriteLight;
	Animation* m_animation;
	Animate* m_animate;
	int m_iNumberSprite;
};

