#include "PopUpAbout.h"

bool PopUpAbout::init()
{
	if (!PopUp::init())
		return false;

	this->setTitlePopup("About");
	return true;
}

void PopUpAbout::onExit()
{
	PopUp::onExit();
}