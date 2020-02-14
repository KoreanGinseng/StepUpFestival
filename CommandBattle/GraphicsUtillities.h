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
		static int ChangeWindowMode(const int& flag);
		static int SetWindowTitle(const std::string& title);
		static int SetWindowIcon(const int& id);
		static int SetWindowSize(const int& w, const int& h);
		//static int 
	};
}