#pragma once
#include "PopUp.h"

class PopupSetting :
	public PopUp
{
public:
	CREATE_FUNC(PopupSetting);

	bool init();
	virtual void onExit();

	virtual void appear();

	void sliderEventMusic(Ref *pSender, Slider::EventType type);
	void sliderEventSound(Ref* pSender, Slider::EventType type);

	void changeVolumeOfAudio(int _typeAudio, float _valueVolume);

	void OnButtonSound(Ref* sender, Widget::TouchEventType type);
	void OnButtonMusic(Ref* sender, Widget::TouchEventType type);
protected:
private:
	RefPtr<Slider> m_sliderOptionMusics[2];

	RefPtr<Button> m_buttonSound;
	RefPtr<Button> m_buttonMusic;
};

