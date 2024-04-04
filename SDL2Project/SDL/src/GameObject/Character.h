#pragma once
#include<iostream>
#include<map>

#include "CMath.h"
#include "BaseObject.h"
#include"SpriteAnimation.h"

struct PlayerInput
{
    bool onW = false;
    bool onA = false;
    bool onS = false;
    bool onD = false;
    bool onCtrl = false;
    bool onShift = false;
    bool onRightClick = false;
    bool onLeftClick = false;
    float scroll = 0;
    float angle = 0;
};

struct CharacterInventory
{
    int inventorySize = 0;
    int handInventorySize = 0;
    int holdingSlot = 0;
    std::map<int, char*> inventory;
    std::map<int, char*> hand;
};

struct SavePoint
{
    Vector2 savePosition;
    CharacterInventory saveInventory;
};

class Character:SpriteAnimation
{
public:
    PlayerInput             m_input;
    std::map<int, char*>    m_nearbyEntity;
    SavePoint               m_playerLastSavePoint;

    int                     m_maxHP = 0;
    int                     m_maxFood = 0;
    int                     m_maxThirst = 0;
    int                     m_maxSpeed = 0;
    int                     m_maxAtk = 0;
    int                     m_maxInventorySize = 0;
    int                     m_maxHandSize = 0;

    int                     m_currentHP = 0;
    int                     m_currentFood = 0;
    int                     m_currentThirst = 0;
    int                     m_currentSpeed = 0;
    int                     m_currentAtk = 0;
    int                     m_currentInventorySpace = 0;
    int                     m_heldSlot = 0;

    Character(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime);
    Character();
    PlayerInput& getInput();
};
