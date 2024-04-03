#pragma once
#include<iostream>
#include<vector>

#include"BaseObject.h"
#include"SpriteAnimation.h"
#include"Sprite2D.h"
#include"define.h"
#include"ResourceManagers.h"

const float TREE_HEIGHT = 1.5;
const float TREE_WIDTH = 1;
const float BUSH_HEIGHT = 0.7;
const float BUSH_WIDTH = 1;
const float ROCK_HEIGHT = 1;
const float ROCK_WIDTH = 1;
const float CHESS_HEIGHT = 0.5;
const float CHESS_WIDTH = 1;

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
	Vector2 tl, br; // top-left and bottom-right coodinate

	std::shared_ptr<TextureManager> texture = ResourceManagers::GetInstance()->GetTexture("Forest_Turf_Texture.png");

	MapObject();
	MapObject(std::shared_ptr<TextureManager> texture);

	void Draw(SDL_Renderer* renderer) override;
};

