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
	this->maxHP = MOB_BASE_HP * scale / 7;
	this->currentHP = maxHP/2;
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

bool Mob::Attack()
{
	if (this->distanceToPlayer < 0.5 * GRID_UNITS) {
		this->attackCD = this->attackCD <= 0 ? 0 : this->attackCD - 1;
		if (this->attackCD <= 0) {
			this->attackCD = MOB_ATTACK_CD;
			return true;
		}
		
		auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/Splumonkey_Attack.png");
		this->SetTexture(texture);
		return false;
	}
	else {
		
		return false;
	}
}

void Mob::OnHit()
{
}

void Mob::DisplayHP(SDL_Renderer* renderer)
{
	int barWidth = this->currentHP * (this->GetWidth()) / MOB_BASE_HP;
	// Set the draw color based on value
	if (this->currentHP >= 7) {
		SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF); // Green
	}
	else {
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF); // Red
	}
	SDL_Rect hpBarRect = { this->GetPosition().x - Camera::GetInstance()->GetPosition().x, this->GetPosition().y - Camera::GetInstance()->GetPosition().y, barWidth, 5 };
	SDL_RenderFillRect(renderer, &hpBarRect);
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

void Mob::MoveToward(Vector2 goal)
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

void Mob::BounceBack(Vector2 goal)
{
	if (this->distanceToPlayer < 3 * GRID_UNITS) {
		auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/Splumonkey_Run.png");
		this->SetTexture(texture);
		float distance = sqrt(pow(goal.x - this->Get2DPosition().x, 2) + pow(goal.y - this->Get2DPosition().y, 2));
		float stepSize = -2;

		float newX = this->Get2DPosition().x + (goal.x - this->Get2DPosition().x) * stepSize;
		float newY = this->Get2DPosition().y + (goal.y - this->Get2DPosition().y) * stepSize;

		this->Set2DPosition(newX, newY);
	}
	else {
		auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/Splumonkey_Sleep.png");
		this->SetTexture(texture);
	}
}

void Mob::UpdateTexture(Vector2 playerPos)
{
	if (playerPos.x > this->Get2DPosition().x) {
		this->SetFlip(SDL_FLIP_NONE);
	}
	else {
		this->SetFlip(SDL_FLIP_HORIZONTAL);
	}
}
