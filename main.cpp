#include <Novice.h>
#include "Player.h"
#include "enemy.h"
const char kWindowTitle[] = "LC1A_15_サノ_ハヤテ_タイトル";
enum SCENE {
	TITLE,
	GAME,
};
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	Player* player = new Player(600, 700, 20, 5,20);
	Enemy* enemy = new Enemy(100, 50, 30, 5,20,2,30);

	int scene = GAME;
	int titleHandle = Novice::LoadTexture("./resource/title.png");
	int backHandle = Novice::LoadTexture("./resource/back.png");
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();
		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		/// ↓更新処理ここから
		switch (scene) {
		case TITLE:
			break;
		case GAME:
			player->Update(keys, preKeys);
			enemy->Update(*player);
			if (preKeys[DIK_Q] == 0 && keys[DIK_Q] != 0) {
				scene = TITLE;
				player->Reset();
				enemy->Reset();
			}
			if (preKeys[DIK_R] == 0 && keys[DIK_R] != 0) {
				player->Reset();
				enemy->Reset();
			}
			break;
		}
		/// ↑更新処理ここまで
		/// ↓描画処理ここから
		switch (scene) {
		case TITLE:
			Novice::DrawSprite(0, 0, backHandle, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite(0, 0, titleHandle, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
			break;
		case GAME:
			Novice::ScreenPrintf(100, 100, "pcount = %d", enemy->GetEnemyLife());
			Novice::ScreenPrintf(100, 150, "bcount = %d", player->GetPlayerLife());
			player->Draw();
			enemy->Draw();
			break;
		}
		/// ↑描画処理ここまで
		// フレームの終了
		Novice::EndFrame();
		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}
	delete player;
	// ライブラリの終了
	Novice::Finalize();
	return 0;
}