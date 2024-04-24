#pragma once
#include<iostream>
#include<map>
#include<list>

#include "CMath.h"
#include "BaseObject.h"
#include"SpriteAnimation.h"
#include "MapObject.h"
#include "Mob.h"
#include "Item.h"

struct PlayerInput
{
    bool onW = false;
    bool onA = false;
    bool onS = false;
    bool onD = false;
    bool onE = false;
    bool onBackspace = false;
    bool onEnter = false;
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

struct CharacterStatus {
    std::shared_ptr<Item>   inventory[15];
    int                     inventorySlot[15];
    int                     maxHP = 0;
    int                     maxFood = 0;
    int                     maxThirst = 0;
    int                     maxSpeed = 0;
    int                     maxAtk = 0;
    int                     maxInventorySize = 0;
    int                     maxHandSize = 0;

    int                     currentHP = 0;
    int                     currentFood = 0;
    int                     currentThirst = 0;
    int                     currentSpeed = 0;
    int                     currentAtk = 0;
    int                     currentInventorySpace = 0;
    int                     heldSlot = 0;
};

class Character : public SpriteAnimation
{
public:
    PlayerInput             m_input;
    std::map<int, char*>    m_nearbyEntity;
    SavePoint               m_playerLastSavePoint;
    std::map<int, char*>    m_inventory;

    //std::list<std::shared_ptr<MapObject> >    m_nearbyObjects;
    //std::list<std::shared_ptr<Mob> >          m_nearbyMobs;

    CharacterStatus status;

    Character();
    Character(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
    //Character(CharacterStatus baseStatus, std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);

    PlayerInput& getInput();
    void Init() override; 
    void Move(float deltaTime);
    void DisplayInventory(SDL_Renderer* renderer);
};
