#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "GameValue.h"
#include "MiddleScene.h"

USING_NS_CC;
using namespace ui;

class TurtorialLayer: public LayerColor
{
public:
	bool init() override;
	CREATE_FUNC(TurtorialLayer);
private:
	void OnButtonPrevTouch(Ref* sender, Widget::TouchEventType type);
	void OnButtonNextTouch(Ref* sender, Widget::TouchEventType type);
	void OnButtonSkipTouch(Ref* sender, Widget::TouchEventType type);

	RefPtr<Button> PrevButton;
	RefPtr<Button> NextButton;
	RefPtr<Button> SkipButton;
	RefPtr<Sprite> m_sprite;
	int i = 0;
};

