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
		this->hitbox[0].x = MAP_START_X + GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->hitbox[0].y = MAP_START_Y + GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		this->hitbox[1].x = MAP_START_X + GRID_UNITS * ((gridNumber % CHUNK_UNITS) + 1);
		this->hitbox[1].y = MAP_START_Y + GRID_UNITS * ((gridNumber / CHUNK_UNITS) + 1);
		this->tl.x = this->hitbox[0].x - (TREE_WIDTH - GRID_UNITS) / 2;
		this->tl.y = this->hitbox[0].y - TREE_HEIGHT + GRID_UNITS;
		this->br.x = this->hitbox[1].x;
		this->br.y = this->hitbox[1].y;
		break;

	case MObject::MOBJECT_BUSH:
		texture = ResourceManagers::GetInstance()->GetTexture("300px-Berry_Bush_Build.png");
		this->hitbox[0].x = MAP_START_X + GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->hitbox[0].y = MAP_START_Y + GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		this->hitbox[1].x = MAP_START_X + GRID_UNITS * ((gridNumber % CHUNK_UNITS) + 1);
		this->hitbox[1].y = MAP_START_Y + GRID_UNITS * ((gridNumber / CHUNK_UNITS) + 1);
		this->tl.x = this->hitbox[0].x - (BUSH_WIDTH - GRID_UNITS) / 2;
		this->tl.y = this->hitbox[0].y - BUSH_HEIGHT + GRID_UNITS;
		this->br.x = this->hitbox[1].x;
		this->br.y = this->hitbox[1].y;
		break;

	case MObject::MOBJECT_GRASS:
		texture = ResourceManagers::GetInstance()->GetTexture("300px-Tall_Grass.png");
		this->hitbox[0].x = MAP_START_X + GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->hitbox[0].y = MAP_START_Y + GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		this->hitbox[1].x = MAP_START_X + GRID_UNITS * ((gridNumber % CHUNK_UNITS) + 1);
		this->hitbox[1].y = MAP_START_Y + GRID_UNITS * ((gridNumber / CHUNK_UNITS) + 1);
		this->tl.x = this->hitbox[0].x - (BUSH_WIDTH - GRID_UNITS) / 2;
		this->tl.y = this->hitbox[0].y - BUSH_HEIGHT + GRID_UNITS;
		this->br.x = this->hitbox[1].x;
		this->br.y = this->hitbox[1].y;
		break;

	case MObject::MOBJECT_CROP:
		texture = ResourceManagers::GetInstance()->GetTexture("Grass_Tuft.png");
		this->hitbox[0].x = MAP_START_X + GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->hitbox[0].y = MAP_START_Y + GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		this->hitbox[1].x = MAP_START_X + GRID_UNITS * ((gridNumber % CHUNK_UNITS) + 1);
		this->hitbox[1].y = MAP_START_Y + GRID_UNITS * ((gridNumber / CHUNK_UNITS) + 1);
		this->tl.x = this->hitbox[0].x - (BUSH_WIDTH - GRID_UNITS) / 2;
		this->tl.y = this->hitbox[0].y - BUSH_HEIGHT + GRID_UNITS;
		this->br.x = this->hitbox[1].x;
		this->br.y = this->hitbox[1].y;
		break;

	case MObject::MOBJECT_DEADBUSH:
		texture = ResourceManagers::GetInstance()->GetTexture("300px-Sapling.png");
		this->hitbox[0].x = MAP_START_X + GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->hitbox[0].y = MAP_START_Y + GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		this->hitbox[1].x = MAP_START_X + GRID_UNITS * ((gridNumber % CHUNK_UNITS) + 1);
		this->hitbox[1].y = MAP_START_Y + GRID_UNITS * ((gridNumber / CHUNK_UNITS) + 1);
		this->tl.x = this->hitbox[0].x - (BUSH_WIDTH - GRID_UNITS) / 2;
		this->tl.y = this->hitbox[0].y - BUSH_HEIGHT + GRID_UNITS;
		this->br.x = this->hitbox[1].x;
		this->br.y = this->hitbox[1].y;
		break;

	case MObject::MOBJECT_ROCK:
		texture = ResourceManagers::GetInstance()->GetTexture("Boulder.png");
		this->hitbox[0].x = MAP_START_X + GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->hitbox[0].y = MAP_START_Y + GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		this->hitbox[1].x = MAP_START_X + GRID_UNITS * ((gridNumber % CHUNK_UNITS) + 1);
		this->hitbox[1].y = MAP_START_Y + GRID_UNITS * ((gridNumber / CHUNK_UNITS) + 1);
		this->tl.x = this->hitbox[0].x - (ROCK_WIDTH - GRID_UNITS) / 2;
		this->tl.y = this->hitbox[0].y - ROCK_HEIGHT + GRID_UNITS;
		this->br.x = this->hitbox[1].x;
		this->br.y = this->hitbox[1].y;
		break;

	case MObject::MOBJECT_CHESS:
		texture = ResourceManagers::GetInstance()->GetTexture("40px-Booty_Bag.png");
		this->hitbox[0].x = MAP_START_X + GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->hitbox[0].y = MAP_START_Y + GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		this->hitbox[1].x = MAP_START_X + GRID_UNITS * ((gridNumber % CHUNK_UNITS) + 1);
		this->hitbox[1].y = MAP_START_Y + GRID_UNITS * ((gridNumber / CHUNK_UNITS) + 1);
		this->tl.x = this->hitbox[0].x - (CHESS_WIDTH - GRID_UNITS) / 2;
		this->tl.y = this->hitbox[0].y - CHESS_HEIGHT + GRID_UNITS;
		this->br.x = this->hitbox[1].x;
		this->br.y = this->hitbox[1].y;
		break;

	case MObject::MOBJECT_GATE:
		texture = ResourceManagers::GetInstance()->GetTexture("Icefishing_Hole_Map_Icon.png");
		this->hitbox[0].x = MAP_START_X + GRID_UNITS * ((gridNumber % CHUNK_UNITS));
		this->hitbox[0].y = MAP_START_Y + GRID_UNITS * ((gridNumber / CHUNK_UNITS));
		this->hitbox[1].x = MAP_START_X + GRID_UNITS * ((gridNumber % CHUNK_UNITS) + 1);
		this->hitbox[1].y = MAP_START_Y + GRID_UNITS * ((gridNumber / CHUNK_UNITS) + 1);
		this->tl.x = this->hitbox[0].x - (CHESS_WIDTH - GRID_UNITS)/2;
		this->tl.y = this->hitbox[0].y - CHESS_HEIGHT + GRID_UNITS;
		this->br.x = this->hitbox[1].x;
		this->br.y = this->hitbox[1].y;
		break;
	}
		
	if (texture != nullptr)
	{
		float posX = tl.x - Camera::GetInstance()->GetPosition().x;
		float posY = tl.y - Camera::GetInstance()->GetPosition().y;
		int sizeW = br.x - tl.x;
		int sizeH = br.y - tl.y;
		texture->Render(posX, posY, sizeW, sizeH, 0, m_flip);
		//if(this->objectType != MObject::MOBJECT_INVALID) printf("size: %f x %f\n", br.x - tl.x, br.y - tl.y);
	}
	
}
