#pragma once
#include <Novice.h>
class Bullet
{
public:
    int x_;
    int y_;
    int radius_;
    int speed_;
    bool isShot;
    int bulletHandle =
        Novice::LoadTexture("./resource/bullet.png");
public:
    Bullet(int X, int Y, int radius, int speed);
    void Update();
    void Draw();
    void Reset();
    void Shoot(int playerX, int playerY);
    int GetbulletposX()const { return x_; }
    int GetbulletposY()const { return y_; }
    int Getbulletradius()const { return radius_; }
};