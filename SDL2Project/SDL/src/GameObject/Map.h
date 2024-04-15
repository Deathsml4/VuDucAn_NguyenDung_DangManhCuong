#pragma once
#include<iostream>
#include<vector>
#include<list>
#include <utility>

#include"BaseObject.h"
#include"Sprite2D.h"
#include"MapObject.h"
#include"Mob.h"
#include"CMath.h"
#include"Define.h"
#include"Character.h"

enum class MapMode
{
	MAP_INVALID = 0,
	MAP_VALLILA,
	MAP_MAZE
};

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
	int mobCount = 0;
	std::shared_ptr<GridPoint> plainTerrain;
	std::shared_ptr<GridPoint> riverTerrain;
	std::shared_ptr<MapObject> mObject;
	std::vector<std::shared_ptr<GridPoint>> grids; //list the map grid
	std::vector< std::shared_ptr<MapObject>> objects; //list the objects that are here
	std::list < std::shared_ptr<Mob>> mobs; // list the mobs

	MapChunk(MapMode mode);
	//MapChunk(char* data);
	void Draw(SDL_Renderer* renderer) override;
	Vector2 Get2DPosition() { return Vector2(m_position.x, m_position.y); };
};

class Map
{
private:
	std::pair<Vector2, Vector2> checkPoint;
public:
	int h, v; //size of the map in chunk unit
	std::vector<std::shared_ptr<MapChunk>> chunks;
	std::map <std::shared_ptr<MapObject>, Vector2*> objectHitboxs;
	std::vector<std::pair<Vector2, Vector2>> collieBoxs;
	Map(MapMode mode);
	void Init(MapMode mode);
	//Map(char* data);
	void Draw(SDL_Renderer* renderer);
	void DisplayHitboxs(SDL_Renderer* renderer);
	void UpdateCollies();
	bool isOnTheCheckPoint(Vector2 playerPos);
	std::vector<std::shared_ptr<MapChunk>> relatedMapChunk(std::shared_ptr<Character> character);
};

