#include "Enemy.h"
#include <Novice.h>
Enemy::Enemy(int posX, int posY, int radius, int speed, int enemyLife,
	int enemyattack, int respawnTime) :enemybullet(posX, posY, 5, 10, 2)
{
	posX_ = posX;
	posY_ = posY;
	radius_ = radius;
	speed_ = speed;
	enemyLife_ = enemyLife;
	enemyattack_ = enemyattack;
	isAlive_ = true;
	respawnTime_ = respawnTime;
	respawnTimer_ = 0;
}
void Enemy::Update(Player& player) {
	if (!isAlive_) {
		respawnTimer_++;
		if (respawnTimer_ >= respawnTime_) {
			Respawn();
		}
		return;
	}
	posX_ += speed_;
	if (posX_ > 1250 || posX_ < 10)
	{
		speed_ = -speed_;
	}
	if (enemyLife_ < 1) {
		isAlive_ = false;
		respawnTimer_ = 0;
	}
	auto currentTime = std::chrono::steady_clock::now();
	auto invincibleDuration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastHitTime_).count();
	if (invincibleDuration < 1000) { // 1000ミリ秒（1秒）の無敵時間
		invincible_ = true;
	}
	else {
		invincible_ = false;
	}
	// プレイヤーとの当たり判定
	if (!player.IsInvincible() && player.CheckCollision(posX_, posY_, radius_)) {
		player.DecreaseLife();
		player.SetInvincible(true);
		player.ResetInvincibleTime();
	}
	// プレイヤーと敵の弾の当たり判定
	if (!player.IsInvincible() && checkEnemyBulletCollision(player.GetX(), player.GetY(), player.GetRadius())) {
		player.DecreaseLife();
		player.SetInvincible(true);
		player.ResetInvincibleTime();
	}
	// プレイヤーの弾と敵の当たり判定
	if (!IsInvincible() && player.CheckBulletEnemyCollision(posX_, posY_, radius_)) {
		DecreaseLife();
		SetInvincible(true);
		ResetInvincibleTime();
	}
	// 弾を発射する条件
	auto currentTime2 = std::chrono::steady_clock::now();
	auto timeDiff2 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - lastBulletTime_).count();
	if (timeDiff2 > 1000) {
		enemybullet.Shot(posX_, posY_, 10); 
		lastBulletTime_ = currentTime2; 
	}
	enemybullet.Update();
}

void Enemy::Draw() {
	Novice::DrawEllipse(posX_, posY_, radius_, radius_, 0.0f, RED, kFillModeSolid);
	Novice::DrawSprite(posX_, posY_, enemyHandle, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
	enemybullet.Draw();
}
void Enemy::DecreaseLife() {
	enemyLife_ -= 2;
}
//リスポーン
void Enemy::Respawn() {
	posX_ = 100;
	posY_ = 50;
	isAlive_ = true;
	enemyLife_ = 20;
	speed_ = 10;
}
void Enemy::Reset() {
	posX_ = 100;
	posY_ = 50;
	enemyLife_ = 20;
	enemybullet.Reset(); // 敵の弾の状態もリセットする
	isAlive_ = true;
}
bool Enemy::checkEnemyBulletCollision(int playerX, int playerY, int playerRadius) {
	int bulletX = enemybullet.GetenemybulletposX();
	int bulletY = enemybullet.GetenemybulletposY();
	int bulletRadius = enemybullet.Getenemybulletradius();
	int distanceSquared = (bulletX - playerX) * (bulletX - playerX) + (bulletY - playerY) * (bulletY - playerY);
	if (distanceSquared <= (bulletRadius + playerRadius) * (bulletRadius + playerRadius)) {
		return true;
	}

	return false;
}