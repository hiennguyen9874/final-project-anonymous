#include "GameObject.h"

bool GameObject::init()
{
	if (Node::init() == false)
		return false;
	return true;
}

Size GameObject::GetSize()
{
	return this->m_sprite->getBoundingBox().size;
}
