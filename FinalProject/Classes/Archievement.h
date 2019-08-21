#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "Box2D\Box2D.h"

USING_NS_CC;

class Archivement :public GameObject
{
public:
	bool init() override;
	CREATE_FUNC(Archivement);
	void setStringForLabel(std::string labelString);
	void setPositionForAll(Vec2 position);
	void RunAction();
private:
	Sprite* m_sprite;
	Label* m_label;
};

