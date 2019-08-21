#ifndef __TILED_BODY_CREATOR_H__
#define __TILED_BODY_CREATOR_H__

#include "cocos2d.h"
#include <Box2D/Box2D.h>

USING_NS_CC;

class FixtureDef {
public:
    FixtureDef()
    : next(nullptr) {}
    
    ~FixtureDef() {
        delete next;
        delete fixture.shape;
    }
	void SetFixture(float32 friction, float32 restitution, float32 density, uint16 categoryBits, uint16 maskBits)
	{
		this->fixture.density = density;
		this->fixture.friction = friction;
		this->fixture.restitution = restitution;
		this->fixture.filter.categoryBits = categoryBits;
		this->fixture.filter.maskBits = maskBits;
	}
    
    FixtureDef *next;
    b2FixtureDef fixture;
    int callbackData;
};

class BodyDef {
public:
    BodyDef()
    : fixtures(nullptr) {}
    
    ~BodyDef() {
        if (fixtures)
            delete fixtures;
    }
    
    FixtureDef *fixtures;
    Point anchorPoint;
};

class TiledBodyCreator
{
public:
	static void initCollisionMap(TMXTiledMap* map, b2World* world, float32 friction, float32 restitution, float32 density, uint16 categoryBits, uint16 maskBits, std::string name_Object);
	
	static FixtureDef* createFixture(ValueMap object);
	static FixtureDef* createPolygon(ValueMap object);
	static FixtureDef* createPolyline(ValueMap object);
	static FixtureDef* createCircle(ValueMap object);
	static FixtureDef* createRect(ValueMap object);
	
};

#endif // __TILED_BODY_CREATOR_H__
