#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Constant.h"
#include "Structure.h"

/// <summary>
/// 座標変換を行う
/// </summary>
/// <param name="world">ワールド座標</param>
/// <returns>座標変換を行い、構造体を返却する</returns>
Coordinate2 CoordinateTransformation(Coordinate2 world)
{
	// スクリーン座標
	Coordinate2 screen;

	screen = { world.x , -world.y + 600.0f };

	return screen;
}

/// <summary>
/// 矩形の当たり判定を行う
/// </summary>
/// <param name="world1">ワールド座標1</param>
/// <param name="radius1">図形の半径1</param>
/// <param name="world2">ワールド座標2</param>
/// <param name="radius2">図形の半径2</param>
/// <returns>矩形の当たり判定を行いtrueかfalseを返却する</returns>
int HitBox(Coordinate2 world1, Radius2 radius1, Coordinate2 world2, Radius2 radius2)
{
	if (world1.x + radius1.x > world2.x - radius2.x &&
		world1.x - radius1.x < world2.x + radius2.x)
	{
		if (world1.y - radius1.y < world2.y + radius2.y &&
			world1.y + radius1.y > world2.y - radius2.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

/// <summary>
/// 復活処理を行う
/// </summary>
/// <param name="respawn">復活</param>
void RespawnProcess(Respawn* respawn)
{
	// null を探す
	if (respawn == nullptr)
	{
		return;
	}

	// 復活していない（復活フラグがfalseである）ときに、復活処理を行う
	if (respawn->isRespawn == false)
	{
		respawn->timer--;

		if (respawn->timer <= 0)
		{
			// 復活する（復活フラグがtrueになる）
			respawn->isRespawn = true;

			// 復活処理を初期化する
			respawn->timer = 120;
		}
	}
}

/// <summary>
/// ダメージ処理を行う
/// </summary>
/// <param name="hp">体力</param>
void DamageProcess(Hp* hp)
{
	// null を探す
	if (hp == nullptr)
	{
		return;
	}

	// ダメージが入った（ダメージフラグがtrueである）ときに、処理を行う
	if (hp->isDamage)
	{
		hp->damageTimer--;

		if (hp->damageTimer <= 0)
		{
			// ダメージが消える（ダメージフラグがfalseになる）
			hp->isDamage = false;

			// ダメージ時間を初期化する
			hp->damageTimer = 5;
		}
	}
}

/// <summary>
/// プレイヤーのゲーム中の初期値を入力する
/// </summary>
/// <param name="player">プレイヤー</param>
void PlayerGameInitialValue(Player* player)
{
	// null を探す
	if (player == nullptr)
	{
		return;
	}

	// 復活
	player->respawn.isRespawn = true;
	player->respawn.timer = 120;

	// 体力
	player->hp.quantity = 300;
	player->hp.damageTimer = 5;
	player->hp.isDamage = false;

	// 向ている方向
	player->directionNo = DIRECTION_RIGHT;

	// 位置
	player->pos.world = { 300.0f , 0.0f };
	player->pos.screen = CoordinateTransformation(player->pos.world);

	// 移動速度
	player->vel = { 0.0f , 0.0f };

	// 加速度
	player->acceleration = { 0.0f , 0.0f };

	// フラグ
	player->flug.isJump = false;
	player->flug.isTwoStepJump = false;
	player->flug.isBombHave = false;

	// 図形の半径
	player->radius = { 16.0f , 16.0f };
}

/// <summary>
/// 画像を描画する
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="gh">画像</param>
/// <param name="srcX">左上のX軸</param>
/// <param name="srcY">左上のY軸</param>
/// <param name="color">色</param>
void Draw(Player player, Graph gh, int srcX, int srcY, int color)
{
	Novice::DrawQuad
	(
		static_cast<int>(player.pos.screen.x - player.radius.x), static_cast<int>(player.pos.screen.y - player.radius.y),
		static_cast<int>(player.pos.screen.x + player.radius.x), static_cast<int>(player.pos.screen.y - player.radius.y),
		static_cast<int>(player.pos.screen.x - player.radius.x), static_cast<int>(player.pos.screen.y + player.radius.y),
		static_cast<int>(player.pos.screen.x + player.radius.x), static_cast<int>(player.pos.screen.y + player.radius.y),
		srcX, srcY, gh.width, gh.height, gh.texture, color
	);
}

/// <summary>
/// 描画する
/// </summary>
/// <param name="enemy">敵</param>
/// <param name="gh">画像</param>
/// <param name="srcX">左上のX軸</param>
/// <param name="srcY">左上のY軸</param>
/// <param name="color">色</param>
void Draw(Enemy enemy, Graph gh, int srcX, int srcY, int color)
{
	Novice::DrawQuad
	(
		static_cast<int>(enemy.pos.screen.x - enemy.radius.x), static_cast<int>(enemy.pos.screen.y - enemy.radius.y),
		static_cast<int>(enemy.pos.screen.x + enemy.radius.x), static_cast<int>(enemy.pos.screen.y - enemy.radius.y),
		static_cast<int>(enemy.pos.screen.x - enemy.radius.x), static_cast<int>(enemy.pos.screen.y + enemy.radius.y),
		static_cast<int>(enemy.pos.screen.x + enemy.radius.x), static_cast<int>(enemy.pos.screen.y + enemy.radius.y),
		srcX, srcY, gh.width, gh.height, gh.texture, color
	);
}

/// <summary>
/// 描画する
/// </summary>
/// <param name="bomb">爆弾</param>
/// <param name="gh">画像</param>
/// <param name="srcX">左上のX軸</param>
/// <param name="srcY">左上のY軸</param>
/// <param name="color">色</param>
void Draw(Bomb bomb, Graph gh, int srcX, int srcY, int color)
{
	Novice::DrawQuad
	(
		static_cast<int>(bomb.pos.screen.x - bomb.radius.x), static_cast<int>(bomb.pos.screen.y - bomb.radius.y),
		static_cast<int>(bomb.pos.screen.x + bomb.radius.x), static_cast<int>(bomb.pos.screen.y - bomb.radius.y),
		static_cast<int>(bomb.pos.screen.x - bomb.radius.x), static_cast<int>(bomb.pos.screen.y + bomb.radius.y),
		static_cast<int>(bomb.pos.screen.x + bomb.radius.x), static_cast<int>(bomb.pos.screen.y + bomb.radius.y),
		srcX, srcY, gh.width, gh.height, gh.texture, color
	);
}

/// <summary>
/// 描画する
/// </summary>
/// <param name="bullet">弾</param>
/// <param name="gh">画像</param>
/// <param name="srcX">左上のX軸</param>
/// <param name="srcY">左上のY軸</param>
/// <param name="color">色</param>
void Draw(Bullet bullet, Graph gh, int srcX, int srcY, int color)
{
	Novice::DrawQuad
	(
		static_cast<int>(bullet.pos.screen.x - bullet.radius.x), static_cast<int>(bullet.pos.screen.y - bullet.radius.y),
		static_cast<int>(bullet.pos.screen.x + bullet.radius.x), static_cast<int>(bullet.pos.screen.y - bullet.radius.y),
		static_cast<int>(bullet.pos.screen.x - bullet.radius.x), static_cast<int>(bullet.pos.screen.y + bullet.radius.y),
		static_cast<int>(bullet.pos.screen.x + bullet.radius.x), static_cast<int>(bullet.pos.screen.y + bullet.radius.y),
		srcX, srcY, gh.width, gh.height, gh.texture, color
	);
}

/// <summary>
/// 描画する
/// </summary>
/// <param name="boss">ボス</param>
/// <param name="gh">画像</param>
/// <param name="srcX">左上のX軸</param>
/// <param name="srcY">左上のY軸</param>
/// <param name="color">色</param>
void Draw(Boss boss, Graph gh, int srcX, int srcY, int color)
{
	Novice::DrawQuad
	(
		static_cast<int>(boss.pos.screen.x - boss.radius.x), static_cast<int>(boss.pos.screen.y - boss.radius.y),
		static_cast<int>(boss.pos.screen.x + boss.radius.x), static_cast<int>(boss.pos.screen.y - boss.radius.y),
		static_cast<int>(boss.pos.screen.x - boss.radius.x), static_cast<int>(boss.pos.screen.y + boss.radius.y),
		static_cast<int>(boss.pos.screen.x + boss.radius.x), static_cast<int>(boss.pos.screen.y + boss.radius.y),
		srcX, srcY, gh.width, gh.height, gh.texture, color
	);
}

/// <summary>
/// プレイヤーを操作する
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="keys">キー</param>
void PlayerMove(Player* player, const char* keys, const char* preKeys)
{
	// null を探す
	if (player == nullptr)
	{
		return;
	}


	// プレイヤーが復活していない（復活フラグがfalseである）ときは、操作ができない

	/*   横移動操作   */

	// 横移動を初期化する
	player->vel.x = 0.0f;

	// Aキーで、左に移動する
	if (keys[DIK_A])
	{
		if (player->respawn.isRespawn)
		{
			// 左を向く
			player->directionNo = DIRECTION_LEFT;

			if (player->pos.world.x - player->radius.x > 0.0f)
			{
				player->vel.x = -6.0f;
			}
		}
	}

	// Dキーで、右に移動する
	if (keys[DIK_D])
	{
		if (player->respawn.isRespawn)
		{
			// 左を向く
			player->directionNo = DIRECTION_RIGHT;

			if (player->pos.world.x + player->radius.x < static_cast<float>(kScreenWidth))
			{
				player->vel.x = 6.0f;
			}
		}
	}

	// プレイヤーを横に動かす
	player->pos.world.x += player->vel.x;


	/*   ジャンプ操作   */

	// Jキーで、ジャンプする（ジャンプフラグがtrueになる）
	if (!preKeys[DIK_J] && keys[DIK_J])
	{
		if (player->respawn.isRespawn)
		{
			// ジャンプしていない（ジャンプフラグがfalseである）ときは、一段ジャンプ
			if (player->flug.isJump == false)
			{
				player->flug.isJump = true;

				// 加速度が上がる
				player->acceleration.y = 1.0f;
			} 
			else
			{
				// ジャンプしている（ジャンプフラグがtrueである）ときは、二段ジャンプ
				if (player->flug.isTwoStepJump == false)
				{
					player->flug.isTwoStepJump = true;

					// 加速度が上がる
					player->acceleration.y = 1.0f;
				}
			}
		}
	}

	// ジャンプしている（ジャンプフラグがtrueである）と、上に飛ぶ
	if (player->flug.isJump)
	{
		player->vel.y = 8.0f;

		// 落下する
		if (player->acceleration.y > -1.0f)
		{
			player->acceleration.y += -0.05f;
		}
	} 
	else
	{
		// ジャンプしていない（ジャンプフラグがfalseである）と、縦の動きが止まる
		player->vel.y = 0.0f;
		player->acceleration.y = 0.0f;
	}

	// プレイヤーを縦に動かす
	player->pos.world.y += player->vel.y * player->acceleration.y;

	// 着地したらジャンプしなくなる（ジャンプ・二段ジャンプフラグがfalseになる）
	if (player->pos.world.y - player->radius.y <= 0.0f)
	{
		player->flug.isJump = false;
		player->flug.isTwoStepJump = false;
	}


	/*   体力   */

	// 大量がなくなったら消える（復活フラグがfalseになる）
	if (player->hp.quantity <= 0)
	{
		player->respawn.isRespawn = false;

		// 他のフラグもfalseになる
		player->flug.isJump = false;
		player->flug.isTwoStepJump = false;
	}


	/*   プレイヤーの位置   */

	// 移動範囲がに出たら元の位置に戻す
	if (player->pos.world.y - player->radius.y < 0.0f)
	{
		player->pos.world.y = player->radius.y;
	}

	if (player->pos.world.x - player->radius.x < 0.0f)
	{
		player->pos.world.x = player->radius.x;
	}

	if (player->pos.world.x + player->radius.x > static_cast<float>(kScreenWidth))
	{
		player->pos.world.x = static_cast<float>(kScreenWidth) - player->radius.x;
	}
}

/// <summary>
/// プレイヤーが爆弾を持つ
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="bomb">爆弾</param>
void PlayerHaveBomb(Player* player, Bomb* bomb)
{
	// null を探す
	if (player == nullptr || bomb == nullptr)
	{
		return;
	}

	// 爆弾を持つ
	for (int i = 0; i < kBombNum; i++)
	{
		if (bomb[i].isPlayerHave == false && bomb[i].isShot == false && bomb[i].respawn.isRespawn)
		{
			// 爆弾を持つ（所持フラグがtrueになる）
			bomb[i].isPlayerHave = true;

			// 爆弾を発射しない（発射フラグがfalaeになる）
			bomb[i].isShot = false;

			// 制限時間を設定する
			bomb[i].timeLimit = 180;

			// 位置
			bomb[i].pos.world = { player->pos.world.x , player->pos.world.y + 30.0f };

			// 移動速度
			bomb[i].vel = { 0.0f , 0.0f };

			// 加速度
			bomb[i].acceleration = { 0.0f , 0.0f };

			// 図形の半径
			bomb[i].radius = { 16.0f , 16.0f };

			break;
		}
	}
}

/// <summary>
/// プレイヤーの爆弾を発射する
/// </summary>
/// <param name="bomb">爆弾</param>
/// <param name="velX">X軸の移動速度</param>
/// <param name="velY">Y軸の移動速度</param>
/// <param name="accelerationX">X軸の加速度</param>
/// <param name="accelerationY">Y軸の加速度</param>
void PlayerBombShot(Bomb* bomb,float velX, float velY, float accelerationX, float accelerationY)
{
	// null を探す
	if (bomb == nullptr)
	{
		return;
	}

	// 持っている（所持フラグがtrueである）ボムを投げる
	for (int i = 0; i < kBombNum; i++)
	{
		if (bomb[i].isPlayerHave && bomb[i].isShot == false)
		{
			// 爆弾を離す（所持フラグがfalseになる）
			bomb[i].isPlayerHave = false;

			// 爆弾が発射される（発射フラグがfalseになる）
			bomb[i].isShot = true;

			// 移動速度
			bomb[i].vel = { velX , velY };

			// 加速度
			bomb[i].acceleration = { accelerationX , accelerationY };

			break;
		}
	}
}

/// <summary>
/// 弾を発射する
/// </summary>
/// <param name="bullet">弾</param>
/// <param name="type">種類</param>
/// <param name="posX">X軸の位置</param>
/// <param name="posY">Y軸の位置</param>
/// <param name="radiusX">X軸の図形の半径</param>
/// <param name="radiusY">Y軸の図形の半径</param>
void BulletShot(Bullet* bullet, int type, float posX, float posY, float radiusX, float radiusY)
{
	// null を探す
	if (bullet == nullptr)
	{
		return;
	}

	// 弾を発射する
	for (int i = 0; i < kBulletNum; i++)
	{
		if (bullet[i].isShot == false && bullet[i].respawn.isRespawn)
		{
			// 弾を発射する（発射フラグがtrueになる）
			bullet[i].isShot = true;

			// 発射されている時間
			bullet[i].shotTimer = 0;

			// 種類
			bullet[i].type = type;

			// 位置
			bullet[i].pos.world = { posX , posY };

			// ベクトル
			bullet[i].vec = { 0.0f , 0.0f };

			// 移動速度
			bullet[i].vel = { 0.0f , 0.0f };

			// 加速度
			bullet[i].acceleration = { 0.0f , 0.0f };

			// 図形の半径
			bullet[i].radius = { radiusX , radiusY };

			break;
		}
	}
}

/// <summary>
/// プレイヤーが爆弾を使う
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="bomb">爆弾</param>
/// <param name="bullet">弾</param>
/// <param name="keys">キー</param>
/// <param name="preKeys">前のキー</param>
void PlayerUseBomb(Player* player, Bomb* bomb,Bullet* bullet, const char* keys, const char* preKeys)
{
	// null を探す
	if (player == nullptr || bomb == nullptr || bullet == nullptr)
	{
		return;
	}


	// プレイヤーが復活していない（復活フラグがfalseである）ときは、操作ができない

	// スペースキーで爆弾を使う
	if (!preKeys[DIK_SPACE] && keys[DIK_SPACE])
	{
		if (player->respawn.isRespawn)
		{
			// 爆弾を持っていない（所持フラグがfalseである）ときに、所持する
			if (player->flug.isBombHave == false)
			{
				// 爆弾を持つ（所持フラグがtrueになる）
				player->flug.isBombHave = true;

				// 爆弾を持つ
				PlayerHaveBomb(player, bomb);
			}
			else
			{
				// 爆弾を持っている（所持フラグがtrueである）とき、爆弾を投げる

				// 爆弾を離す（所持フラグがfalseになる）
				player->flug.isBombHave = false;

				// プレイヤーの向きに合わせて、投げる方向を変える
				if (player->directionNo == DIRECTION_RIGHT)
				{
					// 右に進んでいるとき
					if (player->vel.x > 0.0f)
					{
						// 爆弾を投げる
						PlayerBombShot(bomb, 8.0f, 6.0f, 1.0f, 0.0f);
					}
					else
					{
						// 止まっているとき

						// 爆弾を投げる
						PlayerBombShot(bomb, 6.0f, 6.0f, 1.0f, 0.0f);
					}
				}
				else if (player->directionNo == DIRECTION_LEFT)
				{
					// 左に進んでいるとき
					if (player->vel.x < 0.0f)
					{
						// 爆弾を投げる
						PlayerBombShot(bomb, -8.0f, 6.0f, 1.0f, 0.0f);
					}
					else
					{
						// 止まっているとき

						// 爆弾を投げる
						PlayerBombShot(bomb, -6.0f, 6.0f, 1.0f, 0.0f);
					}
				}
			}
		}
	}

	// 所持している（所持フラグがtrueである）ときの爆弾を動かす
	if (player->flug.isBombHave)
	{
		for (int i = 0; i < kBombNum; i++)
		{
			if (bomb[i].isPlayerHave)
			{
				// 爆弾の位置
				bomb[i].pos.world = { player->pos.world.x  , player->pos.world.y + 30.0f };


				/* 爆弾の制限時間 */

				bomb[i].timeLimit--;

				// 制限時間が終了したら爆発する
				if (bomb[i].timeLimit <= 0)
				{
					// 弾を発射する
					BulletShot(bullet, BULLET_TYPE_EXPLOSION, bomb[i].pos.world.x, bomb[i].pos.world.y, 70.0f , 70.0f);

					// 爆弾が消える（発射、所持フラグがfalseになる）
					bomb[i].isShot = false;
					bomb[i].isPlayerHave = false;

					// プレイヤーが爆弾を離す（所持フラグがfalseになる）
					player->flug.isBombHave = false;
				}
			}
		}
	}
}

/// <summary>
/// 敵を作る
/// </summary>
/// <param name="enemy">敵</param>
/// <param name="type">種類</param>
/// <param name="posX">X軸の位置</param>
/// <param name="posY">Y軸の位置</param>
/// <param name="radius">図形の半径</param>
void MakeEnemy(Enemy* enemy, int type, float posX, float posY, float radius)
{
	// null を探す
	if (enemy == nullptr)
	{
		return;
	}

	for (int i = 0; i < kEnemyNum; i++)
	{
		if (enemy[i].isArrival == false && enemy[i].respawn.isRespawn)
		{
			// 敵を出現させる（出現フラグをtrueにする）
			enemy[i].isArrival = true;

			// 種類
			enemy[i].type = type;

			// 体力
			switch (enemy[i].type)
			{
			case ENEMY_TYPE_FLYING:

				enemy[i].hp.quantity = 1;
				enemy[i].hp.damageTimer = 5;
				enemy[i].hp.isDamage = false;

				break;
			}

			// フレーム
			enemy[i].frame = 0;

			// フラグ
			enemy[i].flug.isJump = false;

			// 位置
			enemy[i].pos.world = { posX , posY };

			// ベクトル
			enemy[i].vec = { 0.0f , 0.0f };

			// 移動速度
			enemy[i].vel = { 0.0f , 0.0f };

			// 加速度
			enemy[i].acceleration = { 0.0f , 0.0f };

			// 図形の半径
			enemy[i].radius = { radius , radius };

			break;
		}
	}
}

/// <summary>
/// ボスを作る
/// </summary>
/// <param name="boss">ボス</param>
/// <param name="type">種類</param>
/// <param name="posX">X軸の位置</param>
/// <param name="posY">Y軸の位置</param>
/// <param name="radiusX">X軸の図形の半径</param>
/// <param name="radiusY">Y軸の図形の半径</param>
void MakeBoss(Boss* boss, int type, float posX, float posY, float radiusX, float radiusY)
{
	// null を探す
	if (boss == nullptr)
	{
		return;
	}

	if (boss->isArrival == false && boss->respawn.isRespawn)
	{
		// 出現させる（出現フラグをtrueにする）
		boss->isArrival = true;

		// 攻撃していない（攻撃フラグをfalseにする）
		boss->isAttack = false;

		// 種類
		boss->type = type;

		// 体力
		switch (type)
		{
		case BOSS_TYPE_STAGE_1:

			boss->hp.quantity = 300;
			boss->hp.damageTimer = 5;
			boss->hp.isDamage = false;

			break;
		}

		// 攻撃のバリュエーション
		boss->attackNo = -1;

		// 向いている方向
		boss->directionNo = DIRECTION_LEFT;

		// フレーム
		boss->frame = 0;

		// フラグ
		boss->flug.isJump = false;

		// 位置
		boss->pos.world = { posX , posY };

		// ベクトル
		boss->vec = { 0.0f , 0.0f };

		// 移動速度
		boss->vel = { 0.0f , 0.0f };

		// 加速度
		boss->acceleration = { 0.0f , 0.0f };

		// 図形の半径
		boss->radius = { radiusX , radiusY };
	}
}

/// <summary>
/// 爆弾を動かす
/// </summary>
/// <param name="bomb">爆弾</param>
/// <param name="bullet">弾</param>
void BombMove(Bomb* bomb , Bullet* bullet)
{
	// null を探す
	if (bomb == nullptr || bullet == nullptr)
	{
		return;
	}

	for (int i = 0; i < kBombNum; i++)
	{
		// 発射されている（発射フラグがtrueである）弾を動かす
		if (bomb[i].isShot)
		{
			/* 制限時間 */

			bomb[i].timeLimit--;

			// 制限時間が終了したら爆発する
			if (bomb[i].timeLimit <= 0)
			{
				// 弾を発射する
				BulletShot(bullet, BULLET_TYPE_EXPLOSION, bomb[i].pos.world.x, bomb[i].pos.world.y, 70.0f , 70.0f);

				// 爆弾が消える（発射、所持フラグがfalseになる）
				bomb[i].isShot = false;
				bomb[i].isPlayerHave = false;
			}


			/* 移動 */

			// 落下させる
			if (bomb[i].acceleration.y > -3.0f)
			{
				bomb[i].acceleration.y += -0.1f;
			}
			else
			{
				// 加速度が想定外の値にならないようにする
				bomb[i].acceleration.y = -3.0f;
			}

			// 飛ぶ速度を低下させる
			if (bomb[i].acceleration.x > 0.0f)
			{
				bomb[i].acceleration.x += -0.02f;
			} 
			else
			{
				// 加速度が想定外の値にならないようにする
				bomb[i].acceleration.x = 0.0f;
			}

			// 反発させる
			if (bomb[i].pos.world.y - bomb[i].radius.y <= 0.0f)
			{
				// 反発係数
				bomb[i].acceleration.y *= -0.3f;

				// 埋まらないようにする
				bomb[i].pos.world.y = bomb[i].radius.y;

				// 加速度が低下したら、反発しなくなる
				if (bomb[i].acceleration.y < 0.1f && bomb[i].acceleration.y > -0.1f)
				{
					bomb[i].acceleration.y = 0.0f;
				}
			}

			// 弾を動かす
			bomb[i].pos.world.x += bomb[i].vel.x * bomb[i].acceleration.x;
			bomb[i].pos.world.y += bomb[i].vel.y * bomb[i].acceleration.y;


			// 画面外に出ないようにする
			if (bomb[i].pos.world.x - bomb[i].radius.x < 0.0f)
			{
				bomb[i].pos.world.x = bomb[i].radius.x;
			}

			if (bomb[i].pos.world.x + bomb[i].radius.x > static_cast<float>(kScreenWidth))
			{
				bomb[i].pos.world.x = static_cast<float>(kScreenWidth) - bomb[i].radius.x;
			}
		}
	}
}

/// <summary>
/// 弾を動かす
/// </summary>
/// <param name="bullet">弾</param>
void BulletMove(Bullet* bullet)
{
	// null を探す
	if (bullet == nullptr)
	{
		return;
	}

	// 発射された弾を動かす
	for (int i = 0; i < kBulletNum; i++)
	{
		if (bullet[i].isShot)
		{
			// 弾の種類で動きを変える
			switch (bullet[i].type)
			{
			case BULLET_TYPE_EXPLOSION:

				// 爆発

				bullet[i].shotTimer++;

				if (bullet[i].shotTimer > 1)
				{
					bullet[i].isShot = false;
					bullet[i].respawn.isRespawn = false;
				}

				break;

			case BULLET_TYPE_VIBRATION:

				// 振動

				bullet[i].shotTimer++;

				if (bullet[i].shotTimer > 1)
				{
					bullet[i].isShot = false;
					bullet[i].respawn.isRespawn = false;
				}

				break;
			}
		}
	}
}

/// <summary>
/// 敵を動かす
/// </summary>
/// <param name="enemy">敵</param>
/// <param name="bullet">弾</param>
/// <param name="player">プレイヤー</param>
/// <param name="boss">ボス</param>
void EnemyMove(Enemy* enemy, Bullet* bullet, Player* player, Boss* boss)
{
	// null を探す
	if (enemy == nullptr || bullet == nullptr || player == nullptr || boss == nullptr)
	{
		return;
	}

	// 出現している（出現フラグがfalseである）敵を動かす
	for (int i = 0; i < kEnemyNum; i++)
	{
		if (enemy[i].isArrival)
		{
			
		}
	}
}

/// <summary>
/// ボスを動かす
/// </summary>
/// <param name="boss">ボス</param>
/// <param name="bullet">弾</param>
/// <param name="enemy">敵</param>
void BossMove(Boss* boss, Bullet* bullet, Enemy* enemy , Player* player)
{
	// null を探す
	if (boss == nullptr || bullet == nullptr || enemy == nullptr || player == nullptr)
	{
		return;
	}

	// 乱数を作る
	unsigned int currentTimer = static_cast<unsigned int>(time(nullptr));
	srand(currentTimer);

	// 出現している（出現フラグがtrueである）ときに動かす
	if (boss->isArrival)
	{
		/*   攻撃   */

		// ボスのフレームを動かす
		boss->frame++;

		// 種類で動きを変える
		switch (boss->type)
		{
		case BOSS_TYPE_STAGE_1:

			// 60フレームから攻撃する
			if (boss->frame >= 60)
			{
				// 攻撃していない（攻撃フラグがfalseである）ときは、ランダムで攻撃を選ぶ
				if (boss->isAttack == false)
				{
					// ランダムで攻撃を選ぶ
					boss->attackNo = 4;

					// 攻撃する（攻撃フラグがtrueになる）
					boss->isAttack = true;
				} 
				else
				{
					// 攻撃する
					switch (boss->attackNo)
					{
					case 0:

						/* 突進攻撃 */

						// 100フレームで、プレイヤーのいる方向に突進する
						if (boss->frame >= 120)
						{
							if (boss->directionNo == DIRECTION_LEFT)
							{
								boss->pos.world.x += -8.0f;
							}
							else if (boss->directionNo == DIRECTION_RIGHT)
							{
								boss->pos.world.x += 8.0f;
							}

							// 画面の端についたら攻撃が停止する
							if (boss->pos.world.x - boss->radius.x <= 0.0f || boss->pos.world.x + boss->radius.x >= static_cast<float>(kScreenWidth))
							{
								// 攻撃しなくなる（攻撃フラグがfalseになる）
								boss->isAttack = false;
								boss->attackNo = -1;

								// ボスのフレームを攻撃前に戻す
								boss->frame = -100;
							}
						}

						break;

					case 1:

						/* 浮遊する敵を召喚 */

						// 80フレームで、敵を召喚する
						if (boss->frame == 80)
						{
							for (int i = 0; i < 3; i++)
							{
								MakeEnemy(enemy, ENEMY_TYPE_FLYING, 340.0f + i * 300.0f, 500.0f, 8.0f);
							}
						}

						// 100フレームで、攻撃を停止する
						if (boss->frame >= 100)
						{
							// 攻撃しなくなる（攻撃フラグがfalseになる）
							boss->isAttack = false;
							boss->attackNo = -1;

							// ボスのフレームを攻撃前に戻す
							boss->frame = -100;
						}


						break;

					case 2:

						/* 地上の敵を召喚 */

						break;

					case 3:

						/* 振動攻撃 */

						// 80フレームでジャンプする（ジャンプフラグがtrueになる）
						if (boss->frame == 80)
						{
							boss->flug.isJump = true;

							// 上に飛ぶ
							boss->vel.y = 32.0f;
							boss->acceleration.y = 1.0f;
						}

						// 81フレームで、加速度が0以下になるまでフレームを進めない
						if (boss->frame == 81)
						{
							if (boss->acceleration.y <= 0.0f)
							{
								boss->vel.y = 0.0f;
								boss->acceleration.y = 0.0f;
							}
							else
							{
								// フレームを進めない
								boss->frame--;
							}
						}

						// 120フレームで、一気に落下させる
						if (boss->frame == 120)
						{
							boss->vel.y = 20.0f;
							boss->acceleration.y = -1.0f;
						}

						// 121フレームで、着地する（ジャンプフラグがfalseになる）まで、フレームを進めない
						if (boss->frame == 121)
						{
							if (boss->flug.isJump == false)
							{
								// 着地したら、地面が爆発する
								BulletShot(bullet, BULLET_TYPE_VIBRATION, 640.0f, 0.0f, 640.0f, 5.0f);
							}
							else
							{
								// フレームを進めない
								boss->frame--;
							}
						}

						// 140フレームで、攻撃を修了する
						if (boss->frame >= 140)
						{
							// 攻撃しなくなる（攻撃フラグがfalseになる）
							boss->isAttack = false;
							boss->attackNo = -1;

							// ボスのフレームを攻撃前に戻す
							boss->frame = -100;
						}

						break;

					case 4:

						/*   瓦礫を落とす   */

						// 120フレームで、思いっきりジャンプする（ジャンプフラグがtrueになる）
						if (boss->frame == 120)
						{
							boss->flug.isJump = true;

							// 上に飛ぶ
							boss->vel.y = 32.0f;
							boss->acceleration.y = 1.0f;
						}

						// 121フレームで、天井に着くまで、フレームを進めない
						if (boss->frame == 121)
						{
							if (boss->pos.world.y + boss->radius.y > static_cast<float>(kScreenHeight) - 100.0f)
							{
								// 画面から出ないようにする
								boss->pos.world.y = static_cast<float>(kScreenHeight) - 100.0f - boss->radius.y;

								// 上についたら、移動速度を消す
								boss->vel.y = 0.0f;
							}
							else
							{
								// フレームを進めない
								boss->frame--;

								// 加速度を下げない
								boss->acceleration.y = 1.0f;
							}
						}

						// 140フレームで落下する
						if (boss->frame == 140)
						{
							boss->vel.y = 14.0f;
							boss->acceleration.y = 0.0f;
						}

						// 141フレームで、着地するまで、フレームを進めない
						if (boss->frame == 141)
						{
							if (boss->flug.isJump)
							{
								boss->frame--;
							}
						}

						// 150フレームで攻撃を停止する
						if (boss->frame >= 150)
						{
							// 攻撃しなくなる（攻撃フラグがfalseになる）
							boss->isAttack = false;
							boss->attackNo = -1;

							// ボスのフレームを攻撃前に戻す
							boss->frame = -100;
						}


						break;
					}
				}
			}
			else
			{
				// 60フレーム前は、プレイヤーに近くづくように動く
				if (player->pos.world.x + 100.0f < boss->pos.world.x)
				{
					boss->pos.world.x += -2.0f;
				}

				if (player->pos.world.x - 100.0f > boss->pos.world.x)
				{
					boss->pos.world.x += 2.0f;
				}

				// プレイヤーの方向を向く
				if (player->pos.world.x < boss->pos.world.x)
				{
					boss->directionNo = DIRECTION_LEFT;
				}
				else if (player->pos.world.x > boss->pos.world.x)
				{
					boss->directionNo = DIRECTION_RIGHT;
				}
			}

			break;
		}


		/*   ジャンプ   */
		
		// ジャンプしたら（ジャンプフラグがtrueになったら）上に飛び、落下する
		if (boss->flug.isJump)
		{
			// 徐々に落下する
			if (boss->acceleration.y > -1.0f)
			{
				boss->acceleration.y += -0.05f;
			}
		}
		else
		{
			// 上下の動きが止まる
			boss->vel.y = 0.0f;
			boss->acceleration.y = 0.0f;
		}

		// 縦に動かす
		boss->pos.world.y += boss->vel.y * boss->acceleration.y;

		// 地面についたら、ジャンプしなくなる（ジャンプフラグがfalseになる）
		if (boss->pos.world.y - boss->radius.y <= 0.0f)
		{
			boss->flug.isJump = false;
		}


		/*   体力   */

		// 体力がなくなったら、倒せる（出現、復活フラグがfalseになる）
		if (boss->hp.quantity <= 0)
		{
			boss->isArrival = false;
			boss->respawn.isRespawn = false;
		}


		/*   位置   */

		// 画面外に出ないようにする
		if (boss->pos.world.y - boss->radius.y < 0.0f)
		{
			boss->pos.world.y = boss->radius.y;
		}

		if (boss->pos.world.x - boss->radius.x < 0.0f)
		{
			boss->pos.world.x = boss->radius.x;
		}

		if (boss->pos.world.x + boss->radius.x > static_cast<float>(kScreenWidth))
		{
			boss->pos.world.x = static_cast<float>(kScreenWidth) - boss->radius.x;
		}
	}
}