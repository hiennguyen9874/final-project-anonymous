#include "DynamicObject.h"
#include "Config.h"

bool DynamicObject::init()
{
	if (GameObject::init() == false)
		return false;	
	return true;
}
