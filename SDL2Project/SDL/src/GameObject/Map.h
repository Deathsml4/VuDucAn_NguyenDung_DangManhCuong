#pragma once
#include<iostream>
#include<vector>

#include"BaseObject.h"
#include"Sprite2D.h"
#include"MapObject.h"
#include"Mob.h"
#include"CMath.h"
#include"Define.h"

enum class MTerrain
{
	MTERRAIN_INVALID = 0,
	MTERRAIN_PLAIN,
	MTERRAIN_RIVER
};

class GridPoint : Sprite2D{
public:
	int gridNumber;
	MTerrain terrain; //terrain type
	std::shared_ptr<TextureManager> texture = ResourceManagers::GetInstance()->GetTexture("Forest_Turf_Texture.png");

	GridPoint();
	GridPoint(std::shared_ptr<TextureManager> texture);

	void Draw(SDL_Renderer* renderer) override;
};

class MapChunk : Sprite2D {
public:
	std::shared_ptr<GridPoint> plainTerrain;
	std::shared_ptr<GridPoint> riverTerrain;
	std::vector<std::shared_ptr<GridPoint>> grids; //list the map grid
	std::vector< std::shared_ptr<MapObject>> objects; //list the objects that are here
	//std::vector<Mob> Mobs; // list the mobs

	MapChunk();
	//MapChunk(char* data);
	void Draw(SDL_Renderer* renderer) override;
};

class Map
{
public:
	int h, v; //size of the map in chunk unit
	std::vector<std::shared_ptr<MapChunk>> chunks;

	Map();
	//Map(char* data);
	void Draw(SDL_Renderer* renderer);
};

