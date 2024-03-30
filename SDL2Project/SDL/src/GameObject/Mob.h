#pragma once
#include<iostream>

#include"BaseObject.h"

class Mob
{
public:
	float x1, y1, x2, y2;
	float rotation;
	float size;
	bool active; // dead or alive
	int type;
	int lifeTime; // disappear 
	int spawnTime; // spawn
	bool killed; 

	float angleToPlayer;
	float distanceToPlayer;
	float MoveToX, MoveToY;
};

