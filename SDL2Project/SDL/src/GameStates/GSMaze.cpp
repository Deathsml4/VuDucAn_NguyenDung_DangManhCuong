#include "GSMaze.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"


GSMaze::GSMaze()
{
}


GSMaze::~GSMaze()
{
}


void GSMaze::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Wood_panelling_texture.png");

	// background

	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);
	// map
	map = std::make_shared<Map>(MapMode::MAP_MAZE);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.png");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 40);
	button->Set2DPosition(SCREEN_WIDTH - 50 - 10, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// Animation 
	texture = ResourceManagers::GetInstance()->GetTexture("sprite/375px-Player_Sneaky.png");
	character = std::make_shared<Character>(texture, 1, 15, 3, 0.2f);
	character->SetFlip(SDL_FLIP_HORIZONTAL);
	character->SetSize(CHAR_W, CHAR_H);
	character->Set2DPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	playerStatus = std::make_shared<PlayerStatus>(character);

	Camera::GetInstance()->SetTarget(character);

	//for (int i = 0; i < MOB_DENSITY; i++) {
	//	texture = ResourceManagers::GetInstance()->GetTexture("sprite/DST_Steam_Animated_Sticker_Chester.png");
	//	std::shared_ptr<Mob> mob = std::make_shared<Mob>(texture, 1, 10, 1, 0.05f);
	//	mob->SetFlip(SDL_FLIP_HORIZONTAL);
	//	mob->Init();
	//	mobs.push_back(mob);
	//}

	texture = ResourceManagers::GetInstance()->GetTexture("btn_music.png");
	btnMusicOn = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnMusicOn->Set2DPosition(SCREEN_WIDTH - button->GetWidth() - 10 - 60, 10);
	btnMusicOn->SetSize(50, 40);
	btnMusicOn->SetOnClick([]() {
		std::shared_ptr<Sound> i = std::make_shared<Sound>();
		i->LoadSound("Data/Sounds/01_Main.wav");
		i->PlaySound();
		});
	m_listButton.push_back(btnMusicOn);

	//m_listAnimation.push_back(character);

	m_Sound = std::make_shared<Sound>();
	m_Sound->LoadSound("Data/Sounds/17_Working_Through_Winter.wav");
	m_Sound->PlaySound();

	m_KeyPress = 0;

}

void GSMaze::Exit()
{
}


void GSMaze::Pause()
{

}
void GSMaze::Resume()
{

}


void GSMaze::HandleEvents()
{
}

