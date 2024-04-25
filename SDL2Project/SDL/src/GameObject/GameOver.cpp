#include "GameOver.h"

GameOver::GameOver(std::string time, std::string layer)
{
	auto texture = ResourceManagers::GetInstance()->GetTexture("imgpsh_fullsize_anim.png");
	textBox = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	textBox->SetSize(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	textBox->Set2DPosition(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);
	drawables.push_back(textBox);

	///Set Font
	title = std::make_shared<Text>("Data/Text/Consolas.ttf", textColorBlack);
	title->SetSize(120, 40);
	title->Set2DPosition(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2 - title->GetWidth())/2, SCREEN_HEIGHT / 4 + 60);
	title->LoadFromRenderText("Gameover!");
	drawables.push_back(title);

	message = std::make_shared<Text>("Data/Text/Consolas.ttf", textColorBlack);
	message->SetSize(300, 30);
	message->Set2DPosition(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2 - message->GetWidth()) / 2, SCREEN_HEIGHT / 4 + 90);
	message->LoadFromRenderText("Your adventure ended here!");
	drawables.push_back(message);

	finishTime = std::make_shared<Text>("Data/Text/Consolas.ttf", textColorRed);
	finishTime->SetSize(90, 20);
	finishTime->Set2DPosition(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2 - finishTime->GetWidth()) / 2, SCREEN_HEIGHT / 4 + 130);
	finishTime->LoadFromRenderText("Survived " + time);
	drawables.push_back(finishTime);

	finishLayer = std::make_shared<Text>("Data/Text/Consolas.ttf", textColorRed);
	finishLayer->SetSize(90, 20);
	finishLayer->Set2DPosition(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2 - finishLayer->GetWidth()) / 2, SCREEN_HEIGHT / 4 + 150);
	finishLayer->LoadFromRenderText("Passed " + layer + " pages");
	drawables.push_back(finishLayer);

	texture = ResourceManagers::GetInstance()->GetTexture("btn-play.png");
	restartBtm = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	restartBtm->SetSize(150, 40);
	restartBtm->Set2DPosition(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2 - restartBtm->GetWidth()) / 2, SCREEN_HEIGHT / 4 + 200);
	restartBtm->SetOnClick([]() {
		std::cout << "Restart" << std::endl;
		});
	drawables.push_back(restartBtm);

	texture = ResourceManagers::GetInstance()->GetTexture("btn-play.png");
	exitBtn = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	exitBtn->SetSize(150, 40);
	exitBtn->Set2DPosition(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2 - exitBtn->GetWidth()) / 2, SCREEN_HEIGHT / 4 + 250);
	exitBtn->SetOnClick([]() {
		std::cout << "Exit" << std::endl;
		});
	drawables.push_back(exitBtn);
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
