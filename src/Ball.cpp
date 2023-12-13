#include "Ball.h"
#include "mFramework.h"
#include "Chunk.h"
#include<iostream>
#include "Platform.h"
#include<unordered_set>

int Ball::killCount = 0;

//this is method is a part of Ball::move()
//here program collisions in chunks where ball is present
void Ball::collision(int i)
{
	
	bool Xcolll; 
	bool Ycolll;
	for (int j = 0; j < Framework->chunks[i]->insideMembers.size(); ++j)
	{
		Xcolll = false;
		Ycolll = false;
		if (Framework->chunks[i]->insideMembers[j]->show)
			if ((Framework->chunks[i]->insideMembers[j]->x <= x + width) && (Framework->chunks[i]->insideMembers[j]->x + Framework->chunks[i]->insideMembers[j]->width >= x) &&
				(Framework->chunks[i]->insideMembers[j]->y <= y + height) && (Framework->chunks[i]->insideMembers[j]->y + Framework->chunks[i]->insideMembers[j]->height >= y))
				{
					Xcolll = (((x + x2) / 2 >= Framework->chunks[i]->insideMembers[j]->x) && ((x + x2) / 2 <= Framework->chunks[i]->insideMembers[j]->x2));
					Ycolll = (((y + y2) / 2 >= Framework->chunks[i]->insideMembers[j]->y) && ((y + y2) / 2 <= Framework->chunks[i]->insideMembers[j]->y2));
					if (Xcolll)
					{
						if (!Ycolll)
						{
 							speedY *= -1;
							if (speedScale - 0.1 <= 0.4)
							{
								//don't change speed
							}
							else
								speedScale -= 0.1;
							if (Framework->chunks[i]->insideMembers[j]->unbreakable)
							{
								if (speedY < 0)
									y += -8;
								y += 8;
								continue;
							}
							Framework->chunks[i]->insideMembers[j]->show = false;
							++killCount;
							continue;
						}
						if (Ycolll)
						{
							std::cout << "Ball inside brick!!!! [" << j << "] chunk: " << i << std::endl;
							if (speedY < 0)
								y += -8;
							y += 8;
							continue;
						}
					}
					else
					{
						if (!Ycolll)
						{
							continue;
						}
						if (Ycolll)
						{
							speedX *= -1;
							if (std::abs(speedX) < 1)
							{
								if (speedX < 0)
									x += 10;
								x += -10;
							}
							if (Framework->chunks[i]->insideMembers[j]->unbreakable)
							{
								continue;
							}
							Framework->chunks[i]->insideMembers[j]->show = false;
							++killCount;
							continue;
						}
					}
			}
	}
}

//method for calculete start speed after mouse click 
void Ball::Start(float mouseX, float mouseY)
{
	if (start)
	{
	
		float tempX = mouseX - x, tempY = mouseY - y;
		speedX = (tempX / std::sqrt(tempX * tempX + tempY * tempY)) ;
		speedY = (tempY / std::sqrt(tempX * tempX + tempY * tempY));
		std::cout << "Start speedX : "<< speedX << " and speedY " << speedY << std::endl;//Start speedX and speedY
	}
}

float& Ball::bonusScaleGetSet()
{
	return bonusScale;
}

//this is methid calculete the all movement logic of the ball
//his collisions with bricks and platform 
//ball checks inside what chunks present his angles and them check collisions with bricks in that chunks
void Ball::move()
{
	bool Xcolll;
	bool Ycolll;
	std::unordered_set<int> chunkToCheck;

	if (start)
	{
		x = Framework->platform->x + Framework->platform->width / 2 - width / 2;
		y = Framework->platform->y - height;
		x2 = x + width;
		y2 = y + height;
	}

	else
	{
		Xcolll = false;
		Ycolll = false;
		if ((Framework->platform->x+10 <= x + width) && (Framework->platform->x + Framework->platform->width >= x + 10) &&
			(Framework->platform->y <= y + height) && (Framework->platform->y + Framework->platform->height >= y))
		{
			Xcolll = (((x + x2) / 2 >= Framework->platform->x) && ((x + x2) / 2 <= Framework->platform->x2));
			Ycolll = (((y + y2) / 2 >= Framework->platform->y) && ((y + y2) / 2 <= Framework->platform->y2));
			if (Xcolll)
			{
				if (!Ycolll)
				{
					speedY *= -1;
					if (speedScale + 0.15 > 3)
					{
						//don't change speed
					}
					else
						speedScale += 0.15;
				}
				if (Ycolll)
				{
					std::cout << "Ball inside platform!!!!" << std::endl;
					y += -30;
					speedY *= -1;
					speedX *= -1;
					if (speedScale + 0.15 > 3)
					{
						//don't change speed
					}
					else
						speedScale += 0.15;
				}
			}
			else
			{
				if (Ycolll)
				{
					speedX *= -1;
					speedY *= -1;
				}
			}
		}
	}

	chunkToCheck.insert(((x - Framework->curb[0].width) / Framework->chunkW) + (int)(y / Framework->chunkH) * Framework->chunkInLine);
	chunkToCheck.insert(((x2 - Framework->curb[0].width) / Framework->chunkW) + (int)(y / Framework->chunkH) * Framework->chunkInLine);
	chunkToCheck.insert(((x - Framework->curb[0].width) / Framework->chunkW) + (int)(y2 / Framework->chunkH) * Framework->chunkInLine);
	chunkToCheck.insert(((x2 - Framework->curb[0].width) / Framework->chunkW) + (int)(y2 / Framework->chunkH) * Framework->chunkInLine);

	for (int i : chunkToCheck)
	{
		if (i > Framework->chunks.size() - 1)
			continue;
		//std::cout << "chunks:" << i << "_";    // log to check the chunk with ball
		collision(i);
	}

		for (int b = 0; b < bonusFasts.size(); ++b)
		{
			if (getTickCount() - bonusFasts[b] >= 20000)
			{
				BonusSpeedX = abs(BonusSpeedX) - abs(speedX * 0.4);
				BonusSpeedY = abs(BonusSpeedY) - abs(speedY * 0.4);
				bonusFasts.erase(bonusFasts.begin() + b);
			}
		}

		for (int b = 0; b < bonusSlows.size(); ++b)
		{
			if (getTickCount() - bonusSlows[b] >= 20000)
			{
				BonusSpeedX = abs(BonusSpeedX) - abs(speedX * 0.4);
				BonusSpeedY = abs(BonusSpeedY) - abs(speedY * 0.4);
				bonusSlows.erase(bonusSlows.begin() + b);
			}
		}

	if (x + deltaX + width >= Framework->curb[1].x)
	{
		speedX *= -1;
		BonusSpeedX *= -1;
	}
	if (x + deltaX <= Framework->curb[0].x + Framework->curb[0].width)
	{
		speedX *= -1;
		BonusSpeedX *= -1;
	}
	if (y + deltaY <= 0)
	{
		speedY *= -1;
		BonusSpeedY *= -1;
	}
	if (y > window_h)
	//{
	//	speedY *= -1;
	//	BonusSpeedY *= -1; //uncoment this to take a godmod
	//}
		Framework->game = false;

	x += ((deltaX * speedX * speedScale) + (deltaX * BonusSpeedX));
	y += ((deltaY * speedY * speedScale ) + (deltaY * BonusSpeedY));
	x2 = x + width;
	y2 = y + height;
}


