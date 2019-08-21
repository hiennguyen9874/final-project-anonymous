#pragma once
#include "string"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Config.h"

using namespace cocos2d::ui;
USING_NS_CC;

class PopUpPause :public Node
{
public:
	virtual bool init() override;
	virtual void onExit();
	virtual void disappear();
	virtual void appear();
	virtual void setTitlePopup(std::string _titlePopup);
	virtual void setTitlePopUpWithSprite(std::string _pathSprite);
	Size GetBackgroundContentSize() { return this->m_backgroundContentSize; }
	bool GetVisiblePopUp() { return this->m_close; }
	CREATE_FUNC(PopUpPause);

	void OnButtonSound(Ref* sender, Widget::TouchEventType type);
	void OnButtonMusic(Ref* sender, Widget::TouchEventType type);
	void OnButtonResume(Ref* sender, Widget::TouchEventType type);
	void OnButtonRestart(Ref* sender, Widget::TouchEventType type);
	void OnButtonExit(Ref* sender, Widget::TouchEventType type);
	void OnButtonSave(Ref* sender, Widget::TouchEventType type);

	bool GetResume() { return this->m_bResume; }
	void SetResume(bool enable) {
		this->m_bResume = enable;
	}
	void Pause(){
		Director::getInstance()->pause();
	}

	bool GetSave() { return this->m_bSave; }
	void SetSave(bool enable) { this->m_bSave = enable; }

protected:
	RefPtr<Layer>	m_popupLayer;

	Size	m_backgroundContentSize;
	Size	m_visibleSize;
	Point	m_origin;

	RefPtr<ActionInterval> m_appearAction;
	RefPtr<ActionInterval> m_disappearAction;
	bool m_close = true;

	Vec2 m_startPosition;
	Vec2 m_endPosition;
private:
	RefPtr<Button> m_buttonSound;
	
	RefPtr<Button> m_buttonMusic;

	RefPtr<Button> m_buttonSave;
	bool m_bSave = false;

	bool m_bResume = false;
	RefPtr<Sequence> m_seq;
};

