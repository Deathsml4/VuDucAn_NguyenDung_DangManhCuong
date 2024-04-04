#include "GSSetting.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"

GSSetting::GSSetting()
{
}


GSSetting::~GSSetting()
{
}


void GSSetting::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Site-background.jpg");

	// background

	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnClose->SetSize(50, 50);
	btnClose->Set2DPosition(SCREEN_WIDTH - 50, 10);
	btnClose->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(btnClose);
	///Set Font
	m_textColor = { 255, 255, 255 };

	m_musicText = std::make_shared<Text>("Data/sample.ttf", m_textColor);
	m_musicText->SetSize(350, 40);
	m_musicText->Set2DPosition((SCREEN_WIDTH - m_musicText->GetWidth()) / 5, SCREEN_HEIGHT / 2 - 175);
	m_musicText->LoadFromRenderText("Game music: ");
	m_listText.push_back(m_musicText);

	//Mute
	texture = ResourceManagers::GetInstance()->GetTexture("btn_help.tga");
	btnMusicMute = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnMusicMute->Set2DPosition((SCREEN_WIDTH - btnMusicMute->GetWidth()) / 2, SCREEN_HEIGHT / 2 - 200);
	btnMusicMute->SetSize(100, 100);
	btnMusicMute->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_CREDIT);
		});
	m_listButton.push_back(btnMusicMute);
	///Set Font
	m_effectText = std::make_shared<Text>("Data/sample.ttf", m_textColor);
	m_effectText->SetSize(350, 40);
	m_effectText->Set2DPosition((SCREEN_WIDTH - m_effectText->GetWidth()) / 5, SCREEN_HEIGHT / 2 - 25);
	m_effectText->LoadFromRenderText("Game effect: ");
	m_listText.push_back(m_effectText);

	//Mute
	texture = ResourceManagers::GetInstance()->GetTexture("btn_help.tga");
	btnEffectMute = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnEffectMute->Set2DPosition((SCREEN_WIDTH - btnEffectMute->GetWidth()) / 2, SCREEN_HEIGHT / 2 - 50);
	btnEffectMute->SetSize(100, 100);
	btnEffectMute->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_CREDIT);
		});
	m_listButton.push_back(btnEffectMute);
}

void GSSetting::Exit()
{
}


void GSSetting::Pause()
{

}
void GSSetting::Resume()
{
	// button close
	//auto texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	//button->SetTexture(texture);

}


void GSSetting::HandleEvents()
{
}

void GSSetting::HandleKeyEvents(SDL_Event& e)
{
	
}

void GSSetting::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSSetting::HandleMouseMoveEvents(int x, int y)
{
}

void GSSetting::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSSetting::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	//m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	//	obj->Draw(renderer);
	for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}

	for (auto it : m_listText) {
		it->Draw(renderer);
	}
}