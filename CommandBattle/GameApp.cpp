/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	ゲームアプリクラス

															@author	いのうえ
															@date	2020.02.14
*//**************************************************************************/

//INCLUDE
#include "GameApp.h"
#include "GameDefine.h"
#include "Player.h"
#include "Enemy.h"

//画像登録情報
TexMngInfo TexFile[] = {
   { "dragon_blue"   , "Enemy/dragon_blue.png"   },
   { "dragon_red"    , "Enemy/dragon_red.png"    },
   { "dragon_green"  , "Enemy/dragon_green.png"  },
   { "dragon_komodo" , "Enemy/komodo_dragon.png" },
   { "effect_fire"   , "Effect/Fire.png"         },
   { "effect_ice"    , "Effect/Ice.png"          },
   { "effect_thunder", "Effect/Thunder.png"      },
   { "effect_slash"  , "Effect/Slash.png"        },
   { "cursor"        , "cursor.png"              },
};

//エフェクト作成情報
Animation<10> EffectAnim[] = {
	{
		"FIRE", 0, 0, 192, 192, false,
		{
			{ 5, 0, 0 }, { 5, 1, 0 },{ 5, 2, 0 }, { 5, 3, 0 }, { 5, 4, 0 },
			{ 5, 0, 1 }, { 5, 1, 1 },{ 5, 2, 1 }, { 5, 3, 1 }, { 5, 4, 1 }
		}
	},
	{
		"ICE", 0, 0, 192, 192, false,
		{
			{ 5, 0, 0 }, { 5, 1, 0 },{ 5, 2, 0 }, { 5, 3, 0 }, { 5, 4, 0 },
			{ 5, 0, 1 }, { 5, 1, 1 },{ 5, 2, 1 }, { 5, 3, 1 }, { 5, 4, 1 }
		}
	},
	{
		"THUNDER", 0, 0, 192, 192, false,
		{
			{ 5, 0, 0 }, { 5, 1, 0 },{ 5, 2, 0 }, { 5, 3, 0 }, { 5, 4, 0 },
			{ 5, 0, 1 }, { 5, 1, 1 },{ 5, 2, 1 }, { 5, 3, 1 }, { 5, 4, 1 }
		}
	},
	{
		"SLASH", 0, 0, 192, 192, false,
		{
			{ 5, 0, 0 }, { 5, 1, 0 },{ 5, 2, 0 }, { 5, 3, 0 }, { 5, 4, 0 },
			{ 5, 0, 1 }, { 5, 1, 1 },{ 5, 2, 1 }, { 5, 3, 1 }, { 5, 4, 1 }
		}
	},
};

CPlayer		gPlayer;
CEnemy		gEnemy;
bool		gbChangeTurn = false;
int			gGameState = STATE_GAME;

std::string gMessage = "";

