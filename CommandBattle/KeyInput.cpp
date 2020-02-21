/*************************************************************************//*!

					@file	KeyInput.cpp
					@brief	�L�[���̓N���X

															@author	���̂���
															@date	2020.02.21
*//**************************************************************************/

//INCLUDE
#include "KeyInput.h"

namespace DxLibPlus
{
	// ********************************************************************************
	/// <summary>
	/// �L�[�}�l�[�W���[�擾
	/// </summary>
	/// <returns>�L�[�}�l�[�W���[</returns>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	CKeyInput & CKeyInput::GetKeyInput(void)
	{
		static CKeyInput obj;
		return obj;
	}
	// ********************************************************************************
	/// <summary>
	/// �L�[�̍X�V
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
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
	/// �������u�Ԃ̃t���O�擾
	/// </summary>
	/// <param name="keycode">�L�[�R�[�h</param>
	/// <returns>�����ꂽ�u�Ԃ̃t���O</returns>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	bool CKeyInput::IsKeyPush(const int & keycode) const
	{
		return (!m_Prev[keycode] && m_Now[keycode]);
	}
	// ********************************************************************************
	/// <summary>
	/// �����Ă���Ԃ̃t���O�擾
	/// </summary>
	/// <param name="keycode">�L�[�R�[�h</param>
	/// <returns>�����Ă���Ԃ̃t���O</returns>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	bool CKeyInput::IsKeyHold(const int & keycode) const
	{
		return (m_Now[keycode]);
	}
	// ********************************************************************************
	/// <summary>
	/// �L�[����������u�Ԃ̃t���O�擾
	/// </summary>
	/// <param name="keycode">�L�[�R�[�h</param>
	/// <returns>�L�[����������u�Ԃ̃t���O</returns>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	bool CKeyInput::IsKeyPull(const int & keycode) const
	{
		return (m_Prev[keycode] && !m_Now[keycode]);
	}
}
