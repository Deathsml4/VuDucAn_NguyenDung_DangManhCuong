#pragma once
#include "Sprite2D.h"
#include "ResourceManagers.h"
#include "Define.h"

enum class ItemType : int
{
	Item_INVALID = 0,
	Item_LOG = 1,
	Item_BERRIES = 2,
	Item_ROPE = 3,
	Item_WHEAT = 4,
	Item_TWIG = 5,
	Item_FRUIT = 6,
	Item_ROCK = 7,
};

class Item : public Sprite2D
{
private:
	
	int inventorySlot;
	bool consumable;
	int hungerPerConsumable;
public:
	ItemType itemType;
	//void Consume(Character* player);
	Item(ItemType type);
	ItemType GetType();
	bool IsConsumable();
};
