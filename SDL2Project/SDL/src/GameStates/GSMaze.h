#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "Map.h"
#include "Sound.h"
#include"Character.h"
#include "PlayerStatus.h"

class Sprite2D;
class SpriteAnimation;

class GSMaze :
	public GameStateBase
{
public:
	GSMaze();
	~GSMaze();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;
	int m_KeyPress;
	int charHeight = 60;
	int charWidth = 31;
private:

	bool keyW = false;
	bool keyA = false;
	bool keyS = false;
	bool keyD = false;
	bool keyShift = false;
	bool keyEnter = false;
	std::shared_ptr<Sprite2D>	m_background;
	//std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::list<std::shared_ptr<Mob>> mobs; // list the mobs
	std::shared_ptr<Character> character;
	std::shared_ptr<SpriteAnimation> testChar;
	std::shared_ptr<PlayerStatus> playerStatus;
	std::shared_ptr<MouseButton> button;
	std::shared_ptr<Map> map;
	std::shared_ptr<Sound>		m_Sound;
	std::shared_ptr<MouseButton> btnMusicOn;

	float time = 0.0f;
	float m_Velocity = 10.0f;
};

