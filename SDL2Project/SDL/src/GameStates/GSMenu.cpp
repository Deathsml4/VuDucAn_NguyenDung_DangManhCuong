#include "GSMenu.h"

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Site-background-light.png");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("Adventure.png");
	std::shared_ptr<MouseButton> btnAdventure = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

	btnAdventure->SetSize(400 / 2, 150 / 2);
	btnAdventure->Set2DPosition((SCREEN_WIDTH - btnAdventure->GetWidth()) / 2, (SCREEN_HEIGHT - btnAdventure->GetHeight() - 140) / 2 - 10);
	btnAdventure->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(btnAdventure);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("Maze.png");
	std::shared_ptr<MouseButton> btnMaze = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

	btnMaze->SetSize(400 / 2, 150 / 2);
	btnMaze->Set2DPosition((SCREEN_WIDTH - btnMaze->GetWidth()) / 2, (SCREEN_HEIGHT - btnMaze->GetHeight()) / 2);
	btnMaze->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MAZE);
		});
	m_listButton.push_back(btnMaze);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.png");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(50, 40);
	btnClose->Set2DPosition(SCREEN_WIDTH - btnClose->GetWidth() - 10, 10);
	btnClose->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(btnClose);

	//Options game
	texture = ResourceManagers::GetInstance()->GetTexture("btn-options.png");
	std::shared_ptr<MouseButton> btnTutorial = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnTutorial->SetSize(400 / 2, 150 / 2);
	btnTutorial->Set2DPosition((SCREEN_WIDTH - btnTutorial->GetWidth()) / 2, SCREEN_HEIGHT / 2 + 40);
	btnTutorial->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_CREDIT);
		});
	m_listButton.push_back(btnTutorial);

	//CREDIT game
	

	// Music On
	texture = ResourceManagers::GetInstance()->GetTexture("Music_on.png");
	btnMusic = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnMusic->Set2DPosition(SCREEN_WIDTH - btnClose->GetWidth() - 10 - 60, 10);
	btnMusic->SetSize(50, 40);
	btnMusic->SetOnClick([this]() {
		if (checkMusic) {
			auto texture = ResourceManagers::GetInstance()->GetTexture("Music_off.png");
			btnMusic->SetTexture(texture);
			checkMusic = false;
			m_Sound->PauseSound();
		}
		else
		{
			auto texture = ResourceManagers::GetInstance()->GetTexture("Music_on.png");
			btnMusic->SetTexture(texture);
			checkMusic = true;
			m_Sound->ResumeSound();
		}
		});
	m_listButton.push_back(btnMusic);

	// Music Off
	/*texture = ResourceManagers::GetInstance()->GetTexture("btn_music.tga");
	btnMusicOff = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnMusicOff->Set2DPosition(SCREEN_WIDTH - btnClose->GetWidth() - 10 - 120, 10);
	btnMusicOff->SetSize(50, 50);
	btnMusicOff->SetOnClick([]() {
		std::shared_ptr<Sound> i = std::make_shared<Sound>();
		i->LoadSound("Data/Sounds/01_Main.wav");
		i->PlaySound();
		});
	m_listButton.push_back(btnMusicOff);*/

	// game title
	///Set Font
	m_textColor = { 255, 255, 255 };
	m_textGameName = std::make_shared<Text>("Data/Text/PlayTheGameBold-G9pm.ttf", m_textColor);
	m_textGameName->SetSize(400, 100);
	m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth()) / 2, SCREEN_HEIGHT / 2 - 300);
	m_textGameName->LoadFromRenderText("Dig It Up");

	m_Sound = std::make_shared<Sound>();
	m_Sound->LoadSound("Data/Sounds/01_Main.wav");
	m_Sound->PlaySound();

}

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSMenu::Pause()
{
	m_Sound->StopSound();
	// button close

}

void GSMenu::Resume()
{
	m_Sound->PlaySound();
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(SDL_Event& e)
{
}

void GSMenu::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}

	m_textGameName->Draw(renderer);
}
