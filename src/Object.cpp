#include "Object.h"
mFramework* Object::Framework = nullptr;
float& MoveableObject::DeltaX()
{
	return deltaX;
}

float& MoveableObject::SpeedX()
{
	return speedX;
}

float& MoveableObject::SpeedY()
{
	return speedY;
}

float& MoveableObject::DeltaY()
{
	return  deltaY;
}