#include "Item.h"

Item::Item(ItemType type)
{
	switch (type)
	{
	case ItemType::Item_INVALID:
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("Star.png");
		SetSize(ITEM_SIZE, ITEM_SIZE);
		consumable = false;
		hungerPerConsumable = 0;
		break;
	case ItemType::Item_LOG:
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("CD_log.png");
		SetSize(ITEM_SIZE, ITEM_SIZE);
		consumable = false;
		hungerPerConsumable = 0;
		break;
	case ItemType::Item_BERRIES:
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("CD_berries.png");
		SetSize(ITEM_SIZE, ITEM_SIZE);
		consumable = true;
		hungerPerConsumable = 3;
		break;
	case ItemType::Item_ROPE:
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("CD_rope.png");
		SetSize(ITEM_SIZE, ITEM_SIZE);
		consumable = false;
		hungerPerConsumable = 0;
		break;
	case ItemType::Item_WHEAT:
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("CD_cutgrass.png");
		SetSize(ITEM_SIZE, ITEM_SIZE);
		consumable = false;
		hungerPerConsumable = 0;
		break;
	case ItemType::Item_TWIG:
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("CD_twigs.png");
		SetSize(ITEM_SIZE, ITEM_SIZE);
		consumable = false;
		hungerPerConsumable = 0;
		break;
	case ItemType::Item_FRUIT:
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("CD_pumpkin.png");
		SetSize(ITEM_SIZE, ITEM_SIZE);
		consumable = true;
		hungerPerConsumable = 6;
		break;
	case ItemType::Item_ROCK:
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("Rocks.png");
		SetSize(ITEM_SIZE, ITEM_SIZE);
		consumable = false;
		hungerPerConsumable = 0;
		break;
	default:
		break;
	}
}

ItemType Item::GetType()
{
	return this->itemType;
}

bool Item::IsConsumable()
{
	return consumable;
}
