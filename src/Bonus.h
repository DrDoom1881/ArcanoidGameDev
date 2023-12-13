#pragma once
#include "Object.h"
#include<random>
class Bonus :  public MoveableObject
{
public:
    
private:
    static bool status;
    static bool effect;
public:
    Bonus(float x, float y, float width, float height, float speedXx, float speedYy) : MoveableObject(x, y, width, height)
    {
        status = true;
        speedX = speedXx;
        speedY = speedYy;
        deltaX = 0;
        deltaY = -0.7f;
        if (rand() % 2 == 1)
            effect = true;
        else
            effect = false;

    }
    ~Bonus() { status = false; }
    virtual void move() override;
    const bool getStatus() const { return status; }
    const bool getEffect() const { return effect; }
private:
    void collision(int i);
};

