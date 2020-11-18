#include "GameScene.h"
#include "TurnManager.h"

std::string DxLibPlus::CGameScene::m_Message = "";

namespace DxLibPlus
{
	CGameScene::CGameScene(void)
		: CSceneBase()
	{
		//サウンド全ストップ
		theSoundManager.Stop();
	}

	CGameScene::~CGameScene(void)
	{
	}

	void CGameScene::Initialize(void)
	{
		//ターンの初期化
		theTurnManager.SetTurn(TURN_PLAYER);

		//プレイヤーの読み込み
		m_Player.Load();
		//敵の読み込み
		m_Enemy.Load();
		//プレイヤーの初期化
		m_Player.Initialize();
		//敵の初期化
		m_Enemy.Initialize();

		//バトルBGMの再生
		theSoundManager.Play(SoundFile[SOUNDKEY_BGM_BATTLE].key);
	}

	void CGameScene::Update(void)
	{
		//ゲームオーバーかクリアの判定
		unsigned int check = m_GameState & STATE_CHECK;
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
				//ReStart();
				//決定音を鳴らす
				theSoundManager.Play(SoundFile[SOUNDKEY_SE_ENTER].key);
				m_bEnd = true;
				m_NextScene = SCENE_TITLE;
			}
			return;
		}

		//現在のターン取得
		Turn nowTurn = theTurnManager.GetTurn();
		//ターンが変わった時、攻撃の処理をする
		if (!m_bChangeTurn && theTurnManager.IsChanged())
		{
			RefreshChangeTurn(nowTurn);
			return;
		}
		//ターン切り替え完了までの処理
		else if (m_bChangeTurn && !theTurnManager.IsChanged())
		{
			//現在のターンにするための処理
			switch (nowTurn)
			{
			case TURN_PLAYER:
				RefreshPlayer();
				break;
			case TURN_ENEMY:
				m_bChangeTurn = false;
				break;
			}
			return;
		}

		//ターンによって更新
		switch (nowTurn)
		{
		case TURN_PLAYER:
			m_Player.Update();
			m_bEnd = m_Player.IsEnd();
			if (m_bEnd)
			{
				m_NextScene = SCENE_TITLE;
			}
			break;
		case TURN_ENEMY:
			//ダメージの処理
			m_Enemy.RefreshDmg();
			//敵の更新
			m_Enemy.Update();
			break;
		}
		CheckGameOver();
	}

	void CGameScene::Render(void)
	{
		//敵の描画
		m_Enemy.Render();
		//コマンドボックスの描画
		DxLib::DrawBox(CommandRectX, CommandRectY, CommandRectX + CommandRectW, CommandRectY + CommandRectH, DxLib::GetColor(0, 0, 0), true);
		DxLib::DrawBox(CommandRectX, CommandRectY, CommandRectX + CommandRectW, CommandRectY + CommandRectH, DxLib::GetColor(255, 255, 255), false);
		//メッセージボックスの描画
		DxLib::DrawBox(MessageRectX, MessageRectY, MessageRectX + MessageRectW, MessageRectY + MessageRectH, DxLib::GetColor(0, 0, 0), true);
		DxLib::DrawBox(MessageRectX, MessageRectY, MessageRectX + MessageRectW, MessageRectY + MessageRectH, DxLib::GetColor(255, 255, 255), false);
		//メッセージの描画
		DxLib::DrawFormatString(MessageRectX + FontSize, MessageRectY + FontMargin, DxLib::GetColor(255, 255, 255), "%s", m_Message.c_str());
		//プレイヤーの描画
		m_Player.Render();
		//プレイヤーのステータス描画
		if (m_Player.GetDamageWait() % 10 != 1)
		{
			unsigned int Color = DxLib::GetColor(255, 255, 255);
			//死んでいれば色を赤くする
			if (m_Player.IsDead())
			{
				Color = DxLib::GetColor(192, 64, 64);
			}
			//ステータスボックスの描画
			DxLib::DrawBox(PlayerRectX, PlayerRectY, PlayerRectX + PlayerRectW, PlayerRectY + PlayerRectH, DxLib::GetColor(0, 0, 0), true);
			DxLib::DrawBox(PlayerRectX, PlayerRectY, PlayerRectX + PlayerRectW, PlayerRectY + PlayerRectH, Color, false);
			//ステータスの描画
			m_Player.RenderStatus();
		}
		//エフェクトの描画
		theEffectManager.Render();
	}

	void CGameScene::Release(void)
	{
		//各解放処理
		m_Player.Release();
		m_Enemy.Release();
	}

	std::string & CGameScene::GetMessage(void)
	{
		return m_Message;
	}

	void CGameScene::SetMessage(const std::string & str)
	{
		m_Message = str;
	}

	// ********************************************************************************
	/// <summary>
	/// ゲームクリア状態の処理
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CGameScene::GameStateClear(void)
	{
		//メッセージの変更
		m_Message = "敵を倒した！\nEnterキーでタイトルへ！";
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
	void CGameScene::GameStateOver(void)
	{
		//メッセージの変更
		m_Message = "死んでしまった！\nEnterキーでタイトルへ！";
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
	void CGameScene::ReStart(void)
	{
		//プレイヤーの初期化
		m_Player.Initialize();
		//敵の初期化
		m_Enemy.Initialize();
		//ゲームの状態の初期化
		m_GameState = STATE_GAME;
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
	void CGameScene::DmgPlayer(void)
	{
		//敵が死んでいれば攻撃させない
		if (m_Enemy.IsDead())
		{
			return;
		}
		//敵の攻撃力を取得
		int dmg = m_Enemy.GetAttack();
		//プレイヤーにダメージを与える
		m_Player.Dmg(dmg);
		//メッセージの変更
		m_Message += "\nプレイヤーに" + std::to_string(dmg) + "のダメージ！";
	}
	// ********************************************************************************
	/// <summary>
	/// 敵へのダメージ処理
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CGameScene::DmgEnemy(void)
	{
		//プレイヤーの攻撃力を取得
		int dmg = m_Player.GetAttack();
		//敵にダメージを与える
		m_Enemy.Dmg(dmg);
		//メッセージの変更
		m_Message += "\n敵に" + std::to_string(dmg) + "のダメージ！";
	}
	// ********************************************************************************
	/// <summary>
	/// プレイヤーのターンにつなぐまでの処理
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CGameScene::RefreshPlayer(void)
	{
		//プレイヤーのダメージ表現
		m_Player.RefreshDmg();
		//ダメージ表現中にターンは切り替えない
		if (m_Player.GetDamageWait() <= 0)
		{
			m_Player.TurnStart();
			m_bChangeTurn = false;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// ターンが変わった時の次のターンまでつなぐ処理
	/// </summary>
	/// <param name="turn">現在のターン</param>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	void CGameScene::RefreshChangeTurn(const Turn & turn)
	{
		//ターンの切り替え処理をする
		m_bChangeTurn = true;
		//現在のターンがプレイヤーなら敵からの攻撃をくらう
		switch (turn)
		{
		case TURN_PLAYER:
			DmgPlayer();
			break;
		case TURN_ENEMY:
			DmgEnemy();
			break;
		}
		//敵が死んでいればゲームクリア状態にする
		if (m_Enemy.IsDead() && m_Enemy.GetDamageWait() <= 0)
		{
			m_GameState = STATE_GAMECLEAR;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// ゲームオーバーの監視
	/// </summary>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	void CGameScene::CheckGameOver(void)
	{
		//死亡チェック
		if (m_Player.IsDead() && (m_Player.GetDamageWait() <= 0))
		{
			m_GameState |= STATE_GAMEOVER;
		}
	}
}
