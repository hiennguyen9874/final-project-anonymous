#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "Utils.h"
#include "GameValue.h"

USING_NS_CC;
using namespace ui;

class BackpackScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(BackpackScene);
	void OnButtonQuitTouch(Ref * sender, Widget::TouchEventType type);
	void OnListViewItemsRoll(Ref* senderRef, ListView::EventType e);
	void OnListViewSlingShotRoll(Ref* senderRef, ListView::EventType e);
	void OnBoxLeftTouch(Ref * sender, Widget::TouchEventType type);
	void OnBoxRightTouch(Ref * sender, Widget::TouchEventType type);
	void OnButtonTakeOffTouch(Ref * sender, Widget::TouchEventType type);
private:
	//void onEnter();
	//void onExit();
	void CreateRightBox();
	void CreateLeftBox();
	void CreateListViewItems();
	void CreateListViewSlingShot();
	void AddSlingShot();
	void AddItems();

	RefPtr<Label> m_cornScoreLabel;
	RefPtr<Button> m_Quit;
	RefPtr<Button> m_takeOff;
	RefPtr<Sprite> m_Background;
	RefPtr<Sprite> m_Character;
	RefPtr<Sprite> m_cornScore;
	RefPtr<Button> m_boxLeft;
	RefPtr<Button> m_boxRight;
	RefPtr<ListView> m_listSlingShotItems;
	RefPtr<ListView> m_listItems;
};