#include "InfiniteParallaxNode.h"

InfiniteParallaxNode* InfiniteParallaxNode::create()
{
	InfiniteParallaxNode* node = new InfiniteParallaxNode();
	if (node)
	{
		node->autorelease();
	}
	else
	{
		delete node;
		node = 0;
	}
	return node;
}

void InfiniteParallaxNode::updatePosition()
{
	int safeOffset = -10;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	for (int i = 0; i < _children.size(); i++)
	{
		auto node = _children.at(i);
		if (convertToWorldSpace(node->getPosition()).x +
			node->getContentSize().width < safeOffset)
		{
			for (int j = 0; j < _parallaxArray->num; j++)
			{
				auto po = (PointObject*)_parallaxArray->arr[j];
				if (po->getChild() == node)
					po->setOffset(po->getOffset() +
						Point(visibleSize.width + node->getContentSize().width, 0));
			}
		}
	}
}