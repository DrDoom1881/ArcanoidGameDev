#pragma once
class mFramework;
class Object
{
public:
	static mFramework* Framework;
	float x = 0, y = 0;
	float width = 0, height = 0;
	float x2 = x + width, y2 = y + height;
	bool unbreakable;
	bool show;

public:
	Object(float X = 0, float Y = 0, float width = 0, float height = 0, bool unbreakable = false, bool show = true)
		: x(X), y(Y), width(width), height(height), unbreakable(unbreakable), show(show)
	{
		
	}
};
class  MoveableObject : public Object {
protected:
	float speedX = 0, speedY = 0;
	float deltaX = 0, deltaY = 0;
public:
	MoveableObject(float X = 0, float Y = 0, float width = 0, float height = 0)
		: Object(X, Y , width, height, true) { }
	virtual void move() = 0;
	float& DeltaX();
	float& DeltaY();
	float& SpeedX();
	float& SpeedY();
};
