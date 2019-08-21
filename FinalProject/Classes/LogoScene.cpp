#include "LogoScene.h"
#include "SimpleAudioEngine.h"
#include "LoadScene.h"
#include "Utils.h"

USING_NS_CC;

Scene* LogoScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LogoScene::create();
	layer->init();
	scene->addChild(layer);
	return scene;
}

bool LogoScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto spriteBackground = Sprite::create("Background/Logo.png");
	spriteBackground->setScale(ScaleError(spriteBackground));
	spriteBackground->setPosition(visibleSize / 2);
	this->addChild(spriteBackground);

	this->scheduleUpdate();
    return true;
}

void LogoScene::update(float dt)
{
	switch (this->m_loadingStep)
	{
	case 100:
		Director::getInstance()->replaceScene(LoadScene::createScene());
		break;
	}
	this->m_loadingStep++;
}