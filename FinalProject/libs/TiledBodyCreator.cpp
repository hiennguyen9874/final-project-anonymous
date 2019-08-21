#include "TiledBodyCreator.h"

USING_NS_CC;

#define PTMRATIO 32.0f

typedef enum {
	POLYGON_FIXTURE,
	POLYLINE_FIXTURE,
	RECT_FIXTURE,
	CIRCLE_FIXTURE,
	UNKNOWN_FIXTURE
} fixtureTypes;

void TiledBodyCreator::initCollisionMap(TMXTiledMap* map, b2World* world, 
	float32 friction, float32 restitution, float32 density, 
	uint16 categoryBits, uint16 maskBits, std::string name_Object)
{
	auto collisionGroup = map->getObjectGroup(name_Object);
	cocos2d::ValueVector collisionObjects = collisionGroup->getObjects();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	b2BodyDef bd;
	bd.type = b2_staticBody;

	auto collisionBody = world->CreateBody(&bd);

	for (cocos2d::Value objectValue : collisionObjects)
	{
		auto fixtureShape = TiledBodyCreator::createFixture(objectValue.asValueMap());
		if (fixtureShape != NULL && fixtureShape != nullptr) {
			fixtureShape->SetFixture(friction, restitution, density, categoryBits, maskBits);
			collisionBody->CreateFixture(&fixtureShape->fixture);
		}
	}
}

FixtureDef* TiledBodyCreator::createFixture(cocos2d::ValueMap object)
{
	int fixtureType = RECT_FIXTURE;
	for (auto propObj : object)
	{
		if (propObj.first == "points") {
			fixtureType = POLYGON_FIXTURE;
		}
		else if (propObj.first == "polylinePoints") {
			fixtureType = POLYLINE_FIXTURE;
		}
	}
	if (object["type"].asString() == "Circle") {
		fixtureType = CIRCLE_FIXTURE;
	}


	if (fixtureType == POLYGON_FIXTURE) {
		return createPolygon(object);
	}
	else if (fixtureType == POLYLINE_FIXTURE) {
		return createPolyline(object);
	}
	else if (fixtureType == CIRCLE_FIXTURE) {
		return createCircle(object);
	}
	else if (fixtureType == RECT_FIXTURE) {
		return createRect(object);
	}
}

FixtureDef* TiledBodyCreator::createPolygon(ValueMap object)
{
	ValueVector pointsVector = object["points"].asValueVector();
	auto position = Point(object["x"].asFloat() / PTMRATIO, object["y"].asFloat() / PTMRATIO);

	b2PolygonShape *polyshape = new b2PolygonShape();
	b2Vec2 vertices[b2_maxPolygonVertices];
	int vindex = 0;

	if (pointsVector.size() > b2_maxPolygonVertices) {
		CCLOG("Skipping TMX polygon at x=%d,y=%d for exceeding %d vertices", object["x"].asInt(), object["y"].asInt(), b2_maxPolygonVertices);
		return NULL;
	}

	auto fix = new FixtureDef();

	for (Value point : pointsVector) {
		vertices[vindex].x = ((point.asValueMap()["x"].asFloat() / PTMRATIO) / CC_CONTENT_SCALE_FACTOR() + position.x);
		vertices[vindex].y = ((-point.asValueMap()["y"].asFloat() / PTMRATIO) / CC_CONTENT_SCALE_FACTOR() + position.y);
		vindex++;
	}

	polyshape->Set(vertices, vindex);
	fix->fixture.shape = polyshape;
	return fix;
}

FixtureDef* TiledBodyCreator::createPolyline(ValueMap object)
{
	ValueVector pointsVector = object["polylinePoints"].asValueVector();
	auto position = Point(object["x"].asFloat() / PTMRATIO, object["y"].asFloat() / PTMRATIO);

	b2ChainShape *polylineshape = new b2ChainShape();

	int verticesCapacity = 32;
	b2Vec2* vertices = (b2Vec2*)calloc(verticesCapacity, sizeof(b2Vec2));

	int vindex = 0;

	auto fix = new FixtureDef();

	for (Value point : pointsVector) {

		if (vindex >= verticesCapacity)
		{
			verticesCapacity += 32;
			vertices = (b2Vec2*)realloc(vertices, verticesCapacity * sizeof(b2Vec2));
		}

		vertices[vindex].x = ((point.asValueMap()["x"].asFloat() / PTMRATIO) / CC_CONTENT_SCALE_FACTOR() + position.x);
		vertices[vindex].y = ((-point.asValueMap()["y"].asFloat() / PTMRATIO) / CC_CONTENT_SCALE_FACTOR() + position.y);
		vindex++;
	}

	polylineshape->CreateChain(vertices, vindex);
	fix->fixture.shape = polylineshape;

	return fix;
}

FixtureDef* TiledBodyCreator::createCircle(ValueMap object)
{
	auto position = Point(object["x"].asFloat() / PTMRATIO, object["y"].asFloat() / PTMRATIO);
	float radius = object["width"].asFloat() / 2 / PTMRATIO;

	b2CircleShape *circleshape = new b2CircleShape();
	circleshape->m_radius = radius;
	circleshape->m_p.Set(position.x + radius, position.y + radius);

	auto fix = new FixtureDef();
	fix->fixture.shape = circleshape;

	return fix;
}

FixtureDef* TiledBodyCreator::createRect(ValueMap object)
{
	auto position = Point(object["x"].asFloat() / PTMRATIO, object["y"].asFloat() / PTMRATIO);
	float width = object["width"].asFloat() / PTMRATIO;
	float height = object["height"].asFloat() / PTMRATIO;

	b2PolygonShape *rectshape = new b2PolygonShape();
	b2Vec2 vertices[4];
	int vindex = 4;

	vertices[0].x = position.x + 0.0f;
	vertices[0].y = position.y + 0.0f;

	vertices[1].x = position.x + 0.0f;
	vertices[1].y = position.y + height;

	vertices[2].x = position.x + width;
	vertices[2].y = position.y + height;

	vertices[3].x = position.x + width;
	vertices[3].y = position.y + 0.0f;

	auto fix = new FixtureDef();
	rectshape->Set(vertices, vindex);
	fix->fixture.shape = rectshape;

	return fix;
}