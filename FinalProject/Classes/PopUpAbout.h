#pragma once
#include "PopUp.h"

class PopUpAbout :
	public PopUp
{
public:
	CREATE_FUNC(PopUpAbout);

	virtual bool init();
	virtual void onExit();
protected:
private:
};

