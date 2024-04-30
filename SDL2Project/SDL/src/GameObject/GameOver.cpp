#include "GameOver.h"

GameOver::GameOver(std::string time, std::string layer)
{
	auto texture = ResourceManagers::GetInstance()->GetTexture("imgpsh_fullsize_anim.png");
	textBox = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	textBox->SetSize(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	textBox->Set2DPosition(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);
	drawables.push_back(textBox);

	///Set Font
	title = std::make_shared<Text>(F_CONSOLAS, textColorBlack);
	title->SetSize(120, 40);
	title->Set2DPosition(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2 - title->GetWidth()) / 2, SCREEN_HEIGHT / 4 + 60);
	title->LoadFromRenderText("Gameover!");
	drawables.push_back(title);

	message = std::make_shared<Text>(F_CONSOLAS, textColorBlack);
	message->SetSize(300, 30);
	message->Set2DPosition(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2 - message->GetWidth()) / 2, SCREEN_HEIGHT / 4 + 90);
	message->LoadFromRenderText("Your adventure ended here!");
	drawables.push_back(message);

	finishTime = std::make_shared<Text>(F_CONSOLAS, textColorRed);
	finishTime->SetSize(170, 35);
	finishTime->Set2DPosition(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2 - finishTime->GetWidth()) / 2, SCREEN_HEIGHT / 4 + 120);
	finishTime->LoadFromRenderText("Survived " + time);
	drawables.push_back(finishTime);

	finishLayer = std::make_shared<Text>(F_CONSOLAS, textColorRed);
	finishLayer->SetSize(110, 35);
	finishLayer->Set2DPosition(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2 - finishLayer->GetWidth()) / 2, SCREEN_HEIGHT / 4 + 150);
	finishLayer->LoadFromRenderText("Passed " + layer + " pages");
	drawables.push_back(finishLayer);

	texture = ResourceManagers::GetInstance()->GetTexture(T_BUTTON_TRY_AGAIN);
	restartBtm = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	restartBtm->SetSize(180, 60);
	restartBtm->Set2DPosition(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2 - restartBtm->GetWidth()) / 2, SCREEN_HEIGHT / 4 + 180);
	restartBtm->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	drawables.push_back(restartBtm);

	texture = ResourceManagers::GetInstance()->GetTexture(T_BUTTON_BACK_TO_MENU);
	exitBtn = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	exitBtn->SetSize(180, 60);
	exitBtn->Set2DPosition(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2 - exitBtn->GetWidth()) / 2, SCREEN_HEIGHT / 4 + 240);
	exitBtn->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		//GameStateMachine::GetInstance()->PopState();
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
