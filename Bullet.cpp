#include "Bullet.h"
#include "Novice.h"
#include <math.h>
Bullet::Bullet(int X, int Y, int radius, int speed) {
    x_ = X;
    y_ = Y;
    radius_ = radius;
    speed_ = speed;
    isShot = false;
}
void Bullet::Update() {
    if (isShot) {
        y_ -= speed_;
    }
    if (y_ < 0) {
        isShot = false;
    }
}
void Bullet::Draw() {
    if (isShot) {
        Novice::DrawSprite(x_, y_, bulletHandle, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
    }
}
void Bullet::Shoot(int playerX, int playerY) {
    x_ = playerX + 30;
    y_ = playerY;
    isShot = true;
}
void Bullet::Reset() {
    isShot = false;
}