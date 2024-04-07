#include "Mob.h"

int getRand(int min, int max) {
	srand(time(nullptr));
	return min + rand() % (max - min + 1);
}

Mob::Mob(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime)
{
	m_pTexture = texture;
	m_spriteRow = spriteRow;
	m_frameCount = frameCount;
	m_numAction = numAction;
	//m_animSpeed = animSpeed;
	m_frameTime = frameTime;
	//m_flip = flip;
	m_currentFrame = 0;
	m_currentTicks = 0;
	m_lastUpdate = SDL_GetTicks();
	active = true;
	Init();
}

void Mob::Spawn(SDL_Renderer* renderer)
{
	//// random place
	//br.x = getRand(0, CHUNK_UNITS)*GRID_UNITS;
	//br.x = getRand(0, CHUNK_UNITS)*GRID_UNITS;
	//
	//// random size
	//int scale = getRand(1, 7);
	//int width = MAX_MOB_WIDTH * scale;
	//int height = MAX_MOB_HEIGHT * scale;
	//this->SetSize(width, height);
	//// draw
	//tl.x = br.x - width;
	//tl.y = br.y - height;
	//this->Set2DPosition(tl.x, tl.y);
	//this->Draw(renderer);
}

void Mob::Init()
{
	// random place
	br.x = getRand(0, CHUNK_UNITS) * GRID_UNITS;
	br.y = getRand(0, CHUNK_UNITS) * GRID_UNITS;

	// random size
	int scale = getRand(1, 7);
	int width = MAX_MOB_WIDTH * scale/7;
	int height = MAX_MOB_HEIGHT * scale/7;
	this->SetSize(width, height);
	// draw
	tl.x = MAP_START_X + br.x - width;
	tl.y = MAP_START_Y + br.y - height;
	this->Set2DPosition(tl.x, tl.y);
}

void Mob::AutoMove(float deltaTime)
{
	int move = 0;
	int decision = getRand(0, 4);
	int think = getRand(0, 100);
	while (think--) {
		if (decision == 1) MoveUp(deltaTime);
		else if (decision == 2) MoveLeft(deltaTime);
		else if (decision == 3) MoveDown(deltaTime);
		else if (decision == 4) MoveRight(deltaTime);
	}
}

void Mob::OnHit()
{
}
