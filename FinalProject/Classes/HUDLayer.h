#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "ui\CocosGUI.h"
#include "PopUpPause.h"

USING_NS_CC;
using namespace ui;
using namespace std;

/*
* Thanh hub tren cung hien thi trang thai game
*/

class HUDLayer :public LayerColor
{
public:
	bool init() override;
	CREATE_FUNC(HUDLayer);

	void SetPositionForHub(Vec2 positionPlayer,bool startBoolean);
	void SetPositionForHub(Vec2 PositionCamera);
	void SetTime(float time);
	void AddTime(float deltaTime);
	void SetDiamond(int numDiamond);
	void SetNumDead(int numDead);
	void Dead();
	void ShowWindDirectionSprite();
	void ChangeWindDirection(bool i);
	void HideWindDirectionSprite();
	void SetScore(int score);
	void OnButtonPause(Ref* sender, Widget::TouchEventType type);
	bool GetGamePause() { return this->m_pauseGame; }
	void SetStatusPause(bool enable);
	void SetPauseMenu(PopUpPause *popUpPauseGame) { this->m_popUpPauseGame = popUpPauseGame; }
private:
	Vec2 RetPosition(float percent);
private:
	Size m_VisibleSize;
	Vec2 m_VisibleOrigin;

	// Diamond
	RefPtr<Sprite> m_spriteDiamond;
	std::string m_strDiamond;
	RefPtr<Label> m_LabelDiamond;

	// Time
	RefPtr<Sprite> m_spriteTime;
	std::string m_strTime;
	RefPtr<Label> m_LabelTime;
	
	// Num Dead
	RefPtr<Sprite> m_spriteNumDead;
	std::string m_strDead;
	RefPtr<Label> m_LabeDead;

	//Wind Direction
	RefPtr<Sprite> m_windDirectionSprite;

	//Score
	RefPtr<Sprite> m_spriteScore;
	std::string m_strScore;
	RefPtr<Label> m_LabelScore;

	// Pause
	RefPtr<Button> m_buttonPause;
	bool m_pauseGame = false;
	RefPtr<PopUpPause> m_popUpPauseGame;
};

