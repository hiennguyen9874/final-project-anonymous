#pragma once

#include "cocos2d.h"
#include "GameObject.h"

USING_NS_CC;

class SlingShot :public GameObject
{
public:
	bool init() override;
	CREATE_FUNC(SlingShot);

	void SetImageSlingShot(int indexSlingshot);
private:
	SpriteFrame *m_spriteSlingshot0;
	SpriteFrame *m_spriteSlingshot1;
	SpriteFrame *m_spriteSlingshot2;
	SpriteFrame *m_spriteSlingshot3;
};