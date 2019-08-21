#pragma once
#include "cocos2d.h"

USING_NS_CC;


class LayerWindSprite: public LayerColor
{
public:
	bool init() override;
	CREATE_FUNC(LayerWindSprite);
	Sprite* m_windSprite;
private:

};

