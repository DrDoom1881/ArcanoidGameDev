#include "Platform.h"
#include "Brick.h"
#include "mFramework.h"
#include<iostream>

//this is methid calculete the all movement logic of the platform
//and his collisions with bonuses
void Platform::move() 

{
	if (x + deltaX + width >= Framework->curb[1].x)
		x = Framework->curb[1].x - width;
	if (x + deltaX <= Framework->curb[0].x + Framework->curb[0].width)
		x = Framework->curb[0].x + Framework->curb[0].width;
	x += deltaX;
	x2 = x + width;
	if (Framework->bonus->getStatus())
	{
		bool Xcolll = false;
		bool Ycolll = false;
			if ((Framework->bonus->x <= x + width) && (Framework->bonus->x + Framework->bonus->width >= x) &&
				(Framework->bonus->y <= y + height) && (Framework->bonus->y + Framework->bonus->height >= y))
			{
				if (Framework->bonus->getEffect())
				{
					if (abs(Framework->ball->BonusSpeedX + (0.4 * Framework->ball->SpeedX())) > abs(Framework->ball->SpeedX() * 2))
						if (abs(Framework->ball->BonusSpeedY + (0.4 * Framework->ball->SpeedY())) > abs(Framework->ball->SpeedY() * 2))
					{
						//don't chenge speed
					}
					else
					{
						Framework->ball->BonusSpeedX = abs(Framework->ball->BonusSpeedX) + (0.4 * Framework->ball->SpeedX());
						Framework->ball->BonusSpeedY = abs(Framework->ball->BonusSpeedY) + (0.4 * Framework->ball->SpeedY());
						Framework->ball->bonusFasts.push_back(getTickCount());
					}
					std::cout << "FAST BONUS was taken" << std::endl;
					delete Framework->bonus;
										
				}
				else
				{
					if (Framework->ball->BonusSpeedX + (-0.4 * Framework->ball->SpeedX()) < Framework->ball->SpeedX() / 2)
						if (Framework->ball->BonusSpeedY + (-0.4 * Framework->ball->SpeedY()) < Framework->ball->SpeedY() / 2)
					{
						//don't chenge speed
					}
					else
					{
						Framework->ball->BonusSpeedX = abs(Framework->ball->BonusSpeedX) - (0.4 * Framework->ball->SpeedX());
						Framework->ball->BonusSpeedY = abs(Framework->ball->BonusSpeedY) - (0.4 * Framework->ball->SpeedY());
						Framework->ball->bonusSlows.push_back(getTickCount());
					}
					std::cout << "SLOW BONUS was taken" << std::endl;
					delete Framework->bonus;
				}
					
			}
	}



}




