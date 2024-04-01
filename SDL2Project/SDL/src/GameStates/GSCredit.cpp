#include "GSCredit.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"

GSCredit::GSCredit() : GameStateBase(StateType::STATE_CREDIT),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{})
{
}


GSCredit::~GSCredit()
{
}


void GSCredit::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("imgpsh_fullsize_anim.jpeg");

	// background

	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	m_textColor = { 255, 255, 0 };
	m_textStateName = std::make_shared<Text>("Data/MonsterGame-EjB9.ttf", m_textColor);
	m_textStateName->SetSize(400, 100);
	m_textStateName->Set2DPosition((SCREEN_WIDTH - m_textStateName->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 300);
	m_textStateName->LoadFromRenderText("State Credit");

	m_KeyPress = 0;

}

void GSCredit::Exit()
{
}


void GSCredit::Pause()
{

}
void GSCredit::Resume()
{
	// button close
	//auto texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	//button->SetTexture(texture);

}


void GSCredit::HandleEvents()
{
}

void GSCredit::HandleKeyEvents(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN)//&& e.key.repeat == 0) //For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			printf("MOVE LEFT");
			m_KeyPress |= 1;
			break;
		case SDLK_DOWN:
			printf("MOVE BACK");
			m_KeyPress |= 1 << 1;
			break;
		case SDLK_RIGHT:
			m_KeyPress |= 1 << 2;
			break;
		case SDLK_UP:
			m_KeyPress |= 1 << 3;
			break;
		default:
			break;
		}
	}
	////Key Up
	else if (e.type == SDL_KEYUP)//&& e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_KeyPress ^= 1;
			break;
		case SDLK_DOWN:
			m_KeyPress ^= 1 << 1;
			break;
		case SDLK_RIGHT:
			m_KeyPress ^= 1 << 2;
			break;
		case SDLK_UP:
			m_KeyPress ^= 1 << 3;
			break;
		default:
			break;
		}
	}
}

void GSCredit::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSCredit::HandleMouseMoveEvents(int x, int y)
{
}

void GSCredit::Update(float deltaTime)
{
	switch (m_KeyPress)//Handle Key event
	{
	default:
		break;
	}
	// Key State event

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation)
	{
		if (m_KeyPress == 1)
		{

			//	it->MoveLeft(deltaTime);
		}
		it->Update(deltaTime);
	}

	//Update position of camera
	//Camera::GetInstance()->Update(deltaTime);
	//obj->Update(deltaTime);
}

void GSCredit::Draw(SDL_Renderer* renderer)
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
	m_textStateName->Draw(renderer);
}