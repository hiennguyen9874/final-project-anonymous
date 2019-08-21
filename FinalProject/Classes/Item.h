#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "Box2D\Box2D.h"
#include "Config.h"
#include <string.h>

USING_NS_CC;
using namespace std;

class Item
{
public:
	void LoadItem(TypeItem ty);
	string GetSpriteBackgroundInShop() { return this->m_spriteBackgroundInShop; }
	string GetPathBackgroundInShopOnTouch() { return this->m_spriteBackgroundInShopOnTouch; }
	string GetPathBoxItem() { return this->m_spriteBoxItem; }
	string GetPathBoxItemOnTouch() { return this->m_spriteBoxItemOnTouch; }
	string GetPathBoxItemSold() { return this->m_spriteBoxItemSold; }
	int ItemSlingShotToInt();
	TypeItem GetTypeItem();
private:
	string m_spriteBackgroundInShop;
	string m_spriteBackgroundInShopOnTouch;
	string m_spriteBoxItem;
	string m_spriteBoxItemOnTouch;
	string m_spriteBoxItemSold;
	TypeItem m_ty;
};

