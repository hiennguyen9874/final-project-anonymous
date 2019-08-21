#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "Utils.h"
#include "GameValue.h"

USING_NS_CC;

class ShopingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(ShopingScene);
	void OnButtonQuitTouch(Ref * sender, Widget::TouchEventType type);
	void OnListViewItemsRoll(Ref* senderRef, ListView::EventType e);
	void OnButtonBuyTouch(Ref * sender, Widget::TouchEventType type);
private:
	//void onEnter();
	//void onExit();
	void CreateListViewItems();
	void AddItems();

	RefPtr<Label> m_labelPrice;
	RefPtr<Label> m_cornScoreLabel;
	RefPtr<Button> m_buy;
	RefPtr<ListView> m_listItems;
	RefPtr<Sprite> m_Background;
	RefPtr<Sprite> m_Price;
	RefPtr<Sprite> m_cornScore;
	RefPtr<Button> m_box;
	RefPtr<Button> m_Quit;
};