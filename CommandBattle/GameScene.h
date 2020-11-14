#pragma once
//INCLUDE
#include "SceneBase.h"
#include "GameDefine.h"
#include "Player.h"
#include "Enemy.h"

namespace DxLibPlus
{
	//ゲームシーンクラス
	class CGameScene : public CSceneBase
	{
	protected:

		CPlayer		m_Player;					//!<プレイヤー
		CEnemy		m_Enemy;					//!<敵
		bool		m_bChangeTurn = false;		//!<ターン変更フラグ
		int			m_GameState = STATE_GAME;	//!<ゲームの状態

		std::string m_Message = "";				//!<メッセージ

	public:
		//コンストラクタ
		CGameScene(void);
		//デストラクタ
		virtual ~CGameScene(void) override;
		//初期化
		virtual void Initialize(void) override;
		//更新
		virtual void Update(void) override;
		//描画
		virtual void Render(void) override;
		//解放
		virtual void Release(void) override;

	private:
		// ********************************************************************************
		/// <summary>
		/// ゲームクリア状態の処理
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		void GameStateClear(void);
		// ********************************************************************************
		/// <summary>
		/// ゲームオーバー状態の処理
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		void GameStateOver(void);
		// ********************************************************************************
		/// <summary>
		/// リスタート時の初期化
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		void ReStart(void);
		// ********************************************************************************
		/// <summary>
		/// プレイヤーへのダメージ処理
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		void DmgPlayer(void);
		// ********************************************************************************
		/// <summary>
		/// 敵へのダメージ処理
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		void DmgEnemy(void);
		// ********************************************************************************
		/// <summary>
		/// プレイヤーのターンにつなぐまでの処理
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		void RefreshPlayer(void);
		// ********************************************************************************
		/// <summary>
		/// ターンが変わった時の次のターンまでつなぐ処理
		/// </summary>
		/// <param name="turn">現在のターン</param>
		/// <created>いのうえ,2020/02/23</created>
		/// <changed>いのうえ,2020/02/23</changed>
		// ********************************************************************************
		void RefreshChangeTurn(const Turn& turn);
		// ********************************************************************************
		/// <summary>
		/// ゲームオーバーの監視
		/// </summary>
		/// <created>いのうえ,2020/02/23</created>
		/// <changed>いのうえ,2020/02/23</changed>
		// ********************************************************************************
		void CheckGameOver(void);
	};
}

