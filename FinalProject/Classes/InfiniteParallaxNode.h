#pragma once
#include "cocos2d.h"
USING_NS_CC;

class PointObject : public Ref
{
public:
	inline void setRation(Point ratio) { _ratio = ratio; }
	inline void setOffset(Point offset) { _offset = offset; }
	inline void setChild(Node *var) { _child = var; }
	inline Point getOffset() const { return _offset; }
	inline Node* getChild() const { return _child; }
private:
	Point _ratio;
	Point _offset;
	RefPtr<Node> _child;
};

class InfiniteParallaxNode :public ParallaxNode
{
public:
	static InfiniteParallaxNode* create();
	void updatePosition();
};