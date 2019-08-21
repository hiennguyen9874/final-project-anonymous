#pragma once
#include "cocos2d.h"
#include "MapTMX.h"
#include "GameValue.h"
#include "AudioEngine.h"
#include "Utils.h"
#include "EndLayer.h"

USING_NS_CC;

class EndScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(EndScene);
private:
	RefPtr<EndLayer> m_endLayer;
	int i = 0;
};