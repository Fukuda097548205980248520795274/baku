#pragma once

// 座標
typedef struct Coordinate2
{
	float x;
	float y;
}Coordinate2;

// 位置
typedef struct Pos2
{
	// ワールド座標
	struct Coordinate2 world;

	// スクリーン座標
	struct Coordinate2 screen;
}Pos2;

// マップ
typedef struct Map2
{
	int x;
	int y;
}Map2;

// 移動速度
typedef struct Vel2
{
	float x;
	float y;
}Vel2;

// 加速度
typedef struct Acceleration2
{
	float x;
	float y;
}Acceleration2;

// 図形の半径
typedef struct Radius2
{
	float x;
	float y;
}Radius2;

// 復活
typedef struct Respawn
{
	// 復活しているかどうか（復活フラグ）
	int isRespawn;

	// 復活処理
	int timer;
}Respawn;

// プレイヤーのフラグ
typedef struct PlayerFlug
{
	// ジャンプしているかどうか（ジャンプフラグ）
	int isJump;

	// 二段ジャンプしているかどうか（二段ジャンプフラグ）
	int isTwoStepJump;

	// 爆弾を持っているかどうか（所持フラグ）
	int isBombHave;
}PlayerFlug;

// 画像
typedef struct Graph
{
	// 画像
	int texture;

	// 横幅
	int width;

	// 縦幅
	int height;
}Graph;

// プレイヤー
typedef struct Player
{
	// 復活
	Respawn respawn;

	// 向いている方向
	int directionNo;

	// 位置
	Pos2 pos;

	// 移動速度
	Vel2 vel;

	// 加速度
	Acceleration2 acceleration;

	// フラグ
	PlayerFlug flug;

	// 図形の半径
	Radius2 radius;
}Player;

// 爆弾
typedef struct Bomb
{
	// 復活
	Respawn respawn;

	// 発射しているかどうか（発射フラグ）
	int isShot;

	// プレイヤーが持っている（所持フラグ）
	int isPlayerHave;

	// 制限時間
	int timeLimit;

	// 位置
	Pos2 pos;

	// 移動速度
	Vel2 vel;

	// 加速度
	Acceleration2 acceleration;

	// 図形の半径
	Radius2 radius;
}Bomb;

// 敵
typedef struct Enemy
{
	// 復活
	Respawn respawn;

	// 出現しているかどうか（出現フラグ）
	int isArrival;

	// 種類
	int type = -1;

	// 位置
	Pos2 pos;

	// 移動速度
	Vel2 vel;

	// 加速度
	Acceleration2 acceleration;

	// 図形の半径
	Radius2 radius;
}Enemy;