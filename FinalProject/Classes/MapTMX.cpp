#include "MapTMX.h"

bool MapTMX::init()
{
	if (Node::init() == false)
		return false;
	return true;
}

void MapTMX::SetInit(std::string path_TMX)
{
	this->m_tmxTiledMap = TMXTiledMap::create(path_TMX);
	this->m_tmxLayerBackground = this->m_tmxTiledMap->layerNamed("Background");
	this->addChild(this->m_tmxTiledMap);
}

Vec2 MapTMX::GetSpawnPoint()
{
	TMXObjectGroup *objectGroup = this->m_tmxTiledMap->objectGroupNamed("Object");
	if (objectGroup == nullptr)
	{
		CCLOG("Tile map has no objects object layer");
		return nullptr;
	}

	auto spawnPoint = objectGroup->objectNamed("SpawnPoint" + std::to_string(this->GetNumOfSpawnPoint()));
	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();
	return Vec2(x, y);
}

int MapTMX::GetNumOfSpawnPoint()
{
	return this->m_tmxTiledMap->getProperties()["SpawnPoint"].asInt();
}

float MapTMX::GetSizeWidth()
{
	return this->m_tmxTiledMap->getTileSize().width * this->m_tmxTiledMap->getMapSize().width;
}

float MapTMX::GetSizeHeight()
{
	return this->m_tmxTiledMap->getTileSize().height * this->m_tmxTiledMap->getMapSize().height;
}

void MapTMX::CreateCollisionMap(b2World * world, float32 friction, float32 restitution, float32 density, uint16 categoryBits, uint16 maskBits, std::string name_Object)
{
	TiledBodyCreator::initCollisionMap(this->m_tmxTiledMap, world, friction, restitution, density, categoryBits, maskBits, name_Object);
}

void MapTMX::CreateFixtures(b2World * world)
{
	Size layerSize = this->m_tmxLayerMeta->getLayerSize();
	for (int y = 0; y < layerSize.height; y++)
	{
		for (int x = 0; x < layerSize.width; x++)
		{
			auto tileSprite = this->m_tmxLayerMeta->getTileAt(Vec2(x, y));
			if (tileSprite)
				this->CreateRectangularFixture(x, y, 1.1f, 1.1f, world);
		}
	}
}

void MapTMX::CreateRectangularFixture(int x, int y, float width, float height, b2World * world)
{
	// get position & size
	auto p = this->m_tmxLayerMeta->getPositionAt(Point(x, y));
	auto tileSize = this->m_tmxTiledMap->getTileSize();
	const float pixelsPerMeter = 32.0f;

	// create the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(
		(p.x + (tileSize.width / 2.0f)) / pixelsPerMeter,
		(p.y + (tileSize.height / 2.0f)) / pixelsPerMeter
	);
	b2Body* body = world->CreateBody(&bodyDef);

	// define the shape
	b2PolygonShape shape;
	shape.SetAsBox(
		(tileSize.width / pixelsPerMeter) * 0.5f * width,
		(tileSize.width / pixelsPerMeter) * 0.5f * height
	);

	// create the fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;
	fixtureDef.restitution = 0.4;
	fixtureDef.filter.categoryBits = 0x01;
	fixtureDef.filter.maskBits = 0xffff;
	body->CreateFixture(&fixtureDef);
}

Vec2 MapTMX::GetCheckPoint(string name)
{
	TMXObjectGroup *objectGroup = this->m_tmxTiledMap->objectGroupNamed("Object");
	if (objectGroup == nullptr)
	{
		CCLOG("Tile map has no objects object layer");
		return nullptr;
	}
	auto spawnPoint = objectGroup->objectNamed(name);
	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();
	return Vec2(x, y);
}

ValueVector MapTMX::GetObjectGroup(string nameGroup)
{
	TMXObjectGroup *objectGroup = this->m_tmxTiledMap->getObjectGroup(nameGroup);

	return objectGroup->getObjects();
}