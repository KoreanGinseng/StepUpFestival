/*************************************************************************//*!

					@file	TurnManager.cpp
					@brief	�^�[���Ǘ��N���X

															@author	���̂���
															@date	2020.02.15
*//**************************************************************************/

//INCLUDE
#include "TurnManager.h"

namespace DxLibPlus
{
	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <returns>None</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	CTurnManager::CTurnManager(void) :
		m_Turn(TURN_PLAYER),
		m_PrevTurn(m_Turn),
		m_bChange(false)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <returns>None</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	CTurnManager::~CTurnManager(void)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// �}�l�[�W���擾
	/// </summary>
	/// <returns>�}�l�[�W��</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	CTurnManager & CTurnManager::GetTurnManager(void)
	{
		static CTurnManager manager;
		return manager;
	}
	// ********************************************************************************
	/// <summary>
	/// �^�[���̍X�V
	/// </summary>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	void CTurnManager::RefreshTurn(void)
	{
		//�ύX�t���O�̃Z�b�g
		m_bChange = false;
		//�O�t���[������ύX���������ꍇ�t���O�𗧂Ă�
		if (m_Turn != m_PrevTurn)
		{
			m_bChange = true;
		}
		//�X�V
		m_PrevTurn = m_Turn;
	}
	// ********************************************************************************
	/// <summary>
	/// �^�[���̃Z�b�g
	/// </summary>
	/// <param name="turn">�^�[��</param>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	void CTurnManager::SetTurn(const Turn & turn)
	{
		m_Turn = turn;
	}
	// ********************************************************************************
	/// <summary>
	/// �^�[���̎擾
	/// </summary>
	/// <returns>���݂̃^�[��</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	Turn CTurnManager::GetTurn(void) const
	{
		return m_Turn;
	}
	// ********************************************************************************
	/// <summary>
	/// �^�[���ύX�t���O�擾
	/// </summary>
	/// <returns>�^�[���ύX�t���O</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	bool CTurnManager::IsChanged(void) const
	{
		return m_bChange;
	}
}