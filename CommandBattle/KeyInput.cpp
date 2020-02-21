/*************************************************************************//*!

					@file	KeyInput.cpp
					@brief	キー入力クラス

															@author	いのうえ
															@date	2020.02.21
*//**************************************************************************/

//INCLUDE
#include "KeyInput.h"

namespace DxLibPlus
{
	// ********************************************************************************
	/// <summary>
	/// キーマネージャー取得
	/// </summary>
	/// <returns>キーマネージャー</returns>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	CKeyInput & CKeyInput::GetKeyInput(void)
	{
		static CKeyInput obj;
		return obj;
	}
	// ********************************************************************************
	/// <summary>
	/// キーの更新
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CKeyInput::RefreshKey(void)
	{
		for (int i = 0; i < 256; i++)
		{
			m_Prev[i] = m_Now[i];
		}
		for (int i = 0; i < 256; i++)
		{
			m_Now[i] = DxLib::CheckHitKey(i);
		}
	}
	// ********************************************************************************
	/// <summary>
	/// 押した瞬間のフラグ取得
	/// </summary>
	/// <param name="keycode">キーコード</param>
	/// <returns>押された瞬間のフラグ</returns>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	bool CKeyInput::IsKeyPush(const int & keycode) const
	{
		return (!m_Prev[keycode] && m_Now[keycode]);
	}
	// ********************************************************************************
	/// <summary>
	/// 押している間のフラグ取得
	/// </summary>
	/// <param name="keycode">キーコード</param>
	/// <returns>押している間のフラグ</returns>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	bool CKeyInput::IsKeyHold(const int & keycode) const
	{
		return (m_Now[keycode]);
	}
	// ********************************************************************************
	/// <summary>
	/// キーから放した瞬間のフラグ取得
	/// </summary>
	/// <param name="keycode">キーコード</param>
	/// <returns>キーから放した瞬間のフラグ</returns>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	bool CKeyInput::IsKeyPull(const int & keycode) const
	{
		return (m_Prev[keycode] && !m_Now[keycode]);
	}
}
