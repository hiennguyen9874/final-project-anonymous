#include "LoadScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "Utils.h"
#include <string.h>
#include "GameValue.h"
#include "../libs/GB2ShapeCache-x.h"
#include "SoundMgr.h"

USING_NS_CC;

Scene* LoadScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadScene::create();
	

	layer->init();
	scene->addChild(layer);


	return scene;
}

bool LoadScene::init()
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

	this->m_loadingStep = 0;

	this->scheduleUpdate();
	return true;
}

void LoadScene::update(float dt)
{
	switch (this->m_loadingStep)
	{
	case 0:
		// Load texture packer
		for (int i = 1; i <= 5; i++)
		{
			std::string str = "TexturePacker/TexturePacker-" + std::to_string(i);
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(str + ".plist", str + ".png");
		}
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("TexturePacker/ExplosionStone.plist", "TexturePacker/ExplosionStone.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("TexturePacker/Appearance.plist", "TexturePacker/Appearance.png");
		GameValue::getInstance()->LoadTurtorial();
		GameValue::getInstance()->LoadPlot1();
		GameValue::getInstance()->LoadPlot2();
		break;
	case 1:
		// Load Physics
		GB2ShapeCache::getInstance()->addShapesWithFile("physic.plist");
		break;
	case 2:
		// Load game value
		GameValue::getInstance()->LoadHighScore();
		GameValue::getInstance()->LoadGameValue();
		GameValue::getInstance()->LoadEnd();
		GameValue::getInstance()->LoadIsLoadGame();
		break;
	case 3:
		SoundMgr::getInstance()->Preload();
		break;
	default:
		// Replace scene
		Director::getInstance()->replaceScene(MainMenuScene::createScene());
		break;
	}
	this->m_loadingStep++;
}