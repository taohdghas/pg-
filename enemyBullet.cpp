#include "enemyBullet.h"
#include <Novice.h>
enemyBullet::enemyBullet(int X, int Y, int radius, int speed, int attack) {
	bulletX_ = X;
	bulletY_ = Y;
	radius_ = radius;
	speed_ = speed;
	attack_ = attack;
	isshot = false;
}
void enemyBullet::Update() {
	if (isshot) {
		bulletY_ += speed_;
	}
	if (bulletY_ > 720) {
		isshot = false;
	}
}
void enemyBullet::Draw() {
	Novice::DrawSprite(bulletX_, bulletY_, enemybulletHandle, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
	Novice::DrawEllipse(bulletX_, bulletY_, radius_, radius_, 1.0f, BLUE, kFillModeSolid);
}
void enemyBullet::Shot(int enemyX, int enemyY, int enemybulletSpeed) {
	bulletX_ = enemyX + 50;
	bulletY_ = enemyY + 50;
	speed_ = enemybulletSpeed;
	isshot = true;
}
void enemyBullet::Reset() {
	isshot = false;
}
void enemyBullet::Setenemybulletpos(int x, int y) {
	bulletX_ = x;
	bulletY_ = y;
}
void enemyBullet::Setenemybulletspeed(int speed) {
	speed_ = speed;
}