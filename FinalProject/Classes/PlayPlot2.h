#pragma once
#include "cocos2d.h"
#include "MapTMX.h"
#include "GameValue.h"
#include "AudioEngine.h"
#include "Utils.h"
#include "PlotLayer2.h"

USING_NS_CC;

class PlayPlot2 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(PlayPlot2);
private:
	RefPtr<PlotLayer2> m_plot2Layer;
};