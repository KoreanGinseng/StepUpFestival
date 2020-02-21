/*************************************************************************//*!

					@file	GraphicsUtillities.cpp
					@brief	�`�惆�[�e�B���e�B�N���X

															@author	���̂���
															@date	2020.02.14
*//**************************************************************************/
#include "GraphicsUtillities.h"


namespace DxLibPlus
{
	// ********************************************************************************
	/// <summary>
	/// �E�B���h�E���[�h�E�t���X�N���[�����[�h�̕ύX���s��
	/// </summary>
	/// <param name="flag">�E�B���h�E���[�h�ŋN�����邩�̃t���O���</param>
	/// <returns>����(DX_CHANGESCREEN_OK)or���s</returns>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	int CGraphicsUtillities::ChangeWindowMode(const int & flag)
	{
		return DxLib::ChangeWindowMode(flag);
	}
	// ********************************************************************************
	/// <summary>
	/// �E�B���h�E�̃^�C�g����ύX����
	/// </summary>
	/// <param name="title">�^�C�g��������</param>
	/// <returns>����(0)�����s(-1)</returns>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	int CGraphicsUtillities::SetWindowTitle(const std::string & title)
	{
		return DxLib::SetMainWindowText(title.c_str());
	}
	// ********************************************************************************
	/// <summary>
	/// �E�B���h�E�̃A�C�R����ύX����
	/// </summary>
	/// <param name="id">�A�C�R��ID</param>
	/// <returns>����(0)�����s(-1)</returns>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	int CGraphicsUtillities::SetWindowIcon(const int & id)
	{
		return DxLib::SetWindowIconID(id);
	}
	// ********************************************************************************
	/// <summary>
	/// �E�B���h�E�̃T�C�Y��ύX����
	/// </summary>
	/// <param name="w">����</param>
	/// <param name="h">�c��</param>
	/// <returns>����(0)�����s(-1)</returns>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	int CGraphicsUtillities::SetWindowSize(const int & w, const int & h)
	{
		return DxLib::SetGraphMode(w, h, 16);
	}
	// ********************************************************************************
	/// <summary>
	/// �t�H���g�̃T�C�Y��ύX����
	/// </summary>
	/// <param name="size">�T�C�Y</param>
	/// <returns>����(0)�����s(-1)</returns>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	int CGraphicsUtillities::SetFontSize(const int & size)
	{
		return DxLib::SetFontSize(size);
	}
	// ********************************************************************************
	/// <summary>
	/// ��ʂ̃T�C�Y�����擾����
	/// </summary>
	/// <returns>��ʕ�</returns>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	int CGraphicsUtillities::GetTargetWidth(void)
	{
		int width;
		int height;
		int bit;
		DxLib::GetScreenState(&width, &height, &bit);
		return width;
	}
	// ********************************************************************************
	/// <summary>
	/// ��ʂ̃T�C�Y�c���擾����
	/// </summary>
	/// <returns>��ʍ���</returns>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	int CGraphicsUtillities::GetTargetHeight(void)
	{
		int width;
		int height;
		int bit;
		DxLib::GetScreenState(&width, &height, &bit);
		return height;
	}
	// ********************************************************************************
	/// <summary>
	/// �`���O���t�B�b�N�̈�̎w��
	/// </summary>
	/// <param name="screen">�ΏۂƂȂ�O���t�B�b�N�̈���w�肷��</param>
	/// <returns>����(0)�����s(-1)</returns>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	int CGraphicsUtillities::SetDrawScreen(const int & screen)
	{
		return DxLib::SetDrawScreen(screen);
	}
	// ********************************************************************************
	/// <summary>
	/// ��ʂɏ����ꂽ���̂��폜����
	/// </summary>
	/// <returns>����(0)�����s(-1)</returns>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	int CGraphicsUtillities::ClearDrawScreen(void)
	{
		return DxLib::ClearDrawScreen();
	}
	// ********************************************************************************
	/// <summary>
	/// ��ʗ��ɏ����ꂽ���̂�\�ɔ��f����
	/// </summary>
	/// <returns>����(0)�����s(-1)</returns>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	int CGraphicsUtillities::ScreenFlip(void)
	{
		return DxLib::ScreenFlip();
	}
}
