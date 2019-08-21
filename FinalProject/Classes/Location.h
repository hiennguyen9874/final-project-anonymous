#pragma once
#include "GameObject.h"


class Location: public Node
{
public:
	bool init() override;
	CREATE_FUNC(Location);

	void SetScaleX(float scale);
	void ShowCancleCircle();
	void ShowCircle();
private:
	RefPtr<Sprite> m_cancleCircle;
	RefPtr<Sprite> m_spriteCircle;
	RefPtr<Sprite> m_spriteArrow;
};

