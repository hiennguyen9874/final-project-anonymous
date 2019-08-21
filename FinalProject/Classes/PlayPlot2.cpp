#include "PlayPlot2.h"

using namespace experimental;
USING_NS_CC;

Scene* PlayPlot2::createScene()
{
	// 'scene' is an autorelease object
	Scene* scene = Scene::create();

	// 'layer' is an autorelease object
	PlayPlot2* layer = PlayPlot2::create();

	// add layer as a child to scene
	scene->addChild(layer, 0);

	// return the scene
	return scene;
}

bool PlayPlot2::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->m_plot2Layer = PlotLayer2::create();
	this->m_plot2Layer->setAnchorPoint(Vec2(0, 0));
	this->m_plot2Layer->setPosition(0, 0);
	this->addChild(this->m_plot2Layer, 1000);

	return true;
}
