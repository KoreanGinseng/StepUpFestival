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
	// ********************************************************************************
	/// <summary>
	/// ライブラリの初期化
	/// </summary>
	/// <returns>成功(0)かエラー(-1)</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	int CDxLibUtillities::DxLibInit(void)
	{
		return DxLib::DxLib_Init();
	}
	// ********************************************************************************
	/// <summary>
	/// ライブラリ使用の終了
	/// </summary>
	/// <returns>成功(0)かエラー(-1)</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	int CDxLibUtillities::DxLibEnd(void)
	{
		return DxLib::DxLib_End();
	}
	// ********************************************************************************
	/// <summary>
	/// ウィンドウのメッセージを処理する
	/// </summary>
	/// <returns>成功(0)かエラー(-1)</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	int CDxLibUtillities::ProcessMessage(void)
	{
		return DxLib::ProcessMessage();
	}
	// ********************************************************************************
	/// <summary>
	/// 指定の時間だけ処理を止める
	/// </summary>
	/// <param name="t">止める時間(ミリ秒単位)</param>
	/// <returns>成功(0)かエラー(-1)</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	int CDxLibUtillities::WaitTimer(const int & t)
	{
		return DxLib::WaitTimer(t);
	}
	// ********************************************************************************
	/// <summary>
	/// 乱数を取得する
	/// </summary>
	/// <param name="max">取得する乱数の最大値</param>
	/// <returns>0~最大値までの乱数</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	int CDxLibUtillities::Random(const int & max)
	{
		return DxLib::GetRand(max);
	}
	// ********************************************************************************
	/// <summary>
	/// 乱数を取得する
	/// </summary>
	/// <param name="min">取得する乱数の最小値</param>
	/// <param name="max">取得する乱数の最大値</param>
	/// <returns>最小値~最大値までの乱数</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	int CDxLibUtillities::Random(const int & min, const int & max)
	{
		return DxLib::GetRand(max - min) + min;
	}
	// ********************************************************************************
	/// <summary>
	/// 乱数を取得する
	/// </summary>
	/// <returns>0.0f~1.0fまでの乱数(下二桁まで)</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	float CDxLibUtillities::RandomFloat(void)
	{
		return static_cast<float>(DxLib::GetRand(100)) * 0.01f;
	}
	// ********************************************************************************
	/// <summary>
	/// 乱数の初期値を設定する
	/// </summary>
	/// <param name="seed">乱数の初期値</param>
	/// <returns>成功(0)かエラー(-1)</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
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