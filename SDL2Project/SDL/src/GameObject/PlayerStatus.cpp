#include "PlayerStatus.h"

PlayerStatus::PlayerStatus()
{
}

PlayerStatus::PlayerStatus(std::shared_ptr<Character> character)
{
	m_Target = character;

	auto texture = ResourceManagers::GetInstance()->GetTexture("Inventory_Empty.png");
	craftColumn = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	craftColumn->SetSize(680, 50);
	craftColumn->Set2DPosition(-680/2+25, 680/2);
	craftColumn->SetRotation(90);
	drawables.push_back(craftColumn);

	inventoryBar = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	inventoryBar->SetSize(680, 50);
	inventoryBar->Set2DPosition(150, SCREEN_HEIGHT - 50);
	drawables.push_back(inventoryBar);

	texture = ResourceManagers::GetInstance()->GetTexture("sprite/Heath_Badge1.png");
	healthBar = std::make_shared<SpriteAnimation>(texture, 1, 1, 24, 0.2f);
	healthBar->SetSize(50, 50);
	healthBar->Set2DPosition(SCREEN_WIDTH - 300, 150);
	drawables.push_back(healthBar);
}

PlayerStatus::~PlayerStatus()
{
}

void PlayerStatus::Init()
{
}

void PlayerStatus::Draw()
{
}

void PlayerStatus::Update()
{
	int hp = (m_Target->m_currentHP / m_Target->m_maxHP) * 100;
	int hunger = (m_Target->m_currentFood / m_Target->m_maxFood) * 100;
	int thirst = (m_Target->m_currentThirst / m_Target->m_maxThirst) * 100;
	std::map <int, char*> inventory = m_Target->m_inventory;


}
