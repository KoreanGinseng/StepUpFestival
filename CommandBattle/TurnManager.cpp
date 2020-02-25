/*************************************************************************//*!

					@file	TurnManager.cpp
					@brief	ターン管理クラス

															@author	いのうえ
															@date	2020.02.15
*//**************************************************************************/

//INCLUDE
#include "TurnManager.h"

namespace DxLibPlus
{
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <returns>None</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	CTurnManager::CTurnManager(void) :
		m_Turn(TURN_PLAYER),
		m_PrevTurn(m_Turn),
		m_bChange(false)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <returns>None</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	CTurnManager::~CTurnManager(void)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// マネージャ取得
	/// </summary>
	/// <returns>マネージャ</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	CTurnManager & CTurnManager::GetTurnManager(void)
	{
		static CTurnManager manager;
		return manager;
	}
	// ********************************************************************************
	/// <summary>
	/// ターンの更新
	/// </summary>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	void CTurnManager::RefreshTurn(void)
	{
		//変更フラグのセット
		m_bChange = false;
		//前フレームから変更があった場合フラグを立てる
		if (m_Turn != m_PrevTurn)
		{
			m_bChange = true;
		}
		//更新
		m_PrevTurn = m_Turn;
	}
	// ********************************************************************************
	/// <summary>
	/// ターンのセット
	/// </summary>
	/// <param name="turn">ターン</param>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	void CTurnManager::SetTurn(const Turn & turn)
	{
		m_Turn = turn;
	}
	// ********************************************************************************
	/// <summary>
	/// ターンの取得
	/// </summary>
	/// <returns>現在のターン</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	Turn CTurnManager::GetTurn(void) const
	{
		return m_Turn;
	}
	// ********************************************************************************
	/// <summary>
	/// ターン変更フラグ取得
	/// </summary>
	/// <returns>ターン変更フラグ</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	bool CTurnManager::IsChanged(void) const
	{
		return m_bChange;
	}
}