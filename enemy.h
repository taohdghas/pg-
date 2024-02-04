#pragma once
#include <chrono>
#include <Novice.h>
#include "enemyBullet.h"
#include "Player.h"
class Enemy {
private:
    enemyBullet enemybullet;
    int posX_;
    int posY_;
    int radius_;
    int speed_;
    int enemyLife_;
    int enemyattack_;
    bool isAlive_;
    int respawnTime_; 
    int respawnTimer_; 
    std::chrono::steady_clock::time_point lastBulletTime_;
    bool invincible_; 
    std::chrono::steady_clock::time_point lastHitTime_;
    int enemyHandle =
        Novice::LoadTexture("./resource/condor.png");
public:
    Enemy(int posX, int posY,int radius, int speed,int enemyLife, int enemyattack,
        int respawnTime);
    void Update(Player& player);
    void Draw();
    void DecreaseLife();
    void UpdateBulletTimer();
    void Respawn();
    void Reset();
    int GetPosX() const { return posX_; }
    int GetPosY() const { return posY_; }
    int GetRadius() const { return radius_; }
    int GetEnemyLife() const { return enemyLife_; }
    bool CheckCollision(int playerX, int playerY, int playerRadius);
    bool checkEnemyBulletCollision(int playerX, int playerY, int playerRadius);
    void SetInvincible(bool invincible) { invincible_ = invincible; }
    bool IsInvincible() const { return invincible_; }
    void ResetInvincibleTime() { lastHitTime_ = std::chrono::steady_clock::now(); }
};

