#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <algorithm>

#include "ResourceManagers.h"
#include"SpriteAnimation.h"
#include "Camera.h"
#include"Define.h"
#include"ParticleSwarmOptimization.h"

const int LIVETIME = 600;
const int MAX_MOB_WIDTH = 80;
const int MAX_MOB_HEIGHT = 70;


enum class MopType {
	HOUND
};

class Mob : public SpriteAnimation
{
public:
	int maxHP;
	int currentHP;
	float attackCD = MOB_ATTACK_CD;
	float moveDuration = MOB_MOVE_DURATION;

	Vector2 tl, br;
	bool active; // dead or alive
	MopType type;
	bool killed; 

	float angleToPlayer;
	float distanceToPlayer;
	Vector2 moveGoal;

	Mob(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	void Spawn(SDL_Renderer* renderer);
	void Init() override;
	void AutoMove(float deltaTime);
	bool Attack();
	void OnHit();
	void DisplayHP(SDL_Renderer* renderer);
	void OnDead();
	Vector2 MakeDesicion();
	void MoveToward(Vector2 goal);
	void BounceBack(Vector2 goal);
	void UpdateTexture(Vector2 playerPos);
};

