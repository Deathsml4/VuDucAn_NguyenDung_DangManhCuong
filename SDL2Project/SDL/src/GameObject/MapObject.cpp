#include "MapObject.h"
#include "Camera.h"

MapObject::MapObject()
{
	
}

MapObject::MapObject(std::shared_ptr<TextureManager> texture)
{
	MapObject();
	this->active = true;
	this->hp = 10;
	this->texture = texture;
}

void MapObject::Draw(SDL_Renderer* renderer)
{
	this->hitbox[0].x = MAP_START_X + GRID_UNITS * ((gridNumber % CHUNK_UNITS));
	this->hitbox[0].y = MAP_START_Y + GRID_UNITS * ((gridNumber / CHUNK_UNITS));
	this->hitbox[1].x = MAP_START_X + GRID_UNITS * ((gridNumber % CHUNK_UNITS) + 1);
	this->hitbox[1].y = MAP_START_Y + GRID_UNITS * ((gridNumber / CHUNK_UNITS) + 1);
	this->target.x = (this->hitbox[0].x + this->hitbox[1].x) / 2;
	this->target.y = (this->hitbox[0].y + this->hitbox[1].y) / 2;
	switch (objectType) {
	case MObject::MOBJECT_INVALID:
		break;
	case MObject::MOBJECT_TREE: 
		texture = ResourceManagers::GetInstance()->GetTexture(T_OBJECT_TREE);
		this->tl.x = this->hitbox[0].x - (TREE_WIDTH - GRID_UNITS) / 2;
		this->tl.y = this->hitbox[0].y - TREE_HEIGHT + GRID_UNITS;
		this->br.x = this->hitbox[1].x;
		this->br.y = this->hitbox[1].y;
		break;

	case MObject::MOBJECT_BUSH:
		texture = ResourceManagers::GetInstance()->GetTexture(T_OBJECT_BUSH);
		this->tl.x = this->hitbox[0].x - (BUSH_WIDTH - GRID_UNITS) / 2;
		this->tl.y = this->hitbox[0].y - BUSH_HEIGHT + GRID_UNITS;
		this->br.x = this->hitbox[1].x;
		this->br.y = this->hitbox[1].y;
		break;

	case MObject::MOBJECT_GRASS:
		texture = ResourceManagers::GetInstance()->GetTexture(T_OBJECT_GRASS);
		this->tl.x = this->hitbox[0].x - (BUSH_WIDTH - GRID_UNITS) / 2;
		this->tl.y = this->hitbox[0].y - BUSH_HEIGHT + GRID_UNITS;
		this->br.x = this->hitbox[1].x;
		this->br.y = this->hitbox[1].y;
		break;

	case MObject::MOBJECT_CROP:
		texture = ResourceManagers::GetInstance()->GetTexture(T_OBJECT_CROP);
		this->tl.x = this->hitbox[0].x - (BUSH_WIDTH - GRID_UNITS) / 2;
		this->tl.y = this->hitbox[0].y - BUSH_HEIGHT + GRID_UNITS;
		this->br.x = this->hitbox[1].x;
		this->br.y = this->hitbox[1].y;
		break;

	case MObject::MOBJECT_DEADBUSH:
		texture = ResourceManagers::GetInstance()->GetTexture(T_OBJECT_DEATHBUSH);
		this->tl.x = this->hitbox[0].x - (BUSH_WIDTH - GRID_UNITS) / 2;
		this->tl.y = this->hitbox[0].y - BUSH_HEIGHT + GRID_UNITS;
		this->br.x = this->hitbox[1].x;
		this->br.y = this->hitbox[1].y;
		break;

	case MObject::MOBJECT_ROCK:
		texture = ResourceManagers::GetInstance()->GetTexture(T_OBJECT_ROCK);
		this->tl.x = this->hitbox[0].x - (ROCK_WIDTH - GRID_UNITS) / 2;
		this->tl.y = this->hitbox[0].y - ROCK_HEIGHT + GRID_UNITS;
		this->br.x = this->hitbox[1].x;
		this->br.y = this->hitbox[1].y;
		break;

	case MObject::MOBJECT_CHESS:
		texture = ResourceManagers::GetInstance()->GetTexture(T_OBJECT_CHESS);
		this->tl.x = this->hitbox[0].x - (CHESS_WIDTH - GRID_UNITS) / 2;
		this->tl.y = this->hitbox[0].y - CHESS_HEIGHT + GRID_UNITS;
		this->br.x = this->hitbox[1].x;
		this->br.y = this->hitbox[1].y;
		break;

	case MObject::MOBJECT_GATE:
		texture = ResourceManagers::GetInstance()->GetTexture(T_OBJECT_GATE);
		this->tl.x = this->hitbox[0].x - (ROCK_WIDTH - GRID_UNITS) / 2;
		this->tl.y = this->hitbox[0].y - ROCK_HEIGHT + GRID_UNITS;
		this->br.x = this->hitbox[1].x;
		this->br.y = this->hitbox[1].y;
		this->hp = 10;
		break;
	}
	if (active = true) {
		if (texture != nullptr)
		{
			float posX = tl.x - Camera::GetInstance()->GetPosition().x;
			float posY = tl.y - Camera::GetInstance()->GetPosition().y;
			int sizeW = br.x - tl.x;
			int sizeH = br.y - tl.y;
			texture->Render(posX, posY, sizeW, sizeH, 0, m_flip = SDL_FLIP_NONE);
			//if(this->objectType != MObject::MOBJECT_INVALID) printf("size: %f x %f\n", br.x - tl.x, br.y - tl.y);
		}
	}
	else {
		this->objectType = MObject::MOBJECT_INVALID;
		this->SetSize(0, 0);
	}
	
	
}

void MapObject::PreUpdate()
{
	if (active = false) {
		switch (objectType)
		{
		case MObject::MOBJECT_INVALID:
			break;
		case MObject::MOBJECT_TREE:
			break;
		case MObject::MOBJECT_BUSH:
			break;
		case MObject::MOBJECT_GRASS:
			break;
		case MObject::MOBJECT_CROP:
			break;
		case MObject::MOBJECT_DEADBUSH:
			break;
		case MObject::MOBJECT_CHESS:
			break;
		case MObject::MOBJECT_ROCK:
			break;
		case MObject::MOBJECT_GATE:
			break;
		default:
			break;
		}
	}
}
