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
		return DxLib::SetWindowSize(w, h);
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
	int CGraphicsUtillities::GetTargetWidth(void)
	{
		int width;
		int height;
		int bit;
		DxLib::GetScreenState(&width, &height, &bit);
		return width;
	}
	int CGraphicsUtillities::GetTargetHeight(void)
	{
		int width;
		int height;
		int bit;
		DxLib::GetScreenState(&width, &height, &bit);
		return height;
	}
}
