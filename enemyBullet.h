#pragma once
#pragma once
#include <Novice.h>
class enemyBullet
{
private:
	int bulletX_;
	int bulletY_;
	int radius_;
	int speed_;
	int attack_;
	bool isshot;
	int enemybulletHandle =
		Novice::LoadTexture("./resource/enemybullet.png");
public:
	enemyBullet(int X, int Y, int radius, int speed, int attack);
	int GetenemybulletposX()const { return bulletX_; }
	int GetenemybulletposY()const { return bulletY_; }
	int Getenemybulletradius()const { return radius_; }
	int Getenemybulletspeed()const { return speed_; }
	int getenmeyAttack() const { return attack_; }
	void Update();
	void Draw();
	void Shot(int enemyX, int enemyY, int enemybulletSpeed);
	void Reset();
	void Setenemybulletpos(int x, int y);
	void Setenemybulletspeed(int speed);
};

