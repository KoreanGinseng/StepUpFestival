#pragma once
#include "Chara.h"

namespace DxLibPlus
{
	class CPlayer : public CChara
	{
	private:
		enum CommandState {
			COMMAND_WAIT,
			COMMAND_ATTACK,
			COMMAND_SKILL,
		} m_State;
		int					m_Cursor;
		std::vector<Skill>	m_SkillList;
	public:
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		CPlayer(void);
		/*************************************************************************//*!
				@brief			デストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CPlayer(void);
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

