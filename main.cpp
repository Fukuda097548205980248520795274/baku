#include <Novice.h>
#include "Constant.h"
#include "Structure.h"
#include "Bakutyumu.h"

const char kWindowTitle[] = "1228_爆昼夢";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kScreenWidth, kScreenHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	/*-----------------------------
		変数を作り、初期値を入れる
	-----------------------------*/

	/*   プレイヤー   */

	// 構造体
	Player player;

	// 復活
	player.respawn.isRespawn = true;
	player.respawn.timer = 120;

	// 向ている方向
	player.directionNo = DIRECTION_RIGHT;

	// 位置
	player.pos.world = { 0.0f , 0.0f };
	player.pos.screen = CoordinateTransformation(player.pos.world);

	// 移動速度
	player.vel = { 0.0f , 0.0f };

	// 加速度
	player.acceleration = { 0.0f , 0.0f };

	// フラグ
	player.flug.isJump = false;
	player.flug.isTwoStepJump = false;
	player.flug.isBombHave = false;

	// 図形の半径
	player.radius = { 0.0f , 0.0f };

	PlayerGameInitialValue(&player);


	/*   爆弾   */

	// 構造体
	Bomb bomb[kBombNum];

	for (int i = 0; i < kBombNum; i++)
	{
		// 復活
		bomb[i].respawn.isRespawn = true;
		bomb[i].respawn.timer = 120;

		// 発射しているかどうか（発射フラグ）
		bomb[i].isShot = false;

		// プレイヤーが持っているか（所持フラグ）
		bomb[i].isPlayerHave = false;

		// 制限時間
		bomb[i].timeLimit = 0;

		// 位置
		bomb[i].pos.world = { 0.0f , 0.0f };
		bomb[i].pos.screen = CoordinateTransformation(bomb[i].pos.screen);

		// 移動速度
		bomb[i].vel = { 0.0f , 0.0f };

		// 加速度
		bomb[i].acceleration = { 0.0f , 0.0f };

		// 図形の半径
		bomb[i].radius = { 0.0f , 0.0f };
	}


	/*   弾   */

	// 構造体
	Bullet bullet[kBulletNum];

	for (int i = 0; i < kBulletNum; i++)
	{
		// 復活
		bullet[i].respawn.isRespawn = true;
		bullet[i].respawn.timer = 120;

		// 発射されているかどうか（発射フラグ）
		bullet[i].isShot = false;

		// 発射されている時間
		bullet[i].shotTimer = 0;

		// 位置
		bullet[i].pos.world = { 0.0f , 0.0f };
		bullet[i].pos.screen = CoordinateTransformation(bullet[i].pos.world);

		// 移動速度
		bullet[i].vel = { 0.0f , 0.0f };

		// 加速度
		bullet[i].acceleration = { 0.0f , 0.0f };

		// 図形の半径
		bullet[i].radius = { 0.0f , 0.0f };
	}


	/*   敵   */

	// 構造体
	Enemy enemy[kEnemyNum];

	for (int i = 0; i < kEnemyNum; i++)
	{
		// 復活
		enemy[i].respawn.isRespawn = true;
		enemy[i].respawn.timer = 120;

		// 出現しているかどうか（出現フラグ）
		enemy[i].isArrival = false;

		// 種類
		enemy[i].type = -1;

		// 位置
		enemy[i].pos.world = { 0.0f , 0.0f };
		enemy[i].pos.screen = CoordinateTransformation(enemy[i].pos.world);

		// 移動速度
		enemy[i].vel = { 0.0f , 0.0f };

		// 加速度
		enemy[i].acceleration = { 0.0f , 0.0f };

		// 図形の半径
		enemy[i].radius = { 0.0f , 0.0f };
	}


	/*   画像   */

	// 試験用図形
	Graph ghWhite = { Novice::LoadTexture("./NoviceResources/white1x1.png") , 1 , 1 };


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		/*--------------
			復活処理
		--------------*/

		// プレイヤー
		RespawnProcess(&player.respawn);

		// 爆弾
		for (int i = 0; i < kBombNum; i++)
		{
			RespawnProcess(&bomb[i].respawn);
		}

		// 敵
		for (int i = 0; i < kEnemyNum; i++)
		{
			RespawnProcess(&enemy[i].respawn);
		}

		/*------------------
			動きを設定する
		------------------*/

		// プレイヤーを操作する
		PlayerMove(&player, keys, preKeys);

		// プレイヤーが爆弾を投げる
		PlayerThrowBomb(&player, bomb, keys, preKeys);

		// 爆弾の動き
		BombMove(bomb);


		/*-------------
			座標変換
		-------------*/

		// プレイヤー
		player.pos.screen = CoordinateTransformation(player.pos.world);

		// 爆弾
		for (int i = 0; i < kBombNum; i++)
		{
			bomb[i].pos.screen = CoordinateTransformation(bomb[i].pos.world);
		}

		// 敵
		for (int i = 0; i < kEnemyNum; i++)
		{
			enemy[i].pos.screen = CoordinateTransformation(enemy[i].pos.world);
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		/*------------------------
			図形や画像を描画する
		------------------------*/

		/*   敵   */

		// 出現している（出現フラグがtrueである）とき
		for (int i = 0; i < kEnemyNum; i++)
		{
			if (enemy[i].isArrival)
			{
				Draw(enemy[i], ghWhite, 0, 0, 0xFFFFFFFF);
			}
		}

		/*   プレイヤー   */

		// 復活している（復活フラグがtrueである）とき
		if (player.respawn.isRespawn)
		{
			Draw(player, ghWhite, 0, 0, 0xFFFFFFFF);
		}

		/*   爆弾   */

		// 発射している（発射フラグがtrueである）とき
		for (int i = 0; i < kBombNum; i++)
		{
			if (bomb[i].isShot || bomb[i].isPlayerHave)
			{
				Draw(bomb[i], ghWhite, 0, 0, 0xFFFFFFFF);
			}
		}

		Novice::ScreenPrintf(0, 0, "");


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
