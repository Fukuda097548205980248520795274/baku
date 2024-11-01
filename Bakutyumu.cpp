#include <Novice.h>
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
	player->radius = { 32.0f , 32.0f };
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


	/*   横移動操作   */

	// 横移動を初期化する
	player->vel.x = 0.0f;

	// Aキーで、左に移動する
	if (keys[DIK_A])
	{
		// 左を向く
		player->directionNo = DIRECTION_LEFT;

		if (player->pos.world.x - player->radius.x > 0.0f)
		{
			player->vel.x = -6.0f;
		}
	}

	// Dキーで、右に移動する
	if (keys[DIK_D])
	{
		// 左を向く
		player->directionNo = DIRECTION_RIGHT;

		if (player->pos.world.x + player->radius.x < static_cast<float>(kScreenWidth))
		{
			player->vel.x = 6.0f;
		}
	}

	// プレイヤーを横に動かす
	player->pos.world.x += player->vel.x;


	/*   ジャンプ操作   */

	// Jキーで、ジャンプする（ジャンプフラグがtrueになる）
	if (!preKeys[DIK_J] && keys[DIK_J])
	{
		if (player->flug.isJump == false)
		{
			player->flug.isJump = true;

			// 加速度が上がる
			player->acceleration.y = 1.0f;
		} else
		{
			if (player->flug.isTwoStepJump == false)
			{
				player->flug.isTwoStepJump = true;

				player->acceleration.y = 1.0f;
			}
		}
	}

	// ジャンプしている（ジャンプフラグがtrueである）と、上に飛ぶ
	if (player->flug.isJump)
	{
		player->vel.y = 16.0f;

		if (player->acceleration.y > -1.0f)
		{
			player->acceleration.y += -0.05f;
		}
	} else
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


	/*   プレイヤーの位置   */

	// 移動範囲がに出たら元の位置に戻す
	if (player->pos.world.y - player->radius.y < 0.0f)
	{
		player->pos.world.y = player->radius.y;
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

	for (int i = 0; i < kBombNum; i++)
	{
		if (bomb[i].isPlayerHave == false && bomb[i].isShot == false)
		{
			// 爆弾を持つ（所持フラグがtrueになる）
			bomb[i].isPlayerHave = true;

			// 位置
			if (player->directionNo == DIRECTION_RIGHT)
			{
				bomb[i].pos.world = { player->pos.world.x + 50.0f  , player->pos.world.y };
			} else if (player->directionNo == DIRECTION_LEFT)
			{
				bomb[i].pos.world = { player->pos.world.x - 50.0f  , player->pos.world.y };
			}

			// 移動速度
			bomb[i].vel = { 0.0f , 0.0f };

			// 加速度
			bomb[i].acceleration = { 0.0f , 0.0f };

			// 図形の半径
			bomb[i].radius = { 8.0f , 8.0f };

			break;
		}
	}
}

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
void PlayerBombShot(Bomb* bomb, float posX, float posY, float velX, float velY, float accelerationX, float accelerationY, float radius)
{
	// null を探す
	if (bomb == nullptr)
	{
		return;
	}

	// 持っている（所持フラグがtrueである）ボムを投げる
	for (int i = 0; i < kBombNum; i++)
	{
		if (bomb[i].isPlayerHave)
		{
			// 爆弾を離す（所持フラグがfalseになる）
			bomb[i].isPlayerHave = false;

			// 爆弾が発射される（発射フラグがfalseになる）
			bomb[i].isShot = true;

			bomb[i].pos.world = { posX , posY };

			bomb[i].vel = { velX , velY };

			bomb[i].acceleration = { accelerationX , accelerationY };

			bomb[i].radius = { radius , radius };

			break;
		}
	}
}

