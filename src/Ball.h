#pragma once
#include "Object.h"
#include "Framework.h"
#include "vector"

class Ball : public MoveableObject
{
private:
	int window_w , window_h;
	float speedScale = 1;
	float bonusScale = 0;
	int bonusSlowTime = 0;
	int bonusFastTime = 0;

public:
	float BonusSpeedX = 0;
	float BonusSpeedY = 0;
	int slows = 0;
	int fasts = 0;
	bool start;
	static int killCount;
	std::vector<int> bonusSlows;
	std::vector<int> bonusFasts;

public:
	Ball( float width, float height, bool start = true) : MoveableObject(0, 0, width, height), start(start) {
		deltaX = 0.7f; 
		deltaY = 0.7f; 
		getScreenSize(window_w, window_h);
		

	};

	void move() override;
	void collision(int i);
	void redCollision(int i, int j);
	void Start(float mouseX, float mouseY);
	float& bonusScaleGetSet();
	
};

