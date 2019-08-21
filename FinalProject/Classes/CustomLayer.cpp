#include "CustomLayer.h"
#include "Utils.h"

bool CustomLayer::InitWithSpriteName(std::string name)
{
	if (!Layer::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto visibleOrigin = Director::getInstance()->getVisibleOrigin();

	this->m_sprite = Sprite::create(name);
	this->m_sprite->setScale(ScaleError(this->m_sprite));
	this->m_sprite->setPosition(visibleSize / 2);
	this->addChild(m_sprite);
	return true;
}

CustomLayer* CustomLayer::CreateWithSpriteName(std::string name)
{
	CustomLayer* layer = new CustomLayer();
	if (layer && layer->InitWithSpriteName(name))
	{
		layer->autorelease();
		return layer;
	}
	delete layer;
	layer = nullptr;
	return nullptr;
}