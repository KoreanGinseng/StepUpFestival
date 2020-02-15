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
		return DxLib::SetWindowSize(w, h);
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
}
