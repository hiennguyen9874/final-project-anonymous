#pragma once
#include "cocos2d.h"
USING_NS_CC;

template <class T>
class ObjectPool :public Vector<T>
{
private:
	int m_index;
public:
	ObjectPool<T>() : m_index(0)
	{
	}

	T getObject()
	{
		T ObjIndex;
		if (m_index < this->size())
		{
			ObjIndex = this->at(m_index);
			m_index++;
		}
		else
		{
			ObjIndex = this->at(0);
			m_index = 1;
		}

		return ObjIndex;
	}

	void addObject(T obj)
	{
		this->pushBack(obj);
	}
};