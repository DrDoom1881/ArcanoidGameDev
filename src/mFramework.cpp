#include "mFramework.h"
#include "Platform.h"
#include"Ball.h"
#include"Brick.h"
#include "Bonus.h"
#include<iostream>
#include "time.h"

void mFramework::getResolution(int& w, int& h)
//in this method the program calculates how much chunks can be
//inside game zone and calculetes curbs, their widht and height
{
	w = window_W;
	h = window_H;
}
void mFramework::chunkClc()
{
	chunkAmount = (window_W / chunkW) * (window_H / chunkH);
	brickAmount = ((window_W / chunkW) * GameChunksLines) * bricksInChunk; 
	curb[0].width = (window_W - (window_W / chunkW) * chunkW) / 2;
	curb[0].height = window_H;
	curb[0].unbreakable = true;
	curb[1] = curb[0];
	curb[1].x = ((window_W / chunkW) * chunkW) + curb[0].width;
}

//in this method the program initializes chank-system
//chunks inside this system and game-bricks in this chunks and creating platform and ball
void mFramework::chunkInit()
{
//building chunks
	for (int i = 0; i < chunkAmount; ++i)
	{
		if (i == 0)
		{
			chunks.push_back(new Chunk(curb[1].width, 0, chunkW, chunkH));
			continue;
		}
		if (i > 0 && chunks[i - 1]->x + chunkW * 2 >= window_W)
		{
			chunks.push_back(new Chunk(curb[1].width, chunks[i - 1]->y + chunkH, chunkW, chunkH));
			continue;
		}
		chunks.push_back(new Chunk(chunks[i - 1]->x + chunkW, chunks[i - 1]->y, chunkW, chunkH));
	}

//building bricks and fill chuncks them
	for (int i = 0; i < brickAmount; ++i) {
		if (i == 0)
		{
			bricks.push_back(new Brick(curb[1].width, chunkH, brickW, brickH));
			for (int j = 0; j < chunkAmount; ++j)
			{
				if (bricks[i]->x >= chunks[j]->x && bricks[i]->y >= chunks[j]->y && bricks[i]->x2 <= chunks[j]->x2 && bricks[i]->y2 <= chunks[j]->y2)
					chunks[j]->insideMembers.push_back(bricks[i]);
			}
			continue;
		}
		if (i > 0 && bricks[i - 1]->x + brickW * 2 > window_W)
		{
			bricks.push_back(new Brick(curb[1].width, bricks[i - 1]->y + brickH, brickW, brickH));
			for (int j = 0; j < chunkAmount; ++j)
			{
				if (bricks[i]->x >= chunks[j]->x && bricks[i]->y >= chunks[j]->y && bricks[i]->x2 <= chunks[j]->x2 && bricks[i]->y2 <= chunks[j]->y2)
					chunks[j]->insideMembers.push_back(bricks[i]);
			}
			continue;
		}
		bricks.push_back(new Brick(bricks[i - 1]->x + brickW, bricks[i - 1]->y, brickW, brickH));
		for (int j = 0; j < chunkAmount; ++j)
		{
			if (bricks[i]->x >= chunks[j]->x && bricks[i]->y >= chunks[j]->y && bricks[i]->x2 <= chunks[j]->x2 && bricks[i]->y2 <= chunks[j]->y2)
				chunks[j]->insideMembers.push_back(bricks[i]);
		}		
	}

// creating platform and ball
	platform = new Platform((window_W / 2) - platfW / 2, window_H - chunkH - platfH, platfW, platfH);
	ball = new Ball(ballW, ballH);
}

