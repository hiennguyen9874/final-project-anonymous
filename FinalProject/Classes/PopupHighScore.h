#pragma once
#include "PopUp.h"

class PopupHighScore :
	public PopUp
{
public:
	CREATE_FUNC(PopupHighScore);
	bool init();
	virtual void onExit();
	virtual void appear();
protected:
private:
	Label *m_labelHighScore;
};

