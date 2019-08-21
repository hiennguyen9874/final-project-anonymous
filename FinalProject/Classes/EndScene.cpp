#include "EndScene.h"

using namespace experimental;
USING_NS_CC;

Scene* EndScene::createScene()
{
	// 'scene' is an autorelease object
	Scene* scene = Scene::create();

	// 'layer' is an autorelease object
	EndScene* layer = EndScene::create();

	// add layer as a child to scene
	scene->addChild(layer, 0);

	// return the scene
	return scene;
}

bool EndScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	log("a");

	this->m_endLayer = EndLayer::create();
	this->m_endLayer->setAnchorPoint(Vec2(0, 0));
	this->m_endLayer->setPosition(0, 0);
	this->addChild(this->m_endLayer, 1000);

	return true;
}
