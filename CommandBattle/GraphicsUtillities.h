/*************************************************************************//*!

					@file	GraphicsUtillities.h
					@brief	描画ユーティリティクラス

															@author	いのうえ
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
	@brief	描画ユーティリティクラス

	@author	いのうえ
	*//********************************/
	class CGraphicsUtillities
	{
	private:
		CGraphicsUtillities(void) = delete;
		~CGraphicsUtillities(void) = delete;
	public:
		/*************************************************************************//*!
				@brief			ウィンドウモード・フルスクリーンモードの変更を行う
				@param[in]		flag		ウィンドウモードで起動するかのフラグ情報

				@return			DX_CHANGESCREEN_OK		成功<br>
								DX_CHANGESCREEN_RETURN	失敗<br>
								DX_CHANGESCREEN_DEFAULT 失敗
		*//**************************************************************************/
		static int ChangeWindowMode(const int& flag);
		/*************************************************************************//*!
				@brief			ウィンドウのタイトルを変更する
				@param[in]		title		タイトル文字列

				@return			0			成功<br>
								-1			エラー発生
		*//**************************************************************************/
		static int SetWindowTitle(const std::string& title);
		/*************************************************************************//*!
				@brief			ウィンドウのアイコンを変更する
				@param[in]		id			アイコンID

				@return			0			成功<br>
								-1			エラー発生
		*//**************************************************************************/
		static int SetWindowIcon(const int& id);
		/*************************************************************************//*!
				@brief			ウィンドウのサイズを変更する
				@param[in]		w			横幅
				@param[in]		h			縦幅

				@return			0			成功<br>
								-1			エラー発生
		*//**************************************************************************/
		static int SetWindowSize(const int& w, const int& h);
		/*************************************************************************//*!
				@brief			フォントのサイズを変更する
				@param[in]		size		サイズ

				@return			0			成功<br>
								-1			エラー発生
		*//**************************************************************************/
		static int SetFontSize(const int& size);
	};
}