#include "Mob.h"

int getRandT(int min, int max) {
	srand(time(nullptr));
	return min + rand() % (max - min + 1);
}

int getRandC(int min, int max) {
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	srand(seed);
	return min + rand() % (max - min + 1);
}

int getRandR(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(gen);
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
	br.x = getRandR(0, CHUNK_UNITS) * GRID_UNITS;
	br.y = getRandR(0, CHUNK_UNITS) * GRID_UNITS;

	// random size
	int scale = getRandR(3, 7);
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
	int direction = 0;
	int speed = getRandT(0, 2);
	int head = getRandT(0, 100);
	int angle = getRandT(0, 180) - 90;

	direction = head < 25 ? direction == 0 ? 180 : 0 : direction;
	SetFlip(head < 25 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

	int dx = cos(angle) * 1;
	int dy = sin(angle) * 1;
	
	Set2DPosition(this->Get2DPosition().x + dx, this->Get2DPosition().y + dy);
}

void Mob::OnHit()
{
}
