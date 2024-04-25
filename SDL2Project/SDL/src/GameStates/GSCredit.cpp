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
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.png");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 40);
	button->Set2DPosition(SCREEN_WIDTH - 60, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	texture = ResourceManagers::GetInstance()->GetTexture("Move.png");
	Move_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Move_button->SetSize(120, 70);
	Move_button->Set2DPosition(SCREEN_WIDTH / 5 + 10, SCREEN_HEIGHT * 2 / 8 - 50);
	m_listButton_Map_1.push_back(Move_button);

	texture = ResourceManagers::GetInstance()->GetTexture("W.png");
	W_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	W_button->SetSize(60, 60);
	W_button->Set2DPosition(SCREEN_WIDTH * 7 / 10,  SCREEN_HEIGHT / 5 - 50);
	m_listButton_Map_1.push_back(W_button);

	texture = ResourceManagers::GetInstance()->GetTexture("A.png");
	A_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	A_button->SetSize(60, 60);
	A_button->Set2DPosition(SCREEN_WIDTH * 7 / 10 - 70, SCREEN_HEIGHT / 5 + 20);
	m_listButton_Map_1.push_back(A_button);

	texture = ResourceManagers::GetInstance()->GetTexture("S.png");
	S_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	S_button->SetSize(60, 60);
	S_button->Set2DPosition(SCREEN_WIDTH * 7 / 10, SCREEN_HEIGHT / 5 + 20);
	m_listButton_Map_1.push_back(S_button);

	texture = ResourceManagers::GetInstance()->GetTexture("D.png");
	D_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	D_button->SetSize(60, 60);
	D_button->Set2DPosition(SCREEN_WIDTH * 7 / 10 + 70, SCREEN_HEIGHT / 5 + 20);
	m_listButton_Map_1.push_back(D_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Destroy.png");
	Destroy_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Destroy_button->SetSize(120, 70);
	Destroy_button->Set2DPosition(SCREEN_WIDTH / 5 + 10, SCREEN_HEIGHT * 3 / 8 - 20);
	m_listButton_Map_1.push_back(Destroy_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Backspace.png");
	Backspace_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Backspace_button->SetSize(120, 70);
	Backspace_button->Set2DPosition(SCREEN_WIDTH * 7 / 10 - 30, SCREEN_HEIGHT * 3 / 8 - 20);
	m_listButton_Map_1.push_back(Backspace_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Eat.png");
	Eat_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Eat_button->SetSize(120, 70);
	Eat_button->Set2DPosition(SCREEN_WIDTH / 5 + 10, SCREEN_HEIGHT * 4 / 8 - 20);
	m_listButton_Map_1.push_back(Eat_button);

	texture = ResourceManagers::GetInstance()->GetTexture("E.png");
	E_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	E_button->SetSize(60, 60);
	E_button->Set2DPosition(SCREEN_WIDTH * 7 / 10, SCREEN_HEIGHT * 4 / 8 - 20);
	m_listButton_Map_1.push_back(E_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Choose-item.png");
	Choose_item_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Choose_item_button->SetSize(120, 70);
	Choose_item_button->Set2DPosition(SCREEN_WIDTH / 5 + 10, SCREEN_HEIGHT * 5 / 8 - 20);
	m_listButton_Map_1.push_back(Choose_item_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Arrow-left.png");
	Arrow_left_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Arrow_left_button->SetSize(60, 60);
	Arrow_left_button->Set2DPosition(SCREEN_WIDTH * 7 / 10 - 40, SCREEN_HEIGHT * 5 / 8 - 20);
	m_listButton_Map_1.push_back(Arrow_left_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Arrow-right.png");
	Arrow_right_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Arrow_right_button->SetSize(60, 60);
	Arrow_right_button->Set2DPosition(SCREEN_WIDTH * 7 / 10 + 40, SCREEN_HEIGHT * 5 / 8 - 20);
	m_listButton_Map_1.push_back(Arrow_right_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Attack.png");
	Attack_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Attack_button->SetSize(120, 70);
	Attack_button->Set2DPosition(SCREEN_WIDTH / 5 + 10, SCREEN_HEIGHT * 6 / 8 - 20);
	m_listButton_Map_1.push_back(Attack_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Space.png");
	Space_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Space_button->SetSize(120, 70);
	Space_button->Set2DPosition(SCREEN_WIDTH * 7 / 10 - 30, SCREEN_HEIGHT * 6 / 8 - 20);
	m_listButton_Map_1.push_back(Space_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Run.png");
	Run_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Run_button->SetSize(120, 70);
	Run_button->Set2DPosition(SCREEN_WIDTH / 5 + 10, SCREEN_HEIGHT * 7 / 8 - 20);
	m_listButton_Map_1.push_back(Run_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Left-shift.png");
	L_Shift_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	L_Shift_button->SetSize(120, 70);
	L_Shift_button->Set2DPosition(SCREEN_WIDTH * 7 / 10 - 30, SCREEN_HEIGHT * 7 / 8 - 20);
	m_listButton_Map_1.push_back(L_Shift_button);

	m_textColor = { 255, 255, 0 };
	m_textStateName = std::make_shared<Text>("Data/Text/PlayTheGameBold-G9pm.ttf", m_textColor);
	m_textStateName->SetSize(200, 50);
	m_textStateName->Set2DPosition((SCREEN_WIDTH - m_textStateName->GetWidth()) / 2 , SCREEN_HEIGHT / 20);
	m_textStateName->LoadFromRenderText("Tutorial");

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

	for (auto it : m_listButton_Map_1)
	{
		it->Draw(renderer);
	}

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