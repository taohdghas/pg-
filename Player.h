#pragma once
#include "Bullet.h"
#include <math.h>
#include <chrono>
#include <Novice.h>
class Player {
private:
    Bullet bullet;
    int x_;
    int y_;
    int radius_;
    int speed_;
    int playerLife_;
    bool isAlive_;
    bool invincible_; // 無敵状態かどうかを表すフラグ
    bool isGameover_;
    std::chrono::steady_clock::time_point lastHitTime_;
    int playerHandle =
        Novice::LoadTexture("./resource/player.png");
public:
    Player(int X, int Y, int radius, int speed, int playerLife);
    void Update(char* keys, char* prekeys);
    void Draw();
    void Reset();
    int GetX() const { return x_; }
    int GetY() const { return y_; }
    int GetRadius() const { return radius_; }
    void DecreaseLife() { playerLife_--; }
    int GetPlayerLife() const { return playerLife_; }
    //プレイヤーと敵の当たり判定
    bool CheckCollision(int enemyX, int enemyY, int enemyRadius);
    // 弾と敵の当たり判定
    bool CheckBulletEnemyCollision(int enemyX, int enemyY, int enemyRadius);
    void SetInvincible(bool invincible) { invincible_ = invincible; }
    bool IsInvincible() const { return invincible_; }
    void ResetInvincibleTime() { lastHitTime_ = std::chrono::steady_clock::now(); } 
    bool IsGameover() const { return isGameover_; }
};
