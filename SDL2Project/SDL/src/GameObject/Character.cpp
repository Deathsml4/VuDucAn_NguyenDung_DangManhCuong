#include "Character.h"
#include "Define.h"

Character::Character()
{
	this->m_position.x = PLAYER_START;
	this->m_position.y = PLAYER_START;
}

PlayerInput& Character::getInput()
{
	return this->m_input;
}
