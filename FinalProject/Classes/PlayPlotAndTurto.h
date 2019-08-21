#pragma once
#include "cocos2d.h"
#include "MapTMX.h"
#include "GameValue.h"
#include "AudioEngine.h"
#include "Utils.h"
#include "PlotLayer1.h"
#include "TurtorialLayer.h"

USING_NS_CC;

class PlayPlotAndTurto : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(bool boolean);
	static PlayPlotAndTurto* createWithLoad(bool boolean);
	bool initWithLoad(bool boolean);
private:
	RefPtr<TurtorialLayer> m_turtorialLayer;
	RefPtr<PlotLayer1> m_plot1Layer;
};