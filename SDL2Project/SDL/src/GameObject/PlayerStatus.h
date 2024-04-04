#pragma once
#include<iostream>
#include<vector>

#include "Sprite2D.h"
#include "Define.h"
#include "Character.h"


class PlayerStatus
{
public:
	std::shared_ptr<Sprite2D> craftColumn;
	std::shared_ptr<Sprite2D> inventoryBar;
	std::shared_ptr<Sprite2D> healthBar;
	std::shared_ptr<Sprite2D> hungerBar;
	std::shared_ptr<Sprite2D> thirstBar;

	std::vector< std::shared_ptr<Sprite2D> > craftableItem;
	std::vector< std::shared_ptr<Sprite2D> > inventoryItem;

	PlayerStatus();
	PlayerStatus(std::shared_ptr<Character> character);
	~PlayerStatus();

	void Init();
	void Draw();
	void Update();
};

