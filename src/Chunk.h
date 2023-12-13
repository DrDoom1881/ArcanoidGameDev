#pragma once
//#include "mFramework.h"
#include<vector>
#include "Brick.h"
struct Chunk 
{
	//int totalAmount;
	float width = 0 , height = 0;
	float x = 0, y = 0;
	float x2 = x + width, y2 = y + height;
	Chunk(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) { }
	std::vector<Brick*> insideMembers;
		
};
