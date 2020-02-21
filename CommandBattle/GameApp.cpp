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

//サウンド登録情報
SoundMngInfo SoundFile[] = {
	{ "bgm_battle"       , "Sound/BGM/battle.mp3"    },
	{ "bgm_clear"        , "Sound/BGM/gameclear.mp3" },
	{ "bgm_over"         , "Sound/BGM/gameover.mp3"  },
	{ "se_skill_fire"    , "Sound/SE/fire.mp3"       },
	{ "se_skill_ice"     , "Sound/SE/ice.mp3"        },
	{ "se_skill_thunder" , "Sound/SE/thunder.mp3"    },
	{ "se_skill_slash"   , "Sound/SE/slash.mp3"      },
	{ "se_select"        , "Sound/SE/select.mp3"     },
	{ "se_enter"         , "Sound/SE/enter.mp3"      },
	{ "se_enemyattack"   , "Sound/SE/enemyattack.mp3"},
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

CPlayer		gPlayer;					//!<プレイヤー
CEnemy		gEnemy;						//!<敵
bool		gbChangeTurn = false;		//!<ターン変更フラグ
int			gGameState = STATE_GAME;	//!<ゲームの状態

std::string gMessage = "";				//!<メッセージ

namespace DxLibPlus
{
	// ********************************************************************************
	/// <summary>
	/// 初期化
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CGameApp::Initialize(void)
	{
		//フルパス取得
		char pass[MAX_PATH + 1];
		GetCurrentDirectory(MAX_PATH + 1, pass);
		std::string full = pass;
		//カレントパスに変換
		int len = full.length();
		int lastlen = full.find_last_of("\\");
		std::string current = full.substr(lastlen + 1, len - lastlen);
		//現在のファイル位置からリソースフォルダの設定
		if (current == "CommandBattle")
		{
			SetCurrentDirectory("../Resource");
		}
		else if (current == "StepUpFestival")
		{
			SetCurrentDirectory("Resource");
		}
		
		//画像の読み込み
		theTextureManager.LoadList(TexFile, TEXKEY_COUNT);
		
		//サウンドの読み込み
		for (int i = 0; i < SOUNDKEY_COUNT; i++)
		{
			theSoundManager.Load(SoundFile[i].key, SoundFile[i].file);
			if (i < SOUNDKEY_BGM_COUNT)
			{
				theSoundManager.SetLoop(SoundFile[i].key, true);
			}
		}

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
		theSoundManager.Play(SoundFile[SOUNDKEY_BGM_BATTLE].key);
	}
	// ********************************************************************************
	/// <summary>
	/// 更新
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CGameApp::Update(void)
	{
		//ゲームオーバーかクリアの判定
		unsigned int check = gGameState & STATE_CHECK;
		//状態別にメッセージを設定する
		switch (check)
		{
		case STATE_GAMECLEAR:
			gMessage = "敵を倒した！\nEnterキーでリスタート！";
			if (theSoundManager.IsPlay(SoundFile[SOUNDKEY_BGM_BATTLE].key))
			{
				theSoundManager.Stop(SoundFile[SOUNDKEY_BGM_BATTLE].key);
			}
			if (!theSoundManager.IsPlay(SoundFile[SOUNDKEY_BGM_CLEAR].key))
			{
				theSoundManager.Play(SoundFile[SOUNDKEY_BGM_CLEAR].key);
			}
			break;
		case STATE_GAMEOVER:
			gMessage = "死んでしまった！\nEnterキーでリスタート！";
			if (theSoundManager.IsPlay(SoundFile[SOUNDKEY_BGM_BATTLE].key))
			{
				theSoundManager.Stop(SoundFile[SOUNDKEY_BGM_BATTLE].key);
			}
			if (!theSoundManager.IsPlay(SoundFile[SOUNDKEY_BGM_OVER].key))
			{
				theSoundManager.Play(SoundFile[SOUNDKEY_BGM_OVER].key);
			}
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
				theSoundManager.Stop();
				theSoundManager.Play(SoundFile[SOUNDKEY_SE_ENTER].key);
				theSoundManager.Play(SoundFile[SOUNDKEY_BGM_BATTLE].key);
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
				theSoundManager.Play(SoundFile[SOUNDKEY_SE_ENEMYATTACK].key);
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
		theSoundManager.Release();
	}
}
