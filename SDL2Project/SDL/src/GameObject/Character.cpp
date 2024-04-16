#include "Character.h"
#include "Define.h"

Character::Character(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime)
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
	Init();
}

PlayerInput& Character::getInput()
{
	return this->m_input;
}

void Character::Init()
{
	this->m_position.x = PLAYER_START;
	this->m_position.y = PLAYER_START;
	
}

void Character::Move(float deltaTime)
{
	if (m_input.onShift) {
		if (m_input.onW) RunUp(deltaTime);
		if (m_input.onA) RunLeft(deltaTime);
		if (m_input.onS) RunDown(deltaTime);
		if (m_input.onD) RunRight(deltaTime);
	} else {
		if (m_input.onW) MoveUp(deltaTime);
		if (m_input.onA) MoveLeft(deltaTime);
		if (m_input.onS) MoveDown(deltaTime);
		if (m_input.onD) MoveRight(deltaTime);
	}
}
