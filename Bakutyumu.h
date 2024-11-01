#pragma once
#include "Structure.h"

/// <summary>
/// 座標変換を行う
/// </summary>
/// <param name="world">ワールド座標</param>
/// <returns>座標変換を行い、構造体を返却する</returns>
Coordinate2 CoordinateTransformation(Coordinate2 world);

/// <summary>
/// 復活処理を行う
/// </summary>
/// <param name="respawn">復活</param>
void RespawnProcess(Respawn* respawn);

/// <summary>
/// プレイヤーのゲーム中の初期値を入力する
/// </summary>
/// <param name="player">プレイヤー</param>
void PlayerGameInitialValue(Player* player);

/// <summary>
/// 描画する
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="gh">画像</param>
/// <param name="srcX">左上のX軸</param>
/// <param name="srcY">左上のY軸</param>
/// <param name="color">色</param>
void Draw(Player player, Graph gh, int srcX, int srcY, int color);

/// <summary>
/// 描画する
/// </summary>
/// <param name="enemy">敵</param>
/// <param name="gh">画像</param>
/// <param name="srcX">左上のX軸</param>
/// <param name="srcY">左上のY軸</param>
/// <param name="color">色</param>
void Draw(Enemy enemy, Graph gh, int srcX, int srcY, int color);

/// <summary>
/// 描画する
/// </summary>
/// <param name="bomb">爆弾</param>
/// <param name="gh">画像</param>
/// <param name="srcX">左上のX軸</param>
/// <param name="srcY">左上のY軸</param>
/// <param name="color">色</param>
void Draw(Bomb bomb, Graph gh, int srcX, int srcY, int color);

/// <summary>
/// プレイヤーを操作する
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="keys">キー</param>
void PlayerMove(Player* player, const char* keys, const char* preKeys);

/// <summary>
/// プレイヤーが爆弾を投げる
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="bomb">爆弾</param>
/// <param name="keys">キー</param>
/// <param name="preKeys">前のキー</param>
void PlayerThrowBomb(Player* player, Bomb* bomb, const char* keys, const char* preKeys);

/// <summary>
/// プレイヤーの爆弾を発射する
/// </summary>
/// <param name="bomb">爆弾</param>
/// <param name="posX">X軸の位置</param>
/// <param name="posY">Y軸の位置</param>
/// <param name="velX">X軸の移動速度</param>
/// <param name="velY">Y軸の移動速度</param>
/// <param name="accelerationX">X軸の加速度</param>
/// <param name="accelerationY">Y軸の加速度</param>
/// <param name="radius">図形の半径</param>
void PlayerBombShot(Bomb* bomb, float posX, float posY, float velX, float velY, float accelerationX, float accelerationY, float radius);

/// <summary>
/// プレイヤーが爆弾を持つ
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="bomb">爆弾</param>
void PlayerHaveBomb(Player* player, Bomb* bomb);

/// <summary>
/// 爆弾を動かす
/// </summary>
/// <param name="bomb">爆弾</param>
void BombMove(Bomb* bomb);