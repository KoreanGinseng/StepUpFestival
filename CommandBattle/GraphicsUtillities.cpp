/*************************************************************************//*!

					@file	GraphicsUtillities.cpp
					@brief	�`�惆�[�e�B���e�B�N���X

															@author	���̂���
															@date	2020.02.14
*//**************************************************************************/
#include "GraphicsUtillities.h"


namespace DxLibPlus
{
	/*************************************************************************//*!
			@brief			�E�B���h�E���[�h�E�t���X�N���[�����[�h�̕ύX���s��
			@param[in]		flag		�E�B���h�E���[�h�ŋN�����邩�̃t���O���

			@return			DX_CHANGESCREEN_OK		����<br>
							DX_CHANGESCREEN_RETURN	���s<br>
							DX_CHANGESCREEN_DEFAULT ���s
	*//**************************************************************************/
	int CGraphicsUtillities::ChangeWindowMode(const int & flag)
	{
		return DxLib::ChangeWindowMode(flag);
	}
	/*************************************************************************//*!
			@brief			�E�B���h�E�̃^�C�g����ύX����
			@param[in]		title		�^�C�g��������

			@return			0			����<br>
							-1			�G���[����
	*//**************************************************************************/
	int CGraphicsUtillities::SetWindowTitle(const std::string & title)
	{
		return DxLib::SetMainWindowText(title.c_str());
	}
	/*************************************************************************//*!
			@brief			�E�B���h�E�̃A�C�R����ύX����
			@param[in]		id			�A�C�R��ID

			@return			0			����<br>
							-1			�G���[����
	*//**************************************************************************/
	int CGraphicsUtillities::SetWindowIcon(const int & id)
	{
		return DxLib::SetWindowIconID(id);
	}
	/*************************************************************************//*!
			@brief			�E�B���h�E�̃T�C�Y��ύX����
			@param[in]		w			����
			@param[in]		h			�c��

			@return			0			����<br>
							-1			�G���[����
	*//**************************************************************************/
	int CGraphicsUtillities::SetWindowSize(const int & w, const int & h)
	{
		return DxLib::SetGraphMode(w, h, 16);
	}
	/*************************************************************************//*!
			@brief			�t�H���g�̃T�C�Y��ύX����
			@param[in]		size		�T�C�Y

			@return			0			����<br>
							-1			�G���[����
	*//**************************************************************************/
	int CGraphicsUtillities::SetFontSize(const int & size)
	{
		return DxLib::SetFontSize(size);
	}
	/*************************************************************************//*!
			@brief			��ʂ̃T�C�Y�����擾����
			@param			None

			@return			��ʕ�
	*//**************************************************************************/
	int CGraphicsUtillities::GetTargetWidth(void)
	{
		int width;
		int height;
		int bit;
		DxLib::GetScreenState(&width, &height, &bit);
		return width;
	}
	/*************************************************************************//*!
			@brief			��ʂ̃T�C�Y�c���擾����
			@param			None

			@return			��ʍ���
	*//**************************************************************************/
	int CGraphicsUtillities::GetTargetHeight(void)
	{
		int width;
		int height;
		int bit;
		DxLib::GetScreenState(&width, &height, &bit);
		return height;
	}
	/*************************************************************************//*!
			@brief			�`���O���t�B�b�N�̈�̎w��
			@param[in]		screen		�ΏۂƂȂ�O���t�B�b�N�̈���w�肷��

			@return			0			����<br>
							-1			�G���[����
	*//**************************************************************************/
	int CGraphicsUtillities::SetDrawScreen(const int & screen)
	{
		return DxLib::SetDrawScreen(screen);
	}
	/*************************************************************************//*!
			@brief			��ʂɏ����ꂽ���̂��폜����
			@param			None

			@return			0			����<br>
							-1			�G���[����
	*//**************************************************************************/
	int CGraphicsUtillities::ClearDrawScreen(void)
	{
		return DxLib::ClearDrawScreen();
	}
	/*************************************************************************//*!
			@brief			��ʗ��ɏ����ꂽ���̂�\�ɔ��f����
			@param[in]		size		�T�C�Y

			@return			0			����<br>
							-1			�G���[����
	*//**************************************************************************/
	int CGraphicsUtillities::ScreenFlip(void)
	{
		return DxLib::ScreenFlip();
	}
}
