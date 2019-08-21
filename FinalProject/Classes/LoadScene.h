#pragma once
#include "cocos2d.h"

USING_NS_CC;

class LoadScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    CREATE_FUNC(LoadScene);

	void update(float dt);
private:
	int m_loadingStep;
};