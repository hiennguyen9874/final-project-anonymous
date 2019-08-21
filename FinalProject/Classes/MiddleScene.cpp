#include "MiddleScene.h"
#include "AudioEngine.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "Utils.h"
#include <string.h>
#include "SceneMgr.h"

using namespace experimental;
USING_NS_CC;

Scene* MiddleScene::createScene(bool boolean)
{
	auto scene = Scene::create();
	auto layer = MiddleScene::createWithLoad(boolean);
	layer->init();
	scene->addChild(layer);
	return scene;
}

MiddleScene * MiddleScene::createWithLoad(bool boolean)
{
	MiddleScene *scene = new MiddleScene();
	if (scene && scene->initWithLoad(boolean))
	{
		scene->autorelease();
		return scene;
	}
	delete scene;
	scene = nullptr;
	return nullptr;
}

bool MiddleScene::initWithLoad(bool boolean)
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	
	Label* m_LabeDead = Label::createWithTTF("Loading...", "fonts/retro_computer_personal_use.ttf", 30);
	m_LabeDead->setPosition(visibleSize / 2);
	this->addChild(m_LabeDead);
	
	
	this->scheduleUpdate();
	return true;
}

void MiddleScene::update(float dt)
{
	switch (this->m_loadingStep)
	{
	default:
	{
		Director::getInstance()->replaceScene(GameScene::createScene(false));
	}
		break;
	}
	this->m_loadingStep++;
}