#include "Item.h"

void Item::LoadItem(TypeItem ty)
{
	switch (ty)
	{
	case ARMOR:
		break;
	case ARMOR_BOOTS:
		break;
	case BEANIE:
		break;
	case THORNMAIL:
		break;
	case WIND_COLAK:
		break;
	case NORMAL_SLINGSHOT:
		this->m_spriteBackgroundInShop = "Images/SlingShot0.png";
		this->m_spriteBackgroundInShopOnTouch = "Images/SlingShot0-1.png";
		this->m_spriteBoxItem = "Images/box_slingshot0.png";
		this->m_spriteBoxItemOnTouch = "Images/box_slingshot0-1.png";
		this->m_ty = ty;
		break;
	case TIME_SLINGSHOT:
		this->m_spriteBackgroundInShop = "Images/SlingShot1.png";
		this->m_spriteBackgroundInShopOnTouch = "Images/SlingShot1-1.png";
		this->m_spriteBoxItem = "Images/box_slingshot1.png";
		this->m_spriteBoxItemOnTouch = "Images/box_slingshot1-1.png";
		this->m_ty = ty;
		break;
	case FIRE_SLINGSHOT:
		this->m_spriteBackgroundInShop = "Images/SlingShot2.png";
		this->m_spriteBackgroundInShopOnTouch = "Images/SlingShot2-1.png";
		this->m_spriteBoxItem = "Images/box_slingshot2.png";
		this->m_spriteBoxItemOnTouch = "Images/box_slingshot2-1.png";
		this->m_ty = ty;
		break;
	case DIAMOND_SLINGSHOT:
		this->m_spriteBackgroundInShop = "Images/SlingShot3.png";
		this->m_spriteBackgroundInShopOnTouch = "Images/SlingShot3-1.png";
		this->m_spriteBoxItem = "Images/box_slingshot3.png";
		this->m_spriteBoxItemOnTouch = "Images/box_slingshot3-1.png";
		this->m_ty = ty;
		break;
	default:
		break;
	}
}

int Item::ItemSlingShotToInt()
{
	switch (this->m_ty)
	{
	case ARMOR:
		break;
	case ARMOR_BOOTS:
		break;
	case BEANIE:
		break;
	case THORNMAIL:
		break;
	case WIND_COLAK:
		break;
	case NORMAL_SLINGSHOT:
		return 0;
	case TIME_SLINGSHOT:
		return 1;
	case FIRE_SLINGSHOT:
		return 2;
	case DIAMOND_SLINGSHOT:
		return 3;
	default:
		break;
	}
	return -1;
}

TypeItem Item::GetTypeItem()
{
	return this->m_ty;
}
