#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"


GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Wood_panelling_texture.png");

	// background
	
	m_background = std::make_shared<Sprite2D>( texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);
	// map
	map = std::make_shared<Map>();
	
	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.png");
	button = std::make_shared<MouseButton>( texture, SDL_FLIP_NONE);
	button->SetSize(charWidth, charHeight);
	button->Set2DPosition(SCREEN_WIDTH - 50 - 10, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

   // Animation 
	texture = ResourceManagers::GetInstance()->GetTexture("sprite/351px-Frog_Webber_jump_down.png");
	character = std::make_shared<Character>(texture, 1, 15, 1, 0.2f);
	character->SetFlip(SDL_FLIP_HORIZONTAL);
	character->SetSize(40, 50);
	character->Set2DPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

	Camera::GetInstance()->SetTarget(character);
	for (int i = 0; i < MOB_DENSITY; i++) {
		texture = ResourceManagers::GetInstance()->GetTexture("sprite/120px-Hound_Run.png");
		mob = std::make_shared<Mob>(texture, 1, 7, 1, 0.05f);
		mob->SetFlip(SDL_FLIP_HORIZONTAL);
		mob->Init();
		mobs.push_back(mob);
	}
	
	//m_listAnimation.push_back(character);

	m_Sound = std::make_shared<Sound>();
	m_Sound->LoadSound("Data/Sounds/17_Working_Through_Winter.wav");
	m_Sound->PlaySound();

	m_KeyPress = 0;
	
}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{

}
void GSPlay::Resume()
{
	// button close
	//auto texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	//button->SetTexture(texture);

}


void GSPlay::HandleEvents()
{
}

bool keyW = false;
bool keyA = false;
bool keyS = false;
bool keyD = false;
bool keyShift = false;

void GSPlay::HandleKeyEvents(SDL_Event& e)
{
	////Key Down
	
	switch (e.type) {
	case SDL_KEYDOWN:
		
		switch (e.key.keysym.sym) {
		case SDLK_w:
			if (e.key.keysym.mod & KMOD_LSHIFT) {
				keyShift = true;
			}

			keyW = true;
			break;
		case SDLK_a:
			if (e.key.keysym.mod & KMOD_LSHIFT) {
				keyShift = true;
			}

			keyA = true;
			break;
		case SDLK_s:
			if (e.key.keysym.mod & KMOD_LSHIFT) {
				keyShift = true;
			}

			keyS = true;
			break;
		case SDLK_d:
			if (e.key.keysym.mod & KMOD_LSHIFT) {
				keyShift = true;
			}

			keyD = true;
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_w:
			keyW = false;
			break;
		case SDLK_a:
			keyA = false;
			break;
		case SDLK_s:
			keyS = false;
			break;
		case SDLK_d:
			keyD = false;
			break;
		case SDLK_LSHIFT:
			keyShift = false;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void GSPlay::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
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
	if (keyW) {
		auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/342px-Frog_Webber_jump_up2.png");
		character->SetTexture(texture);
		if (keyShift) {

			character->RunUp(deltaTime);
		}
		else {
			character->MoveUp(deltaTime);
		}
	}
	if (keyA) {
		auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/357px-Frog_Webber_jump_side2.png");
		character->SetTexture(texture);
		character->SetFlip(SDL_FLIP_HORIZONTAL);
		if (keyShift) {
			character->RunLeft(deltaTime);
		}
		else {
			character->MoveLeft(deltaTime);
		}
	}
	if (keyS) {
		auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/351px-Frog_Webber_jump_down.png");
		character->SetTexture(texture);
		if (keyShift) {
			character->RunDown(deltaTime);
		}
		else {
			character->MoveDown(deltaTime);
		}
	}
	if (keyD) {
		auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/357px-Frog_Webber_jump_side2.png");
		character->SetTexture(texture);		
		character->SetFlip(SDL_FLIP_NONE);
		if (keyShift) {
			character->RunRight(deltaTime);
		}
		else {
			character->MoveRight(deltaTime);
		}
	}
	character->Update(deltaTime);
	for (auto it : mobs)
	{

		it->Update(deltaTime);
	}

	//Update position of camera
	Camera::GetInstance()->Update(deltaTime);
	//obj->Update(deltaTime);
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	map->Draw(renderer);
	for (auto it : mobs)
	{

		it->Draw(renderer);
	}

	character->Draw(renderer);
	
	//testChar->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
//	obj->Draw(renderer);
	for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}
}