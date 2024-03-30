#pragma once
#include<iostream>
#include<vector>

#include"BaseObject.h"
#include"CMath.h"
#include"Define.h"

struct GridPoint{
	int terrain; //terrain type
	//std::vector <int> objects; //list the objects that are on this map
	//std::vector <int> entities;
	float light[3]; //R,G,B
	int creature[MAX_CREATURES];
};

class Map
{
public:

};

