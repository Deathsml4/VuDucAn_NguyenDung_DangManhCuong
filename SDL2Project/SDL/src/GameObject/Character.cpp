#include "Character.h"
#include "Define.h"
#include <Item.h>

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
	//Initial status
	for (int i = 0; i < 15; i++) {
		std::shared_ptr <Item> newItem = std::make_shared<Item>(ItemType::Item_INVALID);
		status.inventory[i] = newItem;
		status.inventorySlot[i] = 0;
	}
	
	status.inventory[0] = std::make_shared<Item>(ItemType::Item_FRUIT);
	status.inventory[1] = std::make_shared<Item>(ItemType::Item_BERRIES);
	status.inventorySlot[0] = 1;
	status.inventorySlot[1] = 1;

	status.maxHP = 100;
	status.currentHP = 50;

	status.maxFood = 100;
	status.currentFood = 70;

	status.maxThirst = 100;
	status.currentThirst = 20;
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

void Character::DisplayInventory(SDL_Renderer* renderer)
{
	int index = 0;
	int pos = 163;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			status.inventory[index]->Set2DPosition(pos + 36*index, SCREEN_HEIGHT - 38);
			status.inventory[index]->Draw(renderer);
			index++;
		}
		pos = pos + 3;
	}
}