void mFramework::PreInit(int& width, int& height, bool& Fullscreen)
	{
		width = window_W;
		height = window_H;
		Fullscreen = screenType;
	}

	bool mFramework::Init() {
		chunkClc();
		chunkInit();
		tick = getTickCount();
		if (game)
		{


			BrickSpr_1 = createSprite("data/15-Breakout-Tiles.png");
			BrickSpr_red = createSprite("data/07-Breakout-Tiles.png");
			BrickSpr_redBroken = createSprite("data/08-Breakout-Tiles.png");
			background = createSprite("data/background.jpg");
			BallSpr = createSprite("data/58-Breakout-Tiles.png");
			Curb_0 = createSprite("data/17-Breakout-Tiles_rot.png");
			Curb_1 = createSprite("data/17-Breakout-Tiles.png");
			ChunkSpr = createSprite("data/chunk.png");
			PlatformSpr = createSprite("data/56-Breakout-Tiles.png");
			GameOver = createSprite("data/game_over.jpg");
			fast = createSprite("data/42-Breakout-Tiles.png");
			slow = createSprite("data/41-Breakout-Tiles.png");
			pauseSpr = createSprite("data/myPauseButton.jpg");

			setSpriteSize(background, window_W, window_H);
			setSpriteSize(BrickSpr_1, brickW, brickH);
			setSpriteSize(BrickSpr_red, brickW, brickH);
			setSpriteSize(BrickSpr_redBroken, brickW, brickH);
			setSpriteSize(BallSpr, ball->width, ball->height);
			setSpriteSize(ChunkSpr, chunkW, chunkH);
			setSpriteSize(PlatformSpr, platfW, platfH);
			setSpriteSize(Curb_0, curb[0].width, curb[0].height);
			setSpriteSize(Curb_1, curb[1].width, curb[1].height);
			setSpriteSize(GameOver, window_W, window_H);
			setSpriteSize(fast, brickW, brickH);
			setSpriteSize(slow, brickW, brickH);
			setSpriteSize(pauseSpr, 2 * chunkW, chunkW);
		}
		else
			game = true;

		return true;
	}

	void mFramework::Close() 
	{
		destroySprite(BrickSpr_1);
		destroySprite(BrickSpr_red);
		destroySprite(BrickSpr_redBroken);
		destroySprite(background);
		destroySprite(BallSpr);
		destroySprite(Curb_0);
		destroySprite(Curb_1);
		destroySprite(ChunkSpr );
		destroySprite(PlatformSpr);
		destroySprite(GameOver);
		destroySprite(fast);
		destroySprite(slow);
		destroySprite(pauseSpr);

	}

	bool mFramework::Tick() {

		if (pause)
		{
			drawSprite(background, 0, 0);
			drawSprite(pauseSpr, (window_W / 2) - chunkW, (window_H / 2) - chunkH);
			return false;
		}

		if (!game)
		{
			drawSprite(GameOver, 0, 0);
			bricks.clear();
			chunks.clear();
			ball->killCount = 0;
			Brick::redCount = 0;
			if (bonus->getStatus())
				delete bonus;
			return false;
		}

		drawSprite(background, 0, 0);
		drawSprite(Curb_0, curb[0].x, curb[0].y);
		drawSprite(Curb_1, curb[1].x, curb[1].y);

		//this for need for draw a chunk-system
		 
		//for (int i = 0; i < chunkAmount; ++i) { 
		//	drawSprite(ChunkSpr, chunks[i]->x, chunks[i]->y);
		//}

		for (int i = 0; i < brickAmount; ++i)
		{
			if (bricks[i]->show)
				if (bricks[i]->red && bricks[i]->unbreakable)
				{
					drawSprite(BrickSpr_red, bricks[i]->x, bricks[i]->y);
				}
				else
					if (bricks[i]->red && !bricks[i]->unbreakable)
					{
						drawSprite(BrickSpr_redBroken, bricks[i]->x, bricks[i]->y);
					}
					else
						drawSprite(BrickSpr_1, bricks[i]->x, bricks[i]->y);
		}

		ball->move();
		drawSprite(BallSpr, ball->x, ball->y);

		platform->move();
		drawSprite(PlatformSpr, platform->x, platform->y);


		if (bonus->getStatus())
		{
			if (bonus->getEffect())
				drawSprite(fast, bonus->x, bonus->y);
			else
				drawSprite(slow, bonus->x, bonus->y);
		}

		if (getTickCount() - tick >= 15000)//15 sec
		{

			bonus = new Bonus(((rand() % (int)(window_W - brickW - curb[1].width)) + curb[0].width), (rand() % (int)(platfH - chunkH)), brickW, brickH, 0, -1);
			tick = getTickCount();
		}

		if (bonus->getStatus())
			bonus->move();

		if (ball->killCount == brickAmount - Brick::redCount && redFlag)
		{
			for (int i = 0; i < brickAmount; ++i)
			{
				bricks[i]->unbreakable = !bricks[i]->unbreakable;
			}
			redFlag = false;
		}

		if (ball->killCount == brickAmount)
			game = false;
		return false;
	}

		
	

	void mFramework::onMouseMove(int x, int y, int xrelative, int yrelative) 
	{
		if (ball->start)
		{
			ball->Start(x, y);
		}
	}

	void mFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {
		if (isReleased)
			return;
		if (!game)
		{
			if (button == FRMouseButton::LEFT || button == FRMouseButton::RIGHT)
			{
				Init();
			}
		}
		else
		{
			if (button == FRMouseButton::LEFT)
			{
				if (ball->start)
				{
					ball->start = false;
					ball->y += -5;
				}
			}
			if (button == FRMouseButton::MIDDLE)
				pause = !pause;
			
			
		}


	}

	void mFramework::onKeyPressed(FRKey k) {
		if (k == FRKey::RIGHT)
			platform->DeltaX() = platform->SpeedX();
		if (k == FRKey::LEFT)
			platform->DeltaX() = -1 * platform->SpeedX();
	}

	void mFramework::onKeyReleased(FRKey k) {
		if (k == FRKey::RIGHT)
			platform->DeltaX() = 0;
		if (k == FRKey::LEFT)
			platform->DeltaX() = 0;
	}