#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "InfiniteParallaxNode.h"
#include "PopupSetting.h"
#include "PopUpAbout.h"
#include "PopupHighScore.h"
#include "PopUpQuit.h"
#include "PopUpPlay.h"

USING_NS_CC;
using namespace ui;

class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);

	void OnButtonPlay(Ref* sender, Widget::TouchEventType type);
	void OnButtonSetting(Ref* sender, Widget::TouchEventType type);
	void OnButtonAbout(Ref* sender, Widget::TouchEventType type);
	void OnButtonHighScore(Ref* sender, Widget::TouchEventType type);
	void OnButtonExit(Ref* sender, Widget::TouchEventType type);
	Vec2 setViewPointCenter(Point position);
	void updateBackground(float dt);
	bool HasPopUp() {
		return !(this->m_popUpAbout->GetVisiblePopUp() 
			&& this->m_popupSetting->GetVisiblePopUp() 
			&& this->m_popUpHighScore->GetVisiblePopUp() 
			&& this->m_popUpQuit->GetVisiblePopUp()
			&& this->m_popUpPlay->GetVisiblePopUp());
	}
private:
	void onEnter();
	void onExit();

	RefPtr<PopupSetting> m_popupSetting;
	RefPtr<PopUpAbout> m_popUpAbout;
	RefPtr<PopupHighScore> m_popUpHighScore;
	RefPtr<PopUpQuit> m_popUpQuit;
	RefPtr<PopUpPlay> m_popUpPlay;
	bool m_xuoi = true;
	RefPtr<InfiniteParallaxNode> m_parallaxBackground;
	int m_numUpdate = 0;
	Vec2 m_Size;
};