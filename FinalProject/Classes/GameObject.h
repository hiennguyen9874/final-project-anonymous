#pragma once
#include <cocos2d.h>

USING_NS_CC;

struct TypeObject
{
	int idObject;
	void *ptr;
	TypeObject(int id, void *ptr) { this->idObject = id; this->ptr = ptr; }
};

class GameObject : public Node
{
public:
	bool init() override;
	CREATE_FUNC(GameObject);
	Size GetSize();
protected:
	RefPtr<Sprite> m_sprite;
	RefPtr<Animation> m_animation;
	RefPtr<Animate> m_animate;
	int m_iNumberSprite;
};