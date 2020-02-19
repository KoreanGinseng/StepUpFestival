#pragma once

//INCLUDE
#include "Chara.h"
#include <iostream>
#include <fstream>
#include <codecvt>

namespace DxLibPlus
{
	// ********************************************************************************
	/// <summary>
	/// プレイヤークラス
	/// </summary>
	// ********************************************************************************
	class CPlayer : public CChara
	{
	private:
		enum CommandState {
			COMMAND_WAIT,
			COMMAND_ATTACK,
			COMMAND_SKILL,
			COMMAND_ITEM,
		} m_State;
		int					m_Cursor;
		float				m_AttackRate;
		std::vector<Skill>	m_SkillList;
	public:
		// ********************************************************************************
		/// <summary>
		/// @brief			コンストラクタ
		/// </summary>
		/// <returns></returns>
		/// <created>いのうえ,2020/02/19</created>
		/// <changed>いのうえ,2020/02/19</changed>
		// ********************************************************************************
		CPlayer(void);
		// ********************************************************************************
		/// <summary>
		/// デストラクタ
		/// </summary>
		/// <returns></returns>
		/// <created>いのうえ,2020/02/19</created>
		/// <changed>いのうえ,2020/02/19</changed>
		// ********************************************************************************
		virtual ~CPlayer(void);
		// ********************************************************************************
		/// <summary>
		/// 読み込み
		/// </summary>
		/// <returns></returns>
		/// <created>いのうえ,2020/02/19</created>
		/// <changed>いのうえ,2020/02/19</changed>
		// ********************************************************************************
		bool	Load(void);
		/*************************************************************************//*!
				@brief			初期化
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Initialize(void) override;
		/*************************************************************************//*!
				@brief			更新
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Update(void) override;
		/*************************************************************************//*!
				@brief			描画
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Render(void) override;
		/*************************************************************************//*!
				@brief			解放
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Release(void) override;
	};
}

