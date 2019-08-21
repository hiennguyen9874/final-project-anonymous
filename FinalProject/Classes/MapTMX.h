#pragma once
#include "Box2D/Box2D.h"
#include "../libs/TiledBodyCreator.h"
#include "cocos2d.h"
#include "Gold.h"
#include <string>

USING_NS_CC;
using namespace std;

class MapTMX: public Node
{
public:
	bool init() override;
	CREATE_FUNC(MapTMX);

	void SetInit(std::string path_TMX);
	Vec2 GetSpawnPoint();
	int GetNumOfSpawnPoint();

	float GetSizeWidth();
	float GetSizeHeight();
	
	void CreateCollisionMap(b2World * world, float32 friction, float32 restitution, float32 density, uint16 categoryBits, uint16 maskBits, std::string name_Object);
	void CreateFixtures(b2World * world);
	void CreateRectangularFixture(int x, int y, float width, float height, b2World * world);
	
	Vec2 GetCheckPoint(string name);
	ValueVector GetObjectGroup(string nameGroup);

private:
	RefPtr<TMXTiledMap> m_tmxTiledMap;
	RefPtr<TMXLayer> m_tmxLayerBackground;
	RefPtr<TMXLayer> m_tmxLayerMeta;
};