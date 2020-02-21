#pragma once

//INCLUDE
#include "Chara.h"
#include <iostream>
#include <fstream>
#include <codecvt>

namespace DxLibPlus
{
	constexpr int LineMax = (CommandRectH / (FontSize + FontMargin * 2)) + ((CommandRectH % (FontSize + FontMargin * 2)) ? 1 : 0);
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
			COMMAND_EXIT,
		} m_State;
		int					m_Cursor;
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
		virtual bool Load(void) override;
		// ********************************************************************************
		/// <summary>
		/// 初期化
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		virtual void Initialize(void) override;
		// ********************************************************************************
		/// <summary>
		/// 更新
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		virtual void Update(void) override;
		// ********************************************************************************
		/// <summary>
		/// 描画
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		virtual void Render(void) override;
		// ********************************************************************************
		/// <summary>
		/// ステータス描画
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		virtual void RenderStatus(void);
		// ********************************************************************************
		/// <summary>
		/// 解放
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		virtual void Release(void) override;

		void TurnStart(void);
	};
}

