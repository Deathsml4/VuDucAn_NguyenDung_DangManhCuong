#include "MapObject.h"

MapObject::MapObject()
{
	active = true;
}

MapObject::MapObject(std::shared_ptr<TextureManager> texture)
{
	MapObject();
	this->texture = texture;
}

void MapObject::Init()
{
	switch (objectType) {
	case MObject::MOBJECT_TREE: 
		texture = ResourceManagers::GetInstance()->GetTexture("300px-A_Lumpy_Evergreen.png");
		this->tl.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS) - TREE_WIDTH);
		this->tl.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS) - TREE_HEIGHT);
		this->br.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->br.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		break;
	
	case MObject::MOBJECT_BUSH: 
		texture = ResourceManagers::GetInstance()->GetTexture("300px-Berry_Bush_Build.png");
		this->tl.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS) - BUSH_WIDTH);
		this->tl.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS) - BUSH_HEIGHT);
		this->br.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->br.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		break;
	case MObject::MOBJECT_GRASS:
		texture = ResourceManagers::GetInstance()->GetTexture("300px-Tall_Grass.png");
		this->tl.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS) - BUSH_WIDTH);
		this->tl.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS) - BUSH_HEIGHT);
		this->br.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->br.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		break;
	case MObject::MOBJECT_CROP:
		texture = ResourceManagers::GetInstance()->GetTexture("Grass_Tuft.png");
		this->tl.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS) - BUSH_WIDTH);
		this->tl.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS) - BUSH_HEIGHT);
		this->br.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->br.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		break;
	case MObject::MOBJECT_DEADBUSH:
		texture = ResourceManagers::GetInstance()->GetTexture("300px-Sapling.png");
		this->tl.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS) - BUSH_WIDTH);
		this->tl.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS) - BUSH_HEIGHT);
		this->br.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->br.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		break;
	case MObject::MOBJECT_ROCK:
		texture = ResourceManagers::GetInstance()->GetTexture("Boulder.png");
		this->tl.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS) - ROCK_WIDTH);
		this->tl.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS) - ROCK_HEIGHT);
		this->br.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->br.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		break;
	case MObject::MOBJECT_CHESS:
		texture = ResourceManagers::GetInstance()->GetTexture("40px-Booty_Bag.png");
		this->tl.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS) - CHESS_WIDTH);
		this->tl.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS) - CHESS_HEIGHT);
		this->br.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->br.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		break;
	case MObject::MOBJECT_GATE:
		texture = ResourceManagers::GetInstance()->GetTexture("Icefishing_Hole_Map_Icon.png");
		this->tl.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS) - CHESS_WIDTH);
		this->tl.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS) - CHESS_HEIGHT);
		this->br.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->br.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		break;
	}
	
}
