#include "PlayerStatus.h"

PlayerStatus::PlayerStatus()
{
}

PlayerStatus::PlayerStatus(std::shared_ptr<Character> character)
{
	m_Target = character;

	auto texture = ResourceManagers::GetInstance()->GetTexture("realistic smoke overlay.png");
	overlayA = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	overlayA->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	overlayA->Set2DPosition(0,0);
	drawables.push_back(overlayA);
	
	overlayB = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	overlayB->SetSize(SCREEN_WIDTH, SCREEN_WIDTH);
	overlayB->Set2DPosition(0, 0);
	overlayB->SetRotation(90);
	drawables.push_back(overlayB);

	texture = ResourceManagers::GetInstance()->GetTexture("Inventory_Empty.png");
	craftColumn = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	craftColumn->SetSize(680, 50);
	craftColumn->Set2DPosition(-680/2+25, 680/2);
	craftColumn->SetRotation(90);
	drawables.push_back(craftColumn);

	inventoryBar = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	inventoryBar->SetSize(680, 50);
	inventoryBar->Set2DPosition(150, SCREEN_HEIGHT - 50);
	drawables.push_back(inventoryBar);

	texture = ResourceManagers::GetInstance()->GetTexture("sprite/Heath_Badge.png");
	//healthBar = std::make_shared<SpriteSheet>(texture, 1, 1, 24, 0.2f);
	healthBar = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	healthBar->SetSize(50, 50);
	healthBar->Set2DPosition(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100);
	drawables.push_back(healthBar);

	texture = ResourceManagers::GetInstance()->GetTexture("sprite/Hunger_Badge.png");
	//hungerBar = std::make_shared<SpriteSheet>(texture, 1, 1, 24, 0.2f);
	hungerBar = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	hungerBar->SetSize(50, 50);
	hungerBar->Set2DPosition(SCREEN_WIDTH - 125, SCREEN_HEIGHT - 52);
	drawables.push_back(hungerBar);

	texture = ResourceManagers::GetInstance()->GetTexture("sprite/Hunger_Badge.png");
	//thirstBar = std::make_shared<SpriteSheet>(texture, 1, 1, 24, 0.2f);
	thirstBar = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	thirstBar->SetSize(50, 50);
	thirstBar->Set2DPosition(SCREEN_WIDTH - 75, SCREEN_HEIGHT - 52);
	drawables.push_back(thirstBar);

	///Set Font
	formattedTime = std::make_shared<Text>("Data/Text/Consolas.ttf", textColorBlack);
	formattedTime->SetSize(120, 40);
	formattedTime->Set2DPosition(SCREEN_WIDTH - formattedTime->GetWidth() - 190, 10);
	formattedTime->LoadFromRenderText(time);
	drawables.push_back(formattedTime);

	playerStatusLabel = std::make_shared<Text>("Data/Text/Consolas.ttf", textColorBlack);
	playerStatusLabel->SetSize(250, 20);
	playerStatusLabel->Set2DPosition(100, 10);
	playerStatusLabel->LoadFromRenderText(statusLabel);
	drawables.push_back(playerStatusLabel);

	playerStatusData = std::make_shared<Text>("Data/Text/Consolas.ttf", textColorRed);
	playerStatusData->SetSize(250, 20);
	playerStatusData->Set2DPosition(100, 10);
	playerStatusData->LoadFromRenderText(statusData);
	drawables.push_back(playerStatusData);
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
	formattedTime->LoadFromRenderText(time);
	playerStatusData->LoadFromRenderText(statusData);
}