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
	/*moveDuration = moveDuration <= 0 ? 0 : moveDuration - 1;
	if (moveDuration <= 0) {
		moveGoal = MakeDesicion();
	}
	MoveToward(moveGoal, deltaTime);*/
}

void Mob::Attack(int targetHeath)
{
	if (this->distanceToPlayer < 0.5 * GRID_UNITS) {
		if (attackCD <= 0) {
			targetHeath -= 5;
			float attackCD = MOB_ATTACK_CD;
			std::cout << "Attack " << targetHeath << std::endl;
		}
		attackCD = attackCD <= 0 ? 0 : attackCD - 1;
		auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/Splumonkey_Attack.png");
		this->SetTexture(texture);
	}
	else {
		auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/Splumonkey_Run.png");
		this->SetTexture(texture);
	}
}

void Mob::OnHit()
{
}

Vector2 Mob::MakeDesicion()
{
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	srand(seed);

	int xOffset = rand() % 101 - MOB_VISION;
	int yOffset = rand() % 101 - MOB_VISION;

	int newX = this->Get2DPosition().x + xOffset;
	int newY = this->Get2DPosition().y + yOffset;

	newX = std::max(0, std::min(CHUNK_SIZE - 1, newX));
	newY = std::max(0, std::min(CHUNK_SIZE - 1, newY));

	return Vector2(newX, newY);
}

void Mob::MoveToward(Vector2 goal, float deltaTime)
{
	if (this->distanceToPlayer < 3 * GRID_UNITS) {
		auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/Splumonkey_Run.png");
		this->SetTexture(texture);
		float distance = sqrt(pow(goal.x - this->Get2DPosition().x, 2) + pow(goal.y - this->Get2DPosition().y, 2));
		float stepSize = 0.001; 

		float newX = this->Get2DPosition().x + (goal.x - this->Get2DPosition().x) * stepSize;
		float newY = this->Get2DPosition().y + (goal.y - this->Get2DPosition().y) * stepSize;

		this->Set2DPosition(newX, newY);
	}
	else {
		auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/Splumonkey_Sleep.png");
		this->SetTexture(texture);
	}
	
}
