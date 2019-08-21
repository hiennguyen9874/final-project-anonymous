#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "GameValue.h"
#include "MainMenuScene.h"

USING_NS_CC;
using namespace ui;

class EndLayer: public LayerColor
{
public:
	bool init() override;
	CREATE_FUNC(EndLayer);
private:
	void OnButtonSkipTouch(Ref* sender, Widget::TouchEventType type);
	void PlayPlot();
	void NextPic();

	RefPtr<Button> SkipButton;
	RefPtr<Sprite> m_sprite;
	int i = 0;
};

