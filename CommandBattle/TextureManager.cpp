/*************************************************************************//*!

					@file	TextureManager.cpp
					@brief	テクスチャ管理クラス

															@author	いのうえ
															@date	2020.02.15
*//**************************************************************************/

//INCLUDE
#include "TextureManager.h"


namespace DxLibPlus
{
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <returns>None</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	CTextureManager::CTextureManager(void) :
		m_GraphHandleList()
	{
	}
	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <returns>None</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	CTextureManager::~CTextureManager(void)
	{
		for (auto& itr : m_GraphHandleList)
		{
			DxLib::DeleteGraph(itr.second);
		}
	}
	// ********************************************************************************
	/// <summary>
	/// マネージャー呼び出し
	/// </summary>
	/// <returns>マネージャー</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	CTextureManager & CTextureManager::GetTextureManager(void)
	{
		static CTextureManager manager;
		return manager;
	}
	// ********************************************************************************
	/// <summary>
	/// 画像ファイルのハンドルを取得する
	/// </summary>
	/// <param name="name">登録キー名</param>
	/// <returns>グラフィックのハンドル</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	int CTextureManager::GetGraphHandle(const std::string & name)
	{
		return m_GraphHandleList[name];
	}
	// ********************************************************************************
	/// <summary>
	/// 画像ファイルの読み込み
	/// </summary>
	/// <param name="name">登録キー名</param>
	/// <param name="fileName">画像ファイル名</param>
	/// <returns>グラフィックのハンドル</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	int CTextureManager::LoadGraph(const std::string & name, const std::string & fileName)
	{
		m_GraphHandleList[name] = DxLib::LoadGraph(fileName.c_str());
		return m_GraphHandleList[name];
	}
	// ********************************************************************************
	/// <summary>
	/// 画像ファイルの横幅を取得する
	/// </summary>
	/// <param name="name">登録キー名</param>
	/// <returns>画像幅</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	int CTextureManager::GetWidth(const std::string & name) const
	{
		int w, h, handle;
		handle = theTextureManager.GetGraphHandle(name);
		DxLib::GetGraphSize(handle, &w, &h);
		return w;
	}
	// ********************************************************************************
	/// <summary>
	/// 画像ファイルの縦幅を取得する
	/// </summary>
	/// <param name="name">登録キー名</param>
	/// <returns>画像高さ</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	int CTextureManager::GetHeight(const std::string & name) const
	{
		int w, h, handle;
		handle = theTextureManager.GetGraphHandle(name);
		DxLib::GetGraphSize(handle, &w, &h);
		return h;
	}
	// ********************************************************************************
	/// <summary>
	/// 画像ファイルの一括読み込みする
	/// </summary>
	/// <param name="list">読み込みリスト</param>
	/// <param name="cnt">リストの配列数</param>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	void CTextureManager::LoadList(TexMngInfo * list, const int & cnt)
	{
		for (int i = 0; i < cnt; i++)
		{
			theTextureManager.LoadGraph(list[i].key, list[i].file);
		}
	}
}
