/*************************************************************************//*!

					@file	GraphicsUtillities.h
					@brief	�`�惆�[�e�B���e�B�N���X

															@author	���̂���
															@date	2020.02.14
*//**************************************************************************/

//ONCE
#pragma once

//INCLUDE
#include	"DxLib.h"
#include	<string>

namespace DxLibPlus
{
	/*******************************//*!
	@brief	�`�惆�[�e�B���e�B�N���X

	@author	���̂���
	*//********************************/
	class CGraphicsUtillities
	{
	private:
		CGraphicsUtillities(void) = delete;
		~CGraphicsUtillities(void) = delete;
	public:
		/*************************************************************************//*!
				@brief			�E�B���h�E���[�h�E�t���X�N���[�����[�h�̕ύX���s��
				@param[in]		flag		�E�B���h�E���[�h�ŋN�����邩�̃t���O���

				@return			DX_CHANGESCREEN_OK		����<br>
								DX_CHANGESCREEN_RETURN	���s<br>
								DX_CHANGESCREEN_DEFAULT ���s
		*//**************************************************************************/
		static int ChangeWindowMode(const int& flag);
		/*************************************************************************//*!
				@brief			�E�B���h�E�̃^�C�g����ύX����
				@param[in]		title		�^�C�g��������

				@return			0			����<br>
								-1			�G���[����
		*//**************************************************************************/
		static int SetWindowTitle(const std::string& title);
		/*************************************************************************//*!
				@brief			�E�B���h�E�̃A�C�R����ύX����
				@param[in]		id			�A�C�R��ID

				@return			0			����<br>
								-1			�G���[����
		*//**************************************************************************/
		static int SetWindowIcon(const int& id);
		/*************************************************************************//*!
				@brief			�E�B���h�E�̃T�C�Y��ύX����
				@param[in]		w			����
				@param[in]		h			�c��

				@return			0			����<br>
								-1			�G���[����
		*//**************************************************************************/
		static int SetWindowSize(const int& w, const int& h);
		/*************************************************************************//*!
				@brief			�t�H���g�̃T�C�Y��ύX����
				@param[in]		size		�T�C�Y

				@return			0			����<br>
								-1			�G���[����
		*//**************************************************************************/
		static int SetFontSize(const int& size);
	};
}