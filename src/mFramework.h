#pragma once
#include "Framework.h"
#include "Brick.h"
#include "Chunk.h"
#include<vector>
#include "Ball.h"
#include "Bonus.h"

class Platform;
class Ball;

class mFramework : public Framework
{
private:
	int bricksInChunk = 9;
	int window_W = 0; //Aplication's size
	int window_H = 0; //standart size: 800x600
	bool screenType = 0; //standart type: false
	int GameChunksLines = 1;
	float scopeKoefW = (window_W/ 800), scopeKoefH = (window_H / 500);
	float brickW = 60 * scopeKoefW, brickH = 20 * scopeKoefH;//brick's size
	int tick = 0;
	float platfW = 100 * scopeKoefW, platfH = 30 * scopeKoefH;
	float ballW = 15 * scopeKoefW, ballH = 15 * scopeKoefH;
	bool redFlag = true;

private:
	void chunkClc();
	void chunkInit();

public:
	Brick* B;
	Sprite* BrickSpr_1;
	Sprite* BrickSpr_red;
	Sprite* BrickSpr_redBroken;
	Sprite* background;
	Sprite* Curb_0;
	Sprite* Curb_1;
	Sprite* BallSpr;
	Sprite* ChunkSpr;
	Sprite* PlatformSpr;
	Sprite* GameOver;
	Sprite* fast;
	Sprite* slow;
	Sprite* pauseSpr;

	Platform* platform;
	Ball* ball;
	Bonus* bonus;
	Brick* curb = new Brick[2];

	std::vector<Chunk*> chunks;
	std::vector<Brick*> bricks;

	
	int brickAmount = 0, chunkAmount = 0;
	const int chunkW = brickW * 3, chunkH = brickH * 3;
	const int chunkInLine = window_W / chunkW;//how much chunks in 1 line
	bool game = true;
	bool pause = false;

public:
	mFramework(int window_W = 800, int window_H = 600, bool screenType = false) : window_W(window_W < 800 ? 800 : window_W), window_H(window_H < 600 ? 600 : window_H), screenType(screenType) { }
	
	void getResolution(int& w, int& h);

	// no function calls are available here, this function should only return width, height and fullscreen values
	virtual void PreInit(int& width, int& height, bool& screenType) override;

	// return : true - ok, false - failed, application will exit
	virtual bool Init() override;

	virtual void Close() override;

	// return value: if true will exit the application
	virtual bool Tick()override;

	// param: xrel, yrel: The relative motion in the X/Y direction 
	// param: x, y : coordinate, relative to window
	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) override;

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) override;

	virtual void onKeyPressed(FRKey k) override;

	virtual void onKeyReleased(FRKey k) override;

	virtual const char* GetTitle() override { return "Arcanoid 2022"; };
};

