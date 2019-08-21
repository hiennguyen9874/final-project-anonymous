#pragma once
#include "cocos2d.h"

class LogoScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(LogoScene);
	void update(float dt);
private:
	int m_loadingStep = 0;
};