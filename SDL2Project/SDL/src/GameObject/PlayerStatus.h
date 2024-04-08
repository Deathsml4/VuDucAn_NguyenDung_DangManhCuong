#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<list>

#include "Sprite2D.h"
#include "SpriteAnimation.h"
#include "Define.h"
#include "Character.h"
#include "ResourceManagers.h"


class PlayerStatus
{
public:
	std::shared_ptr<Character> m_Target;

	std::shared_ptr<Sprite2D> craftColumn;
	std::shared_ptr<Sprite2D> inventoryBar;
	std::shared_ptr<SpriteAnimation> healthBar;
	std::shared_ptr<SpriteAnimation> hungerBar;
	std::shared_ptr<SpriteAnimation> thirstBar;

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