namespace DxLibPlus
{
	/*************************************************************************//*!
			@brief			初期化
			@param			None

			@return			None
	*//**************************************************************************/
	void CGameApp::Initialize(void)
	{
		//リソースフォルダの設定
		SetCurrentDirectory("../Resource");
		//画像の読み込み
		theTextureManager.LoadList(TexFile, TEXKEY_COUNT);

		//エフェクトの作成
		for (int i = 0; i < SKILL_COUNT; i++)
		{
			theEffectManager.CreateEffect(static_cast<EffectType>(i), &EffectAnim[i], 1);
		}

		//ターンの初期化
		theTurnManager.SetTurn(TURN_PLAYER);

		gPlayer.Load();
		gEnemy.Load();
		gPlayer.Initialize();
		gEnemy.Initialize();
	}
	/*************************************************************************//*!
			@brief			更新
			@param			None

			@return			None
	*//**************************************************************************/
	void CGameApp::Update(void)
	{
		//ゲームオーバーかクリアの判定
		unsigned int check = gGameState & STATE_CHECK;
		//状態別にメッセージを設定する
		switch (check)
		{
		case STATE_GAMECLEAR:
			gMessage = "敵を倒した！\nEnterキーでリスタート！";
			break;
		case STATE_GAMEOVER:
			gMessage = "死んでしまった！\nEnterキーでリスタート！";
			break;
		}
		//リスタートの処理
		if (check)
		{
			if (theInput.IsKeyPush(KEY_INPUT_RETURN))
			{
				gPlayer.Initialize();
				gEnemy.Initialize();
				gGameState = STATE_GAME;
				theTurnManager.SetTurn(TURN_PLAYER);
			}
			return;
		}

		//現在のターン取得
		Turn nowTurn = theTurnManager.GetTurn();
		//ターンが変わった時、攻撃、アイテムの処理をする
		if (!gbChangeTurn && theTurnManager.IsChanged())
		{
			gbChangeTurn = true;
			switch (nowTurn)
			{
			case TURN_PLAYER:
				{
					if (gEnemy.IsDead())
					{
						break;
					}
					int dmg = gEnemy.GetAttack();
					gPlayer.Dmg(dmg);
					gMessage += "\nプレイヤーに" + std::to_string(dmg) + "のダメージ！";
					break;
				}
			case TURN_ENEMY:
				{
					int dmg = gPlayer.GetAttack();
					gEnemy.Dmg(dmg);
					gMessage += "\n敵に" + std::to_string(dmg) + "のダメージ！";
					break;
				}
			}
			//敵が死んでいるかの判定
			if (gEnemy.IsDead())
			{
				if (gEnemy.GetDamageWait() <= 0)
				{
					gGameState |= STATE_GAMECLEAR;
				}
			}
			return;
		}
		else if (gbChangeTurn && !theTurnManager.IsChanged())
		{
			switch (nowTurn)
			{
			case TURN_PLAYER:
				gPlayer.RefreshDmg();
				if (gPlayer.GetDamageWait() <= 0)
				{
					gPlayer.TurnStart();
					gbChangeTurn = false;
				}
				break;
			case TURN_ENEMY:
				gbChangeTurn = false;
				break;
			}
			return;
		}

		//ターンによって更新
		switch (nowTurn)
		{
		case TURN_PLAYER:
			gPlayer.Update();
			break;
		case TURN_ENEMY:
			gEnemy.RefreshDmg();
			gEnemy.Update();
			if (gEnemy.GetDamageWait() <= 0)
			{
				gMessage = "敵の攻撃！";
				theTurnManager.SetTurn(TURN_PLAYER);
			}
			break;
		}
		//死亡チェック
		if (gPlayer.IsDead() && (gPlayer.GetDamageWait() <= 0))
		{
			gGameState |= STATE_GAMEOVER;
		}
	}
	/*************************************************************************//*!
			@brief			描画
			@param			None

			@return			None
	*//**************************************************************************/
	void CGameApp::Render(void)
	{
		gEnemy.Render();

		//コマンド四角の描画
		DxLib::DrawBox(CommandRectX, CommandRectY, CommandRectX + CommandRectW, CommandRectY + CommandRectH, DxLib::GetColor(0, 0, 0), true);
		DxLib::DrawBox(CommandRectX, CommandRectY, CommandRectX + CommandRectW, CommandRectY + CommandRectH, DxLib::GetColor(255, 255, 255), false);
		DxLib::DrawBox(MessageRectX, MessageRectY, MessageRectX + MessageRectW, MessageRectY + MessageRectH, DxLib::GetColor(0, 0, 0), true);
		DxLib::DrawBox(MessageRectX, MessageRectY, MessageRectX + MessageRectW, MessageRectY + MessageRectH, DxLib::GetColor(255, 255, 255), false);
		DxLib::DrawFormatString(MessageRectX + FontSize, MessageRectY + FontMargin, DxLib::GetColor(255, 255, 255), "%s", gMessage.c_str());
		gPlayer.Render();
		if (gPlayer.GetDamageWait() % 10 != 1)
		{
			unsigned int Color = DxLib::GetColor(255, 255, 255);
			if (gPlayer.IsDead())
			{
				Color = DxLib::GetColor(192, 64, 64);
			}
			DxLib::DrawBox(PlayerRectX, PlayerRectY, PlayerRectX + PlayerRectW, PlayerRectY + PlayerRectH, DxLib::GetColor(0, 0, 0), true);
			DxLib::DrawBox(PlayerRectX, PlayerRectY, PlayerRectX + PlayerRectW, PlayerRectY + PlayerRectH, Color, false);
			gPlayer.RenderStatus();
		}

		theEffectManager.Render();
	}
	/*************************************************************************//*!
			@brief			解放
			@param			None

			@return			None
	*//**************************************************************************/
	void CGameApp::Release(void)
	{
		gPlayer.Release();
		gEnemy.Release();
		theEffectManager.Release();
	}
}
