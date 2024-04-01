#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "GameObject/Text.h"
#include "Sound.h"
class Sprite2D;
class SpriteAnimation;

class GSSetting :
	public GameStateBase
{
public:
	GSSetting();
	~GSSetting();

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

private:
	std::shared_ptr<Sprite2D>	m_background;
	SDL_Color m_textColor;
	TTF_Font* m_Font;
	std::shared_ptr<Text>		m_musicText;
	std::shared_ptr<Text>		m_effectText;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::list<std::shared_ptr<Text>>	m_listText;
	std::shared_ptr<SpriteAnimation> obj;
	std::shared_ptr<MouseButton> btnClose;
	std::shared_ptr<MouseButton> btnMusicMute;
	std::shared_ptr<MouseButton> btnEffectMute;

	float time = 0.0f;
	float m_Velocity = 10.0f;
};

