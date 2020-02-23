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
		//リソースフォルダの指定
		SetResourceFolder();
		
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
			theEffectManager.CreateEffect(static_cast<SkillType>(i), &EffectAnim[i], 1);
		}

		//ターンの初期化
		theTurnManager.SetTurn(TURN_PLAYER);

		//プレイヤーの読み込み
		gPlayer.Load();
		//敵の読み込み
		gEnemy.Load();
		//プレイヤーの初期化
		gPlayer.Initialize();
		//敵の初期化
		gEnemy.Initialize();

		//バトルBGMの再生
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
			GameStateClear();
			break;
		case STATE_GAMEOVER:
			GameStateOver();
			break;
		}
		//ゲームオーバーかゲームクリアでエンターキーを押すとリスタート
		if (check)
		{
			if (theInput.IsKeyPush(KEY_INPUT_RETURN))
			{
				//リスタートの処理
				ReStart();
				//決定音を鳴らす
				theSoundManager.Play(SoundFile[SOUNDKEY_SE_ENTER].key);
			}
			return;
		}

		//現在のターン取得
		Turn nowTurn = theTurnManager.GetTurn();
		//ターンが変わった時、攻撃、アイテムの処理をする
		if (!gbChangeTurn && theTurnManager.IsChanged())
		{
			//ターンの切り替え処理をする
			gbChangeTurn = true;
			//現在のターンがプレイヤーなら敵からの攻撃をくらう
			switch (nowTurn)
			{
			case TURN_PLAYER:
				DmgPlayer();
				break;
			case TURN_ENEMY:
				DmgEnemy();
				break;
			}
			//敵が死んでいればゲームクリア状態にする
			if (gEnemy.IsDead() && gEnemy.GetDamageWait() <= 0)
			{
				gGameState = STATE_GAMECLEAR;
			}
			return;
		}
		//ターン切り替え完了までの処理
		else if (gbChangeTurn && !theTurnManager.IsChanged())
		{
			//現在のターンにするための処理
			switch (nowTurn)
			{
			case TURN_PLAYER:
				RefreshPlayer();
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
				theTurnManager.SetTurn(TURN_PLAYER);
				gMessage = "敵の攻撃！";
				if (!gEnemy.IsDead())
				{
					theSoundManager.Play(SoundFile[SOUNDKEY_SE_ENEMYATTACK].key);
				}
			}
			break;
		}
		//死亡チェック
		if (gPlayer.IsDead() && (gPlayer.GetDamageWait() <= 0))
		{
			gGameState |= STATE_GAMEOVER;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// 描画
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CGameApp::Render(void)
	{
		//敵の描画
		gEnemy.Render();
		//コマンドボックスの描画
		DxLib::DrawBox(CommandRectX, CommandRectY, CommandRectX + CommandRectW, CommandRectY + CommandRectH, DxLib::GetColor(0, 0, 0), true);
		DxLib::DrawBox(CommandRectX, CommandRectY, CommandRectX + CommandRectW, CommandRectY + CommandRectH, DxLib::GetColor(255, 255, 255), false);
		//メッセージボックスの描画
		DxLib::DrawBox(MessageRectX, MessageRectY, MessageRectX + MessageRectW, MessageRectY + MessageRectH, DxLib::GetColor(0, 0, 0), true);
		DxLib::DrawBox(MessageRectX, MessageRectY, MessageRectX + MessageRectW, MessageRectY + MessageRectH, DxLib::GetColor(255, 255, 255), false);
		//メッセージの描画
		DxLib::DrawFormatString(MessageRectX + FontSize, MessageRectY + FontMargin, DxLib::GetColor(255, 255, 255), "%s", gMessage.c_str());
		//プレイヤーの描画
		gPlayer.Render();
		//プレイヤーのステータス描画
		if (gPlayer.GetDamageWait() % 10 != 1)
		{
			unsigned int Color = DxLib::GetColor(255, 255, 255);
			//死んでいれば色を赤くする
			if (gPlayer.IsDead())
			{
				Color = DxLib::GetColor(192, 64, 64);
			}
			//ステータスボックスの描画
			DxLib::DrawBox(PlayerRectX, PlayerRectY, PlayerRectX + PlayerRectW, PlayerRectY + PlayerRectH, DxLib::GetColor(0, 0, 0), true);
			DxLib::DrawBox(PlayerRectX, PlayerRectY, PlayerRectX + PlayerRectW, PlayerRectY + PlayerRectH, Color, false);
			//ステータスの描画
			gPlayer.RenderStatus();
		}
		//エフェクトの描画
		theEffectManager.Render();
	}
	// ********************************************************************************
	/// <summary>
	/// 解放
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CGameApp::Release(void)
	{
		//各解放処理
		gPlayer.Release();
		gEnemy.Release();
		theEffectManager.Release();
		theSoundManager.Release();
	}
	// ********************************************************************************
	/// <summary>
	/// リソースフォルダの指定
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CGameApp::SetResourceFolder(void)
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
	}
	// ********************************************************************************
	/// <summary>
	/// ゲームクリア状態の処理
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CGameApp::GameStateClear(void)
	{
		//メッセージの変更
		gMessage = "敵を倒した！\nEnterキーでリスタート！";
		//バトルBGMが鳴っていれば止める
		if (theSoundManager.IsPlay(SoundFile[SOUNDKEY_BGM_BATTLE].key))
		{
			theSoundManager.Stop(SoundFile[SOUNDKEY_BGM_BATTLE].key);
		}
		//クリア音楽が鳴っていなければならす
		if (!theSoundManager.IsPlay(SoundFile[SOUNDKEY_BGM_CLEAR].key))
		{
			theSoundManager.Play(SoundFile[SOUNDKEY_BGM_CLEAR].key);
		}
	}
	// ********************************************************************************
	/// <summary>
	/// ゲームオーバー状態の処理
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CGameApp::GameStateOver(void)
	{
		//メッセージの変更
		gMessage = "死んでしまった！\nEnterキーでリスタート！";
		//バトルBGMが鳴っていれば止める
		if (theSoundManager.IsPlay(SoundFile[SOUNDKEY_BGM_BATTLE].key))
		{
			theSoundManager.Stop(SoundFile[SOUNDKEY_BGM_BATTLE].key);
		}
		//ゲームオーバー音楽が鳴っていなければならす
		if (!theSoundManager.IsPlay(SoundFile[SOUNDKEY_BGM_OVER].key))
		{
			theSoundManager.Play(SoundFile[SOUNDKEY_BGM_OVER].key);
		}
	}
	// ********************************************************************************
	/// <summary>
	/// リスタート時の初期化
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CGameApp::ReStart(void)
	{
		//プレイヤーの初期化
		gPlayer.Initialize();
		//敵の初期化
		gEnemy.Initialize();
		//ゲームの状態の初期化
		gGameState = STATE_GAME;
		//ターンの初期化
		theTurnManager.SetTurn(TURN_PLAYER);
		//サウンド全ストップ
		theSoundManager.Stop();
		//バトルBGMの再生
		theSoundManager.Play(SoundFile[SOUNDKEY_BGM_BATTLE].key);
	}
	// ********************************************************************************
	/// <summary>
	/// プレイヤーへのダメージ処理
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CGameApp::DmgPlayer(void)
	{
		//敵が死んでいれば攻撃させない
		if (gEnemy.IsDead())
		{
			return;
		}
		//敵の攻撃力を取得
		int dmg = gEnemy.GetAttack();
		//プレイヤーにダメージを与える
		gPlayer.Dmg(dmg);
		//メッセージの変更
		gMessage += "\nプレイヤーに" + std::to_string(dmg) + "のダメージ！";
	}
	// ********************************************************************************
	/// <summary>
	/// 敵へのダメージ処理
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CGameApp::DmgEnemy(void)
	{
		//プレイヤーの攻撃力を取得
		int dmg = gPlayer.GetAttack();
		//敵にダメージを与える
		gEnemy.Dmg(dmg);
		//メッセージの変更
		gMessage += "\n敵に" + std::to_string(dmg) + "のダメージ！";
	}
	// ********************************************************************************
	/// <summary>
	/// プレイヤーのターンにつなぐまでの処理
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CGameApp::RefreshPlayer(void)
	{
		//プレイヤーのダメージ表現
		gPlayer.RefreshDmg();
		//ダメージ表現中にターンは切り替えない
		if (gPlayer.GetDamageWait() <= 0)
		{
			gPlayer.TurnStart();
			gbChangeTurn = false;
		}
	}
}
