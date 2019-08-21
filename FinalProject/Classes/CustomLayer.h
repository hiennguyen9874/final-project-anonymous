#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include <string.h>

/*
* Layer chi co mot anh lam background.
* Thuong su dung lam Paralax background
*/
class CustomLayer :public Layer
{
public:
	CustomLayer() {}
	~CustomLayer() {}
	bool InitWithSpriteName(std::string name);
	static CustomLayer* CreateWithSpriteName(std::string name);

	Vec2 GetContentSizeOfSprite() { return this->m_sprite->getContentSize(); }
private:
	RefPtr<Sprite> m_sprite;
};