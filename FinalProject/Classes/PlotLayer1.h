#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "GameValue.h"

USING_NS_CC;
using namespace ui;

class PlotLayer1: public LayerColor
{
public:
	bool init() override;
	CREATE_FUNC(PlotLayer1);
private:
	void OnButtonSkipTouch(Ref* sender, Widget::TouchEventType type);
	void PlayPlot();
	void NextPic();

	RefPtr<Button> SkipButton;
	RefPtr<Sprite> m_sprite;
	int i = 0;
};

