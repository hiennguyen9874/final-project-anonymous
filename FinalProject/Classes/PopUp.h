#pragma once
#include "string"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Config.h" 

using namespace cocos2d::ui;
USING_NS_CC;

class PopUp :public Node
{
public:
	virtual bool init() override;
	virtual void onExit();
	virtual void disappear();
	virtual void appear();
	virtual void setTitlePopup(std::string _titlePopup);
	virtual void setTitlePopUpWithSprite(std::string _pathSprite);
	Size GetBackgroundContentSize() { return this->m_backgroundContentSize; }
	void OnButtonClose(Ref* sender, Widget::TouchEventType type);
	bool GetVisiblePopUp() {
		return this->m_close;
	}
	CREATE_FUNC(PopUp);
protected:
	RefPtr<Layer>	m_popupLayer;

	Size	m_backgroundContentSize;
	Size	m_visibleSize;
	Point	m_origin;

	RefPtr<ActionInterval> m_appearAction;
	RefPtr<ActionInterval> m_disappearAction;
	bool m_close = true;
private:
};

