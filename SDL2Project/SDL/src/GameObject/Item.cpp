#include "Item.h"

Item::Item(ItemType type)
{
	switch (type)
	{
	case ItemType::Item_INVALID:
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("Boulder.png");
		consumable = false;
		hungerPerConsumable = 0;
		break;
	case ItemType::Item_LOG:
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("CD_log.png");
		consumable = false;
		hungerPerConsumable = 0;
		break;
	case ItemType::Item_BERRIES:
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("CD_berries.png");
		consumable = true;
		hungerPerConsumable = 3;
		break;
	case ItemType::Item_ROPE:
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("CD_rope.png");
		consumable = false;
		hungerPerConsumable = 0;
		break;
	case ItemType::Item_WHEAT:
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("CD_cutgrass.png");
		consumable = false;
		hungerPerConsumable = 0;
		break;
	case ItemType::Item_TWIG:
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("CD_twigs.png");
		consumable = false;
		hungerPerConsumable = 0;
		break;
	case ItemType::Item_FRUIT:
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("CD_pumpkin.png");
		consumable = true;
		hungerPerConsumable = 6;
		break;
	case ItemType::Item_ROCK:
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("Rocks.png");
		consumable = false;
		hungerPerConsumable = 0;
		break;
	default:
		break;
	}
}