/// <summary>
/// プレイヤーが爆弾を投げる
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="bomb">爆弾</param>
/// <param name="keys">キー</param>
/// <param name="preKeys">前のキー</param>
void PlayerThrowBomb(Player* player, Bomb* bomb, const char* keys, const char* preKeys)
{
	// null を探す
	if (player == nullptr || bomb == nullptr)
	{
		return;
	}

	// スペースキーで、爆弾を持つ
	if (!preKeys[DIK_SPACE] && keys[DIK_SPACE])
	{
		if (player->flug.isBombHave == false)
		{
			// 爆弾を持つ（所持フラグ）
			player->flug.isBombHave = true;

			// 爆弾を持つ
			PlayerHaveBomb(player, bomb);
		} else
		{
			// 位置
			if (player->directionNo == DIRECTION_RIGHT)
			{
				// 右に進んでいるとき
				if (player->vel.x > 0.0f)
				{
					// 爆弾を投げる
					PlayerBombShot(bomb, player->pos.world.x + 50.0f, player->pos.world.y, 8.0f, 6.0f, 1.0f, 0.0f, 8.0f);
				} else
				{
					// 止まっているとき

					// 爆弾を投げる
					PlayerBombShot(bomb, player->pos.world.x + 50.0f, player->pos.world.y, 6.0f, 6.0f, 1.0f, 0.0f, 8.0f);
				}
			} else if (player->directionNo == DIRECTION_LEFT)
			{
				// 左に進んでいるとき
				if (player->vel.x < 0.0f)
				{
					// 爆弾を投げる
					PlayerBombShot(bomb, player->pos.world.x - 50.0f, player->pos.world.y, -8.0f, 6.0f, 1.0f, 0.0f, 8.0f);
				} else
				{
					// 止まっているとき

					// 爆弾を投げる
					PlayerBombShot(bomb, player->pos.world.x - 50.0f, player->pos.world.y, -6.0f, 6.0f, 1.0f, 0.0f, 8.0f);
				}
			}

			// 爆弾を離す（所持フラグがfalseになる）
			player->flug.isBombHave = false;
		}
	}

	// 所持している（所持フラグがtrueである）ときは、爆弾がプレイヤーの横にある
	if (player->flug.isBombHave)
	{
		for (int i = 0; i < kBombNum; i++)
		{
			if (bomb[i].isPlayerHave)
			{
				// 位置
				if (player->directionNo == DIRECTION_RIGHT)
				{
					bomb[i].pos.world = { player->pos.world.x + 50.0f  , player->pos.world.y };
				} else if (player->directionNo == DIRECTION_LEFT)
				{
					bomb[i].pos.world = { player->pos.world.x - 50.0f  , player->pos.world.y };
				}
			}
		}
	}
}

/// <summary>
/// 爆弾を動かす
/// </summary>
/// <param name="bomb">爆弾</param>
void BombMove(Bomb* bomb)
{
	if (bomb == nullptr)
	{
		return;
	}

	// 発射されている（発射フラグがtrueである）弾を動かす
	for (int i = 0; i < kBombNum; i++)
	{
		if (bomb[i].isShot)
		{
			// 落下させる
			if (bomb[i].acceleration.y > -3.0f)
			{
				bomb[i].acceleration.y += -0.1f;
			} else
			{
				bomb[i].acceleration.y = -3.0f;
			}

			// 飛ぶ速度を低下させる
			if (bomb[i].acceleration.x > 0.0f)
			{
				bomb[i].acceleration.x += -0.02f;
			} else
			{
				bomb[i].acceleration.x = 0.0f;
			}

			// 反発させる
			if (bomb[i].pos.world.y - bomb[i].radius.y <= 0.0f)
			{
				bomb[i].acceleration.y *= -0.3f;

				bomb[i].pos.world.y = bomb[i].radius.y;

				if (bomb[i].acceleration.y < 0.05f && bomb[i].acceleration.y > -0.05f)
				{
					bomb[i].acceleration.y = 0.0f;
				}
			}

			// 弾を動かす
			bomb[i].pos.world.x += bomb[i].vel.x * bomb[i].acceleration.x;
			bomb[i].pos.world.y += bomb[i].vel.y * bomb[i].acceleration.y;
		}
	}
}