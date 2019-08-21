#pragma once
#include "GameObject.h"


class Wind: public GameObject
{
public:
	bool init() override;
	CREATE_FUNC(Wind);

	bool m_directorIsLeftToRight = true;
private:
};

