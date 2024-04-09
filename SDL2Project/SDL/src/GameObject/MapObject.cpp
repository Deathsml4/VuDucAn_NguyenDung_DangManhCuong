#include "MapObject.h"
#include "Camera.h"

MapObject::MapObject()
{
	active = true;
}

MapObject::MapObject(std::shared_ptr<TextureManager> texture)
{
	MapObject();
	this->texture = texture;
}

void MapObject::Draw(SDL_Renderer* renderer)
{
	switch (objectType) {
	case MObject::MOBJECT_TREE: 
		texture = ResourceManagers::GetInstance()->GetTexture("300px-A_Lumpy_Evergreen.png");
		this->tl.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->tl.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		this->br.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS) + TREE_WIDTH);
		this->br.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS) + TREE_HEIGHT);
		break;
	
	case MObject::MOBJECT_BUSH: 
		texture = ResourceManagers::GetInstance()->GetTexture("300px-Berry_Bush_Build.png");
		this->tl.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->tl.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		this->br.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS) + BUSH_WIDTH);
		this->br.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS) + BUSH_HEIGHT);
		break;
	case MObject::MOBJECT_GRASS:
		texture = ResourceManagers::GetInstance()->GetTexture("300px-Tall_Grass.png");
		this->tl.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->tl.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		this->br.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS) + BUSH_WIDTH);
		this->br.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS) + BUSH_HEIGHT);
		break;
	case MObject::MOBJECT_CROP:
		texture = ResourceManagers::GetInstance()->GetTexture("Grass_Tuft.png");
		this->tl.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->tl.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		this->br.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS)) + BUSH_WIDTH;
		this->br.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS) + BUSH_HEIGHT);
		break;
	case MObject::MOBJECT_DEADBUSH:
		texture = ResourceManagers::GetInstance()->GetTexture("300px-Sapling.png");
		this->tl.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->tl.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		this->br.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS) + BUSH_WIDTH);
		this->br.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS) + BUSH_HEIGHT);
		break;
	case MObject::MOBJECT_ROCK:
		texture = ResourceManagers::GetInstance()->GetTexture("Boulder.png");
		this->tl.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->tl.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		this->br.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS) + ROCK_WIDTH);
		this->br.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS) + ROCK_HEIGHT);
		break;
	case MObject::MOBJECT_CHESS:
		texture = ResourceManagers::GetInstance()->GetTexture("40px-Booty_Bag.png");
		this->tl.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->tl.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		this->br.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS) + CHESS_WIDTH);
		this->br.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS) + CHESS_HEIGHT);
		break;
	case MObject::MOBJECT_GATE:
		texture = ResourceManagers::GetInstance()->GetTexture("Icefishing_Hole_Map_Icon.png");
		this->tl.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->tl.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		this->br.x = GRID_UNITS * ((gridNumber % CHUNK_UNITS) + CHESS_WIDTH);
		this->br.y = GRID_UNITS * ((gridNumber / CHUNK_UNITS) + CHESS_HEIGHT);
		break;
	}
		
	if (texture != nullptr)
	{
		texture->Render(MAP_START_X + tl.x - Camera::GetInstance()->GetPosition().x, MAP_START_Y + tl.y - Camera::GetInstance()->GetPosition().y, br.x-tl.x, br.y - tl.y, 0, m_flip);
	}
	
}
