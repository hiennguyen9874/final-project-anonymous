#include "PlayPlotAndTurto.h"

using namespace experimental;
USING_NS_CC;

Scene* PlayPlotAndTurto::createScene(bool boolean)
{
	auto scene = Scene::create();
	auto layer = PlayPlotAndTurto::createWithLoad(boolean);
	layer->init();
	scene->addChild(layer);
	return scene;
}

PlayPlotAndTurto * PlayPlotAndTurto::createWithLoad(bool boolean)
{
	PlayPlotAndTurto *scene = new PlayPlotAndTurto();
	if (scene && scene->initWithLoad(boolean))
	{
		scene->autorelease();
		return scene;
	}
	delete scene;
	scene = nullptr;
	return nullptr;
}

bool PlayPlotAndTurto::initWithLoad(bool boolean)
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->m_plot1Layer = PlotLayer1::create();
	this->m_plot1Layer->setAnchorPoint(Vec2(0, 0));
	this->m_plot1Layer->setPosition(0, 0);
	this->addChild(this->m_plot1Layer, 1000);

	this->m_turtorialLayer = TurtorialLayer::create();
	this->m_turtorialLayer->setAnchorPoint(Vec2(0, 0));
	this->m_turtorialLayer->setPosition(0, 0);
	this->addChild(this->m_turtorialLayer, 950);

	return true;
}
