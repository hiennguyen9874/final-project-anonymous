#pragma once
#include <string.h>
#include <iomanip>
#include <sstream>
#include <math.h>
#include <climits>
#include <random>
#include "GameObject.h"
#include "Config.h"
#include "cocos2d.h"
#include "Box2D\Box2D.h"

using namespace std;
USING_NS_CC;

string strAddNum(string str, int num);
float ScaleError(cocos2d::Sprite* sprite);
float ScaleError(Size sizeContent);
Vec2 PositionError(float x, float y);
float PositionErrorX(float x);
float PositionErrorY(float y);
int rand_int(int min, int max);
float rand_float(float min, float max);
Vec2 b2VecToVec2(b2Vec2 b2Vec);
b2Vec2 Vec2ToB2Vec2(Vec2 vec);