void GSMaze::HandleKeyEvents(SDL_Event& e)
{
	////Key Down

	switch (e.type) {
	case SDL_KEYDOWN:

		switch (e.key.keysym.sym) {
		case SDLK_w:
			keyW = true;
			break;
		case SDLK_a:
			keyA = true;
			break;
		case SDLK_s:
			keyS = true;
			break;
		case SDLK_d:
			keyD = true;
			break;
		case SDLK_LSHIFT:
			keyShift = true;
			break;
		case SDLK_KP_ENTER:
			keyEnter = true;
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
		case SDLK_KP_ENTER:
			keyEnter = false;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void GSMaze::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSMaze::HandleMouseMoveEvents(int x, int y)
{
}

void GSMaze::Update(float deltaTime)
{
	Vector2 charPos = character->Get2DPosition();
	//Sprite update
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
	}

	//Keystate
	if (keyW) {
		/*auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/375px-Player_Sneaky.png");
		character = std::make_shared<Character>(texture, 3, 15, 3, 0.2f);
		character->SetTexture(texture);*/
		
		if (keyShift) {

			character->RunUp(deltaTime);
		}
		else {
			character->MoveUp(deltaTime);
		}
	}
	if (keyA) {
		/*auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/375px-Player_Sneaky.png");
		character = std::make_shared<Character>(texture, 2, 15, 3, 0.2f);
		character->SetTexture(texture);
		character->SetFlip(SDL_FLIP_HORIZONTAL);*/
		if (keyShift) {
			character->RunLeft(deltaTime);
		}
		else {
			character->MoveLeft(deltaTime);
		}
	}
	if (keyS) {
		/*auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/375px-Player_Sneaky.png");
		character = std::make_shared<Character>(texture, 3, 15, 3, 0.2f);
		character->SetTexture(texture);*/
		if (keyShift) {
			character->RunDown(deltaTime);
		}
		else {
			character->MoveDown(deltaTime);
		}
	}
	if (keyD) {
		/*auto texture = ResourceManagers::GetInstance()->GetTexture("sprite/375px-Player_Sneaky.png");
		character = std::make_shared<Character>(texture, 2, 15, 3, 0.2f);
		character->SetTexture(texture);
		character->SetFlip(SDL_FLIP_NONE);*/
		if (keyShift) {
			character->RunRight(deltaTime);
		}
		else {
			character->MoveRight(deltaTime);
		}
	}
	if (keyEnter) {

		if (map->isOnTheCheckPoint(charPos)) {
			map->chunks.clear();
			map->Init(MapMode::MAP_MAZE);
		}
	}
	character->Update(deltaTime);
	for (auto it : mobs)
	{
		it->AutoMove(deltaTime);
		it->Update(deltaTime);
	}

	//Update position of camera
	Camera::GetInstance()->Update(deltaTime);

	//Prevent player fall out of the map
	if (charPos.x <= MAP_START_X - 10)
		character->Set2DPosition(MAP_START_X - 10, charPos.y);
	if (charPos.y <= MAP_START_Y - 20)
		character->Set2DPosition(charPos.x, MAP_START_Y - 20);
	if (charPos.x >= MAP_START_X + CHUNK_UNITS * GRID_UNITS - CHAR_W)
		character->Set2DPosition(MAP_START_X + CHUNK_UNITS * GRID_UNITS - CHAR_W - 1, charPos.y);
	if (charPos.y >= MAP_START_Y + CHUNK_UNITS * GRID_UNITS - CHAR_H)
		character->Set2DPosition(charPos.x, MAP_START_Y + CHUNK_UNITS * GRID_UNITS - CHAR_H - 1);

	// Obstacles
	map->UpdateCollies();
	for (auto obstacle : map->collieBoxs) {
		Vector2 tl = obstacle.first;
		Vector2 br = obstacle.second;

		// Check for collision on the x-axis
		if (charPos.x + CHAR_W > tl.x && charPos.x < br.x) {
			// Check if character is above or below the obstacle
			if (charPos.y + CHAR_H > tl.y && charPos.y < br.y) {
				// Adjust character's y position based on collision
				if (charPos.y < br.y && charPos.y + CHAR_H > br.y) {
					if (keyW)
						character->Set2DPosition(charPos.x, br.y);
				}
				else if (charPos.y + CHAR_H > tl.y && charPos.y < tl.y) {
					if (keyS)
						character->Set2DPosition(charPos.x, tl.y - CHAR_H);
				}
			}
		}

		// Check for collision on the y-axis
		if (charPos.y + CHAR_H > tl.y && charPos.y < br.y) {
			// Check if character is to the left or right of the obstacle
			if (charPos.x + CHAR_W > tl.x && charPos.x < br.x) {
				// Adjust character's x position based on collision
				if (charPos.x < br.x && charPos.x + CHAR_W > br.x) {
					if (keyA)
						character->Set2DPosition(br.x, charPos.y);
				}
				else if (charPos.x + CHAR_W > tl.x && charPos.x < tl.x) {
					if (keyD)
						character->Set2DPosition(tl.x - CHAR_W, charPos.y);
				}
			}
		}
	}



}

void GSMaze::Draw(SDL_Renderer* renderer)
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

	for (auto it : playerStatus->drawables) {
		it->Draw(renderer);
	}
	map->DisplayHitboxs(renderer);
}