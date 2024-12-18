#pragma once
#include "Structure.h"

/// <summary>
/// 座標変換を行う
/// </summary>
/// <param name="world">ワールド座標</param>
/// <returns>座標変換を行い、構造体を返却する</returns>
Coordinate2 CoordinateTransformation(Coordinate2 world);

/// <summary>
/// 矩形の当たり判定を行う
/// </summary>
/// <param name="world1">ワールド座標1</param>
/// <param name="radius1">図形の半径1</param>
/// <param name="world2">ワールド座標2</param>
/// <param name="radius2">図形の半径2</param>
/// <returns>矩形の当たり判定を行いtrueかfalseを返却する</returns>
int HitBox(Coordinate2 world1, Radius2 radius1, Coordinate2 world2, Radius2 radius2);

/// <summary>
/// 復活処理を行う
/// </summary>
/// <param name="respawn">復活</param>
void RespawnProcess(Respawn* respawn);

/// <summary>
/// ダメージ処理を行う
/// </summary>
/// <param name="hp">体力</param>
void DamageProcess(Hp* hp);

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
/// 描画する
/// </summary>
/// <param name="bullet">弾</param>
/// <param name="gh">画像</param>
/// <param name="srcX">左上のX軸</param>
/// <param name="srcY">左上のY軸</param>
/// <param name="color">色</param>
void Draw(Bullet bullet, Graph gh, int srcX, int srcY, int color);

/// <summary>
/// 描画する
/// </summary>
/// <param name="boss">ボス</param>
/// <param name="gh">画像</param>
/// <param name="srcX">左上のX軸</param>
/// <param name="srcY">左上のY軸</param>
/// <param name="color">色</param>
void Draw(Boss boss, Graph gh, int srcX, int srcY, int color);

/// <summary>
/// プレイヤーを操作する
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="keys">キー</param>
void PlayerMove(Player* player, const char* keys, const char* preKeys);

/// <summary>
/// プレイヤーが爆弾を使う
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="bomb">爆弾</param>
/// <param name="bullet">弾</param>
/// <param name="keys">キー</param>
/// <param name="preKeys">前のキー</param>
void PlayerUseBomb(Player* player, Bomb* bomb, Bullet* bullet, const char* keys, const char* preKeys);

/// <summary>
/// 弾を発射する
/// </summary>
/// <param name="bullet">弾</param>
/// <param name="type">種類</param>
/// <param name="posX">X軸の位置</param>
/// <param name="posY">Y軸の位置</param>
/// <param name="radiusX">X軸の図形の半径</param>
/// <param name="radiusY">Y軸の図形の半径</param>
void BulletShot(Bullet* bullet, int type, float posX, float posY, float radiusX, float radiusY);

/// <summary>
/// プレイヤーの爆弾を発射する
/// </summary>
/// <param name="bomb">爆弾</param>
/// <param name="velX">X軸の移動速度</param>
/// <param name="velY">Y軸の移動速度</param>
/// <param name="accelerationX">X軸の加速度</param>
/// <param name="accelerationY">Y軸の加速度</param>
void PlayerBombShot(Bomb* bomb, float velX, float velY, float accelerationX, float accelerationY);

/// <summary>
/// プレイヤーが爆弾を持つ
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="bomb">爆弾</param>
void PlayerHaveBomb(Player* player, Bomb* bomb);

/// <summary>
/// 敵を作る
/// </summary>
/// <param name="enemy">敵</param>
/// <param name="type">種類</param>
/// <param name="posX">X軸の位置</param>
/// <param name="posY">Y軸の位置</param>
/// <param name="radius">図形の半径</param>
void MakeEnemy(Enemy* enemy, int type, float posX, float posY, float radius);

/// <summary>
/// ボスを作る
/// </summary>
/// <param name="boss">ボス</param>
/// <param name="type">種類</param>
/// <param name="posX">X軸の位置</param>
/// <param name="posY">Y軸の位置</param>
/// <param name="radiusX">X軸の図形の半径</param>
/// <param name="radiusY">Y軸の図形の半径</param>
void MakeBoss(Boss* boss, int type, float posX, float posY, float radiusX, float radiusY);

/// <summary>
/// 爆弾を動かす
/// </summary>
/// <param name="bomb">爆弾</param>
/// <param name="bullet">弾</param>
void BombMove(Bomb* bomb, Bullet* bullet);

/// <summary>
/// 弾を動かす
/// </summary>
/// <param name="bullet">弾</param>
void BulletMove(Bullet* bullet);


void BossMove(Boss* boss, Bullet* bullet, Enemy* enemy, Player* player);