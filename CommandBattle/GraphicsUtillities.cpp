/*************************************************************************//*!

					@file	GraphicsUtillities.cpp
					@brief	描画ユーティリティクラス

															@author	いのうえ
															@date	2020.02.14
*//**************************************************************************/
#include "GraphicsUtillities.h"


namespace DxLibPlus
{
	// ********************************************************************************
	/// <summary>
	/// ウィンドウモード・フルスクリーンモードの変更を行う
	/// </summary>
	/// <param name="flag">ウィンドウモードで起動するかのフラグ情報</param>
	/// <returns>成功(DX_CHANGESCREEN_OK)or失敗</returns>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	int CGraphicsUtillities::ChangeWindowMode(const int & flag)
	{
		return DxLib::ChangeWindowMode(flag);
	}
	// ********************************************************************************
	/// <summary>
	/// ウィンドウのタイトルを変更する
	/// </summary>
	/// <param name="title">タイトル文字列</param>
	/// <returns>成功(0)か失敗(-1)</returns>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	int CGraphicsUtillities::SetWindowTitle(const std::string & title)
	{
		return DxLib::SetMainWindowText(title.c_str());
	}
	// ********************************************************************************
	/// <summary>
	/// ウィンドウのアイコンを変更する
	/// </summary>
	/// <param name="id">アイコンID</param>
	/// <returns>成功(0)か失敗(-1)</returns>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	int CGraphicsUtillities::SetWindowIcon(const int & id)
	{
		return DxLib::SetWindowIconID(id);
	}
	// ********************************************************************************
	/// <summary>
	/// ウィンドウのサイズを変更する
	/// </summary>
	/// <param name="w">横幅</param>
	/// <param name="h">縦幅</param>
	/// <returns>成功(0)か失敗(-1)</returns>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	int CGraphicsUtillities::SetWindowSize(const int & w, const int & h)
	{
		return DxLib::SetGraphMode(w, h, 16);
	}
	// ********************************************************************************
	/// <summary>
	/// フォントのサイズを変更する
	/// </summary>
	/// <param name="size">サイズ</param>
	/// <returns>成功(0)か失敗(-1)</returns>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	int CGraphicsUtillities::SetFontSize(const int & size)
	{
		return DxLib::SetFontSize(size);
	}
	// ********************************************************************************
	/// <summary>
	/// 画面のサイズ幅を取得する
	/// </summary>
	/// <returns>画面幅</returns>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
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
	/// 画面のサイズ縦を取得する
	/// </summary>
	/// <returns>画面高さ</returns>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
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
	/// 描画先グラフィック領域の指定
	/// </summary>
	/// <param name="screen">対象となるグラフィック領域を指定する</param>
	/// <returns>成功(0)か失敗(-1)</returns>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	int CGraphicsUtillities::SetDrawScreen(const int & screen)
	{
		return DxLib::SetDrawScreen(screen);
	}
	// ********************************************************************************
	/// <summary>
	/// 画面に書かれたものを削除する
	/// </summary>
	/// <returns>成功(0)か失敗(-1)</returns>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	int CGraphicsUtillities::ClearDrawScreen(void)
	{
		return DxLib::ClearDrawScreen();
	}
	// ********************************************************************************
	/// <summary>
	/// 画面裏に書かれたものを表に反映する
	/// </summary>
	/// <returns>成功(0)か失敗(-1)</returns>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	int CGraphicsUtillities::ScreenFlip(void)
	{
		return DxLib::ScreenFlip();
	}
}
