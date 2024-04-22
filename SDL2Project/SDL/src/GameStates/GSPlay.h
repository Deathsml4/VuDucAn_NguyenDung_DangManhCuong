#pragma once
#include <sstream>
#include <iomanip>

#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "Map.h"
#include "Sound.h"
#include"Character.h"
#include "PlayerStatus.h"

class Sprite2D;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

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

	void	UpdateNearestObject();
	void	DisplayNearestObject(SDL_Renderer* renderer);
	void	UpdateObstacle();
	void	KeyStateHandler(float deltaTime);
	void	InteractToObject();
	void	UpdateTime();
	void	GatherItem(MObject killedObj);
	void	UpdateHoldingItem();
	std::string formatTime(int timeH, int timeM, int timeS, int timeMs);
	float	GetDistance(float x1, float y1, float x2, float y2);
	std::string formatStatus(int HP, int Hunger, int Thirst);
	void	UpdatePlayerStatus();

	int m_KeyPress;
	float interactCD = INTERACT_CD;
	float holdItemCD = HOLD_ITEM_CD;
	float hungerDuration = HUNGER_DURATION;
	float thirstDuration = THIRST_DURATION;
	float healDuration = HEAL_DURATION;
	int timeH = 0;
	int timeM = 0;
	int timeS = 0;
	int timeMs = 0;
	int charHeight = 60;
	int charWidth = 31;
	int holdingItem = 0;
private:

	bool keyW = false;
	bool keyA = false;
	bool keyS = false;
	bool keyD = false;
	bool keyShift = false;
	bool keyE = false;
	bool keyBackspace = false;
	bool keyEnter = false;
	bool keyLeft = false;
	bool keyRight = false;

	Vector2 charPos;

	std::shared_ptr<Sprite2D>	m_background;
	//std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::list<std::shared_ptr<Mob>> mobs; // list the mobs
	std::shared_ptr<Character> character;
	std::shared_ptr<MapObject> nearestObject;
	std::shared_ptr<SpriteAnimation> testChar;
	std::shared_ptr<PlayerStatus> playerStatus;
	std::shared_ptr<MouseButton> button;
	std::shared_ptr<Map> map;
	std::shared_ptr<Sound>		m_Sound;
	std::shared_ptr<MouseButton> btnMusicOn;
	
	float time = 0.0f;
	float m_Velocity = 10.0f;
};

