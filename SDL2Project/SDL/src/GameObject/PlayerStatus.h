#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<list>

#include "BaseObject.h"
#include "Sprite2D.h"
#include "SpriteAnimation.h"
#include "Define.h"
#include "Character.h"
#include "ResourceManagers.h"
#include "Text.h"

class PlayerStatus
{
public:
	std::string time = "00:00:00:00";
	std::string statusLabel = "HP:    Hunger:    Thirst:   ";
	std::string statusData = "   XXX         XXX         XXX";

	std::shared_ptr<Character> m_Target;

	std::shared_ptr<Sprite2D> overlayA;

	std::shared_ptr<Sprite2D> craftColumn;
	std::shared_ptr<Sprite2D> inventoryBar;
	std::shared_ptr<Sprite2D> healthBar;
	std::shared_ptr<Sprite2D> hungerBar;
	std::shared_ptr<Sprite2D> thirstBar;

	SDL_Color textColorWhite = { 255, 255, 255 };
	SDL_Color textColorRed = { 255, 0, 0 };
	SDL_Color textColorGreen = { 3, 252, 23 };
	std::shared_ptr<Text> formattedTime;
	std::shared_ptr<Text> playerStatusLabel;
	std::shared_ptr<Text> playerStatusData;

	std::vector< std::shared_ptr<Sprite2D> > craftableItem;
	std::vector< std::shared_ptr<Sprite2D> > inventoryItem;

	std::list< std::shared_ptr<BaseObject>> drawables;
	

	PlayerStatus();
	PlayerStatus(std::shared_ptr<Character> character);
	~PlayerStatus();

	void Init();
	void Draw();
	void Update();
};

