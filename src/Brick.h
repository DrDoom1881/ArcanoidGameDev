#pragma once
#include<unordered_set>
#include "Object.h"

class Brick : public Object
{
public:
	std::unordered_set<int> BlockBricks;
	bool red ;
public:
	static int redCount;
	//Brick() : Object(0, 0, 0, 0, false) { };
	Brick(int X = 0 , int Y = 0 ,float wight = 0, float height = 0) : Object(X, Y, wight, height) 
	{ 
		if (rand() % 10 == 1) // chance to spawn red bricks 
		{
			red = true;
			unbreakable = true;
			++redCount;
			
		}
		else
		{
			red = false;
		}

	};
	

};

