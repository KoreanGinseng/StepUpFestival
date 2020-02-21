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
	/// �v���C���[�N���X
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
		/// @brief			�R���X�g���N�^
		/// </summary>
		/// <returns></returns>
		/// <created>���̂���,2020/02/19</created>
		/// <changed>���̂���,2020/02/19</changed>
		// ********************************************************************************
		CPlayer(void);
		// ********************************************************************************
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		/// <returns></returns>
		/// <created>���̂���,2020/02/19</created>
		/// <changed>���̂���,2020/02/19</changed>
		// ********************************************************************************
		virtual ~CPlayer(void);
		// ********************************************************************************
		/// <summary>
		/// �ǂݍ���
		/// </summary>
		/// <returns></returns>
		/// <created>���̂���,2020/02/19</created>
		/// <changed>���̂���,2020/02/19</changed>
		// ********************************************************************************
		virtual bool Load(void) override;
		// ********************************************************************************
		/// <summary>
		/// ������
		/// </summary>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		virtual void Initialize(void) override;
		// ********************************************************************************
		/// <summary>
		/// �X�V
		/// </summary>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		virtual void Update(void) override;
		// ********************************************************************************
		/// <summary>
		/// �`��
		/// </summary>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		virtual void Render(void) override;
		// ********************************************************************************
		/// <summary>
		/// �X�e�[�^�X�`��
		/// </summary>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		virtual void RenderStatus(void);
		// ********************************************************************************
		/// <summary>
		/// ���
		/// </summary>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		virtual void Release(void) override;

		void TurnStart(void);
	};
}

