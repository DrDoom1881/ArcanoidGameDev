#pragma once

#include "Object.h"
class Platform : public MoveableObject
{
public:
	Platform(int X, int Y, int width, int height) : MoveableObject(X, Y, width, height) { speedX = 0.95f; speedY = 0; };
	virtual void move() override;

	

};