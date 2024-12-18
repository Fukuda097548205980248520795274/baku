#pragma once

// 画面の横幅
const int kScreenWidth = 1280;

// 画面の縦幅
const int kScreenHeight = 720;

// 爆弾の数
const int kBombNum = 64;

// 弾の数
const int kBulletNum = 128;

// 敵の数
const int kEnemyNum = 64;

// 向き
enum DIRECTION
{
	// 左向き
	DIRECTION_LEFT,

	// 右向き
	DIRECTION_RIGHT
};

// 弾の種類
enum BULLET_TYPE
{
	// 爆発
	BULLET_TYPE_EXPLOSION,

	// 振動
	BULLET_TYPE_VIBRATION,
};

// 敵の種類
enum ENEMY_TYPE
{
	// 空中の敵
	ENEMY_TYPE_FLYING
};

// ボスの種類
enum BOSS_TYPE
{
	// ステージ1
	BOSS_TYPE_STAGE_1,
};

/*

enum PadButton {

	kPadButton0,	//!< XInputの場合、十字キー上
	kPadButton1,	//!< XInputの場合、十字キー下
	kPadButton2,	//!< XInputの場合、十字キー左
	kPadButton3,	//!< XInputの場合、十字キー右
	kPadButton4,	//!< XInputの場合、START
	kPadButton5,	//!< XInputの場合、BACK
	kPadButton6,	//!< XInputの場合、L3
	kPadButton7,	//!< XInputの場合、R3
	kPadButton8,	//!< XInputの場合、L1
	kPadButton9,	//!< XInputの場合、R1
	kPadButton10,	//!< XInputの場合、L2
	kPadButton11,	//!< XInputの場合、R2
	kPadButton12,
	kPadButton13,
	kPadButton14,
	kPadButton15,
	kPadButton16,
	kPadButton17,
	kPadButton18,
	kPadButton19,

};

*/