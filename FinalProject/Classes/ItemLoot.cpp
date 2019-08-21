#include "ItemLoot.h"
#include "Config.h"
#include <string.h>

bool ItemLoot::initWithTypeItem(Item item)
{
	if (Node::init() == false)
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->m_spriteItem = Sprite::create(item.GetPathBoxItem());
	this->addChild(this->m_spriteItem, 1);
	this->m_spriteItem->setScale(0.7);

	this->m_spriteLight = Sprite::createWithSpriteFrameName("1.f0063.png");
	this->addChild(this->m_spriteLight, 0);
	this->m_spriteLight->setScale(2);

	this->m_spriteLight->runAction(RepeatForever::create(RotateTo::create(5.0f, 360 * M_PI)));

	return true;
}

ItemLoot * ItemLoot::createWithTypeItem(Item item)
{
	ItemLoot *itemLoot = new ItemLoot();
	if (itemLoot && itemLoot->initWithTypeItem(item))
	{
		itemLoot->autorelease();
		return itemLoot;
	}
	delete itemLoot;
	itemLoot = nullptr;
	return nullptr;
}
