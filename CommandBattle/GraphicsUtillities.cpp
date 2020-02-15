/*************************************************************************//*!

					@file	GraphicsUtillities.cpp
					@brief	描画ユーティリティクラス

															@author	いのうえ
															@date	2020.02.14
*//**************************************************************************/
#include "GraphicsUtillities.h"


namespace DxLibPlus
{
	/*************************************************************************//*!
			@brief			ウィンドウモード・フルスクリーンモードの変更を行う
			@param[in]		flag		ウィンドウモードで起動するかのフラグ情報

			@return			DX_CHANGESCREEN_OK		成功<br>
							DX_CHANGESCREEN_RETURN	失敗<br>
							DX_CHANGESCREEN_DEFAULT 失敗
	*//**************************************************************************/
	int CGraphicsUtillities::ChangeWindowMode(const int & flag)
	{
		return DxLib::ChangeWindowMode(flag);
	}
	/*************************************************************************//*!
			@brief			ウィンドウのタイトルを変更する
			@param[in]		title		タイトル文字列

			@return			0			成功<br>
							-1			エラー発生
	*//**************************************************************************/
	int CGraphicsUtillities::SetWindowTitle(const std::string & title)
	{
		return DxLib::SetMainWindowText(title.c_str());
	}
	/*************************************************************************//*!
			@brief			ウィンドウのアイコンを変更する
			@param[in]		id			アイコンID

			@return			0			成功<br>
							-1			エラー発生
	*//**************************************************************************/
	int CGraphicsUtillities::SetWindowIcon(const int & id)
	{
		return DxLib::SetWindowIconID(id);
	}
	/*************************************************************************//*!
			@brief			ウィンドウのサイズを変更する
			@param[in]		w			横幅
			@param[in]		h			縦幅

			@return			0			成功<br>
							-1			エラー発生
	*//**************************************************************************/
	int CGraphicsUtillities::SetWindowSize(const int & w, const int & h)
	{
		return DxLib::SetGraphMode(w, h, 16);
	}
	/*************************************************************************//*!
			@brief			フォントのサイズを変更する
			@param[in]		size		サイズ

			@return			0			成功<br>
							-1			エラー発生
	*//**************************************************************************/
	int CGraphicsUtillities::SetFontSize(const int & size)
	{
		return DxLib::SetFontSize(size);
	}
	/*************************************************************************//*!
			@brief			画面のサイズ幅を取得する
			@param			None

			@return			画面幅
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
			@brief			画面のサイズ縦を取得する
			@param			None

			@return			画面高さ
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
			@brief			描画先グラフィック領域の指定
			@param[in]		screen		対象となるグラフィック領域を指定する

			@return			0			成功<br>
							-1			エラー発生
	*//**************************************************************************/
	int CGraphicsUtillities::SetDrawScreen(const int & screen)
	{
		return DxLib::SetDrawScreen(screen);
	}
	/*************************************************************************//*!
			@brief			画面に書かれたものを削除する
			@param			None

			@return			0			成功<br>
							-1			エラー発生
	*//**************************************************************************/
	int CGraphicsUtillities::ClearDrawScreen(void)
	{
		return DxLib::ClearDrawScreen();
	}
	/*************************************************************************//*!
			@brief			画面裏に書かれたものを表に反映する
			@param[in]		size		サイズ

			@return			0			成功<br>
							-1			エラー発生
	*//**************************************************************************/
	int CGraphicsUtillities::ScreenFlip(void)
	{
		return DxLib::ScreenFlip();
	}
}
