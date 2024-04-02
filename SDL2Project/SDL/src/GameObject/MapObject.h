#pragma once
#include<iostream>
#include<vector>

#include"BaseObject.h"
#include"SpriteAnimation.h"
#include"Sprite2D.h"


enum class MObject
{
	MOBJECT_INVALID = 0,
	MOBJECT_TREE,
	MOBJECT_BUSH,
	MOBJECT_GRASS,
	MOBJECT_CROP,
	MOBJECT_DEADBUSH,
	MOBJECT_CHESS,
	MOBJECT_ROCK
};

class MapObject : Sprite2D
{
public:
	MObject objectType;
	int gridNumber;
	bool active;
	//bool visible;
	//int type;
	//float light[3]; // R, G, B

	MapObject();
	MapObject(std::shared_ptr<TextureManager> texture);
};

