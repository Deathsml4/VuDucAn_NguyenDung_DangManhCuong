#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<list>

#include "MouseButton.h"
#include "BaseObject.h"
#include "Sprite2D.h"
#include "SpriteAnimation.h"
#include "Define.h"
#include "Character.h"
#include "ResourceManagers.h"
#include "Text.h"
class GameOver
{
public:
	SDL_Color textColorWhite = { 255, 255, 255 };
	SDL_Color textColorRed = { 255, 0, 0 };
	SDL_Color textColorGreen = { 3, 252, 23 };
	SDL_Color textColorBlack = { 0, 0, 0 };
	std::shared_ptr<Sprite2D> textBox;
	std::shared_ptr<Sprite2D> imageA;
	std::shared_ptr<Text> Title;
	std::shared_ptr<Text> finishTime;
	std::shared_ptr<Text> finishLayer;
	std::shared_ptr<MouseButton> RestartBtm;
	std::shared_ptr<MouseButton> ExitBtn;
	std::list< std::shared_ptr<BaseObject>> drawables;

	GameOver(std::string time, std::string layout);
	~GameOver();

	void Init();
	void Draw();
	void Update();
};

