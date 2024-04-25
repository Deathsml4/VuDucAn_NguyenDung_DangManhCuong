#include "GameOver.h"

GameOver::GameOver(std::string time, std::string layout)
{
	auto texture = ResourceManagers::GetInstance()->GetTexture("imgpsh_fullsize_anim.png");
	textBox = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	textBox->SetSize(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	textBox->Set2DPosition(0, 0);
	drawables.push_back(textBox);
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
}

void GameOver::Draw()
{
}

void GameOver::Update()
{
}
