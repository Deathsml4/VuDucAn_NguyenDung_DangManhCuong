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

	m_textColor = { 255, 255, 0 };
	m_Adventure = std::make_shared<Text>("Data/Text/PlayTheGameBold-G9pm.ttf", m_textColor);
	m_Adventure->SetSize(200, 50);
	m_Adventure->Set2DPosition((SCREEN_WIDTH - m_Adventure->GetWidth()) * 2 / 5 + 30 , SCREEN_HEIGHT / 25);
	m_Adventure->LoadFromRenderText("Adventure");

	m_Maze = std::make_shared<Text>("Data/Text/PlayTheGameBold-G9pm.ttf", m_textColor);
	m_Maze->SetSize(100, 50);
	m_Maze->Set2DPosition((SCREEN_WIDTH - m_Maze->GetWidth()) * 4 / 5, SCREEN_HEIGHT / 25);
	m_Maze->LoadFromRenderText("Maze");

	int position_width = SCREEN_WIDTH / 10;
	int position_height = SCREEN_HEIGHT / 10;
	int button_width = 50;
	int button_height = 50;
	int distance_x = m_Maze->Get2DPosition().x + m_Maze->GetWidth() / 2 - m_Adventure->Get2DPosition().x - m_Adventure->GetWidth() / 2;

	texture = ResourceManagers::GetInstance()->GetTexture("Move.png");
	Move_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Move_button->SetSize(button_width * 2, button_height + 10);
	Move_button->Set2DPosition(position_width, position_height + 40);
	m_listButton_Map_1.push_back(Move_button);

	texture = ResourceManagers::GetInstance()->GetTexture("W.png");
	W_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	W_button->SetSize(button_width, button_height);
	W_button->Set2DPosition(position_width * 4 + 20,  SCREEN_HEIGHT / 5 - 50);
	m_listButton_Map_1.push_back(W_button);

	texture = ResourceManagers::GetInstance()->GetTexture("A.png");
	A_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	A_button->SetSize(button_width, button_height);
	A_button->Set2DPosition(position_width * 4 - 40, SCREEN_HEIGHT / 5 + 10);
	m_listButton_Map_1.push_back(A_button);

	texture = ResourceManagers::GetInstance()->GetTexture("S.png");
	S_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	S_button->SetSize(button_width, button_height);
	S_button->Set2DPosition(position_width * 4 + 20, SCREEN_HEIGHT / 5 + 10);
	m_listButton_Map_1.push_back(S_button);

	texture = ResourceManagers::GetInstance()->GetTexture("D.png");
	D_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	D_button->SetSize(button_width, button_height);
	D_button->Set2DPosition(position_width * 4 + 80, SCREEN_HEIGHT / 5 + 10);
	m_listButton_Map_1.push_back(D_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Destroy.png");
	Destroy_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Destroy_button->SetSize(button_width * 2, button_height + 10);
	Destroy_button->Set2DPosition(position_width, position_height * 3 + 10);
	m_listButton_Map_1.push_back(Destroy_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Backspace.png");
	Backspace_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Backspace_button->SetSize(button_width * 2, button_height + 10);
	Backspace_button->Set2DPosition(position_width * 4 - 5, position_height * 3 + 10);
	m_listButton_Map_1.push_back(Backspace_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Eat.png");
	Eat_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Eat_button->SetSize(button_width * 2, button_height + 10);
	Eat_button->Set2DPosition(position_width, position_height * 4.5 - 15	);
	m_listButton_Map_1.push_back(Eat_button);

	int distance_y = Eat_button->Get2DPosition().y - Destroy_button->Get2DPosition().y;

	texture = ResourceManagers::GetInstance()->GetTexture("E.png");
	E_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	E_button->SetSize(button_width, button_height);
	E_button->Set2DPosition(position_width * 4 + 20, position_height * 4.5 - 10);
	m_listButton_Map_1.push_back(E_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Choose-item.png");
	Choose_item_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Choose_item_button->SetSize(button_width * 2, button_height + 10);
	Choose_item_button->Set2DPosition(position_width, Eat_button->Get2DPosition().y + distance_y);
	m_listButton_Map_1.push_back(Choose_item_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Arrow-left.png");
	Arrow_left_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Arrow_left_button->SetSize(button_width, button_height);
	Arrow_left_button->Set2DPosition(position_width * 4 - 15, Eat_button->Get2DPosition().y + distance_y);
	m_listButton_Map_1.push_back(Arrow_left_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Arrow-right.png");
	Arrow_right_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Arrow_right_button->SetSize(button_width, button_height);
	Arrow_right_button->Set2DPosition(position_width * 4 + 55, Eat_button->Get2DPosition().y + distance_y);
	m_listButton_Map_1.push_back(Arrow_right_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Attack.png");
	Attack_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Attack_button->SetSize(button_width * 2, button_height + 10);
	Attack_button->Set2DPosition(position_width, Eat_button->Get2DPosition().y + distance_y * 2);
	m_listButton_Map_1.push_back(Attack_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Space.png");
	Space_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Space_button->SetSize(button_width * 2, button_height + 10);
	Space_button->Set2DPosition(position_width * 4 - 5, Eat_button->Get2DPosition().y + distance_y * 2);
	m_listButton_Map_1.push_back(Space_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Run.png");
	Run_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Run_button->SetSize(button_width * 2, button_height + 10);
	Run_button->Set2DPosition(position_width, Eat_button->Get2DPosition().y + distance_y * 3);
	m_listButton_Map_1.push_back(Run_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Left-shift.png");
	L_Shift_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	L_Shift_button->SetSize(button_width * 2, button_height + 10);
	L_Shift_button->Set2DPosition(position_width * 4 - 5, Eat_button->Get2DPosition().y + distance_y * 3);
	m_listButton_Map_1.push_back(L_Shift_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Pass_over_gate.png");
	Pass_over_gate_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Pass_over_gate_button->SetSize(button_width * 2, button_height + 10);
	Pass_over_gate_button->Set2DPosition(position_width, Eat_button->Get2DPosition().y + distance_y * 4);
	m_listButton_Map_1.push_back(Pass_over_gate_button);

	texture = ResourceManagers::GetInstance()->GetTexture("Enter.png");
	Enter_button = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Enter_button->SetSize(button_width * 2, button_height + 10);
	Enter_button->Set2DPosition(position_width * 4 - 5, Eat_button->Get2DPosition().y + distance_y * 4);
	m_listButton_Map_1.push_back(Enter_button);

	texture = ResourceManagers::GetInstance()->GetTexture("W.png");
	W_button_1 = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	W_button_1->SetSize(button_width, button_height);
	W_button_1->Set2DPosition(position_width * 4 + distance_x + 20, SCREEN_HEIGHT / 5 - 50);
	m_listButton_Map_1.push_back(W_button_1);

	texture = ResourceManagers::GetInstance()->GetTexture("A.png");
	A_button_1 = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	A_button_1->SetSize(button_width, button_height);
	A_button_1->Set2DPosition(position_width * 4 + distance_x - 40, SCREEN_HEIGHT / 5 + 10);
	m_listButton_Map_1.push_back(A_button_1);

	texture = ResourceManagers::GetInstance()->GetTexture("S.png");
	S_button_1 = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	S_button_1->SetSize(button_width, button_height);
	S_button_1->Set2DPosition(position_width * 4 + distance_x + 20, SCREEN_HEIGHT / 5 + 10);
	m_listButton_Map_1.push_back(S_button_1);

	texture = ResourceManagers::GetInstance()->GetTexture("D.png");
	D_button_1 = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	D_button_1->SetSize(button_width, button_height);
	D_button_1->Set2DPosition(position_width * 4 + distance_x + 80, SCREEN_HEIGHT / 5 + 10);
	m_listButton_Map_1.push_back(D_button_1);

	texture = ResourceManagers::GetInstance()->GetTexture("Enter.png");
	Enter_button_1 = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	Enter_button_1->SetSize(button_width * 2, button_height + 10);
	Enter_button_1->Set2DPosition(position_width * 4 + distance_x - 5, Eat_button->Get2DPosition().y + distance_y * 4);
	m_listButton_Map_1.push_back(Enter_button_1);

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

	//Update position_width of camera
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
	m_Adventure->Draw(renderer);
	m_Maze->Draw(renderer);
}