#pragma once
#include<iostream>
#include<vector>

#include"BaseObject.h"

class MapObject
{
public:
	float x, y;
	bool active;
	bool visible;
	int type;
	float light[3]; // R, G, B
};

