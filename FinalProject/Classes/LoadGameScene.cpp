#include "LoadGameScene.h"
#include "AudioEngine.h"
#include "MainMenuScene.h"
#include "PlayPlotAndTurto.h"
#include "GameScene.h"
#include "Utils.h"
#include <string.h>
#include "SceneMgr.h"

using namespace experimental;
USING_NS_CC;

Scene* LoadGameScene::createScene(bool boolean)
{
	auto scene = Scene::create();
	auto layer = LoadGameScene::createWithLoad(boolean);
	layer->init();

	scene->addChild(layer);
	return scene;
}

LoadGameScene * LoadGameScene::createWithLoad(bool boolean)
{
	LoadGameScene *scene = new LoadGameScene();
	if (scene && scene->initWithLoad(boolean))
	{
		scene->autorelease();
		return scene;
	}
	delete scene;
	scene = nullptr;
	return nullptr;
}

bool LoadGameScene::initWithLoad(bool boolean)
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	/////////////////////////////////////////////
	Label* m_LabeDead = Label::createWithTTF("Loading...", "fonts/retro_computer_personal_use.ttf", 30);
	m_LabeDead->setPosition(visibleSize / 2);
	this->addChild(m_LabeDead);


	this->m_load = boolean;

	this->scheduleUpdate();

	return true;
}

void LoadGameScene::update(float dt)
{
	switch (this->m_loadingStep)
	{
	case 0:
		GameValue::getInstance()->SetIsLoadGame(false);
		GameValue::getInstance()->SaveIsLoadGame();
		break;
	default:
	{
		if(this->m_load)
			Director::getInstance()->replaceScene(GameScene::createScene(true));
		else
			Director::getInstance()->replaceScene(PlayPlotAndTurto::createScene(false));
	}
		break;
	}
	CCLOG("UpdateSpritesSheet");
	this->m_loadingStep++;
}