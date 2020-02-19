/*************************************************************************//*!

					@file	DxLibUtillities.h
					@brief	DxLibユーティリティクラス

															@author	いのうえ
															@date	2020.02.14
*//**************************************************************************/

//INCLUDE
#include "DxLibUtillities.h"


namespace DxLibPlus
{
	/*************************************************************************//*!
			@brief			ライブラリの初期化
			@param			None

			@return			0			成功<br>
							-1			エラー発生
	*//**************************************************************************/
	int CDxLibUtillities::DxLibInit(void)
	{
		return DxLib::DxLib_Init();
	}
	/*************************************************************************//*!
			@brief			ライブラリ使用の終了
			@param			None

			@return			0			成功<br>
							-1			エラー発生
	*//**************************************************************************/
	int CDxLibUtillities::DxLibEnd(void)
	{
		return DxLib::DxLib_End();
	}
	/*************************************************************************//*!
			@brief			ウィンドウのメッセージを処理する
			@param			None

			@return			0			成功<br>
							-1			エラー発生・若しくはウィンドウが閉じられた
	*//**************************************************************************/
	int CDxLibUtillities::ProcessMessage(void)
	{
		return DxLib::ProcessMessage();
	}
	/*************************************************************************//*!
			@brief			指定の時間だけ処理を止める
			@param[in]		t			止める時間(ミリ秒単位)

			@return			0			成功<br>
							-1			エラー発生
	*//**************************************************************************/
	int CDxLibUtillities::WaitTimer(const int & t)
	{
		return DxLib::WaitTimer(t);
	}
	/*************************************************************************//*!
			@brief			乱数を取得する
			@param[in]		max			取得する乱数の最大値

			@return			0~最大値までの乱数
	*//**************************************************************************/
	int CDxLibUtillities::Random(const int & max)
	{
		return DxLib::GetRand(max);
	}
	/*************************************************************************//*!
			@brief			乱数を取得する
			@param[in]		min			取得する乱数の最小値
			@param[in]		max			取得する乱数の最大値

			@return			最小値~最大値までの乱数
	*//**************************************************************************/
	int CDxLibUtillities::Random(const int & min, const int & max)
	{
		return DxLib::GetRand(max - min) + min;
	}
	/*************************************************************************//*!
			@brief			乱数を取得する
			@param			None

			@return			0.0f~1.0fまでの乱数(下二桁まで)
	*//**************************************************************************/
	float CDxLibUtillities::RandomFloat(void)
	{
		return static_cast<float>(DxLib::GetRand(100)) * 0.01f;
	}
	/*************************************************************************//*!
			@brief			乱数の初期値を設定する
			@param[in]		seed		乱数の初期値

			@return			0			成功<br>
							-1			エラー発生
	*//**************************************************************************/
	int CDxLibUtillities::SetRandom(const int & seed)
	{
		return DxLib::SRand(seed);
	}
	// ********************************************************************************
	/// <summary>
	/// wstringをstringへ変換
	/// </summary>
	/// <param name="oWString">ワイド文字列</param>
	/// <returns>マルチバイト文字列</returns>
	/// <created>いのうえ,2020/02/19</created>
	/// <changed>いのうえ,2020/02/19</changed>
	// ********************************************************************************
	std::string CDxLibUtillities::WStringToString(std::wstring oWString)
	{
		// wstring → SJIS
		int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str()
			, -1, (char *)NULL, 0, NULL, NULL);

		// バッファの取得
		CHAR* cpMultiByte = new CHAR[iBufferSize];

		// wstring → SJIS
		WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, cpMultiByte
			, iBufferSize, NULL, NULL);

		// stringの生成
		std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);

		// バッファの破棄
		delete[] cpMultiByte;

		// 変換結果を返す
		return(oRet);
	}
}