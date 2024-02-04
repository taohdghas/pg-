#include "Player.h"
#include <Novice.h>
Player::Player(int X, int Y, int radius, int speed, int playerLife)
    : bullet(X, Y, 10, 10){
    x_ = X;
    y_ = Y;
    radius_ = radius;
    speed_ = speed;
    playerLife_ = playerLife;
    isAlive_ = true;
    isGameover_ = false;
    invincible_ = false;
}
void Player::Update(char* keys, char* prekeys) {
    if (keys[DIK_W] && y_ > 0) {
        y_ -= speed_;
    }
    if (keys[DIK_S] && y_ < 650 - radius_ ) {
        y_ += speed_;
    }
    if (keys[DIK_A] && x_ > 0) {
        x_ -= speed_;
    }
    if (keys[DIK_D] && x_ < 1220 - radius_ ) {
        x_+= speed_;
    }
    auto currentTime = std::chrono::steady_clock::now();
    auto invincibleDuration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastHitTime_).count();
    if (invincibleDuration < 1000) { 
        invincible_ = true;
    }
    else {
        invincible_ = false;
    }
    bullet.Update();
    if (prekeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0 && !bullet.isShot) {
        bullet.Shoot(x_, y_);
    }
    if (playerLife_ <= 0) {
        isGameover_ = true;
    }
    if (isGameover_) {
        Reset();
    }
}
void Player::Draw() {
    Novice::DrawSprite(x_, y_, playerHandle, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
    bullet.Draw();
}
//プレイヤーと敵の当たり判定
bool Player::CheckCollision(int enemyX, int enemyY, int enemyRadius) {
    int distance = int(sqrt(pow(enemyX - x_, 2) + pow(enemyY - y_, 2)));
    if (double(distance < enemyRadius + radius_)) {
        return true;
    }
    return false;
}
bool Player::CheckBulletEnemyCollision(int enemyX, int enemyY, int enemyRadius) {
    // プレイヤーの弾と敵との距離を計算
    int distance = int(sqrt(pow(enemyX - bullet.GetbulletposX(), 2) + pow(enemyY - bullet.GetbulletposY(), 2)));

    // 弾と敵の当たり判定
    if (distance < enemyRadius + bullet.Getbulletradius()) {
        return true;
    }
    return false;
}
void Player::Reset() {
    x_ = 600;
    y_ = 550;
    playerLife_ = 20;
    bullet.Reset(); 
    isGameover_ = false;
    
}