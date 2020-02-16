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
				@brief			�R���X�g���N�^
				@param			None

				@return			None
		*//**************************************************************************/
		CPlayer(void);
		/*************************************************************************//*!
				@brief			�f�X�g���N�^
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CPlayer(void);
		bool	Load(void);
		/*************************************************************************//*!
				@brief			������
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Initialize(void) override;
		/*************************************************************************//*!
				@brief			�X�V
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Update(void) override;
		/*************************************************************************//*!
				@brief			�`��
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Render(void) override;
		/*************************************************************************//*!
				@brief			���
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Release(void) override;
	};
}

