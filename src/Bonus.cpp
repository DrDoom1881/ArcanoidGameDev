#include "Bonus.h"
#include "Platform.h"
#include "mFramework.h"
bool Bonus::status = false;
bool Bonus::effect = false;

//this is methid calculete the all movement logic of the bonuses
void Bonus::move()

{
	x += deltaX * speedX;
	y += deltaY * speedY;
	x2 = x + width;
	y2 = y + height;
}
