#include "TextureManager.h"


namespace DxLibPlus
{
	/*************************************************************************//*!
			@brief			コンストラクタ
			@param			None

			@return			None
	*//**************************************************************************/
	CTextureManager::CTextureManager(void) :
		m_GraphHandleList()
	{
	}
	/*************************************************************************//*!
			@brief			デストラクタ
			@param			None

			@return			None
	*//**************************************************************************/
	CTextureManager::~CTextureManager(void)
	{
		for (auto& itr : m_GraphHandleList)
		{
			DxLib::DeleteGraph(itr.second);
		}
	}
	/*************************************************************************//*!
			@brief			マネージャー呼び出し
			@param			None

			@return			マネージャー
	*//**************************************************************************/
	CTextureManager & CTextureManager::GetTextureManager(void)
	{
		static CTextureManager manager;
		return manager;
	}
	/*************************************************************************//*!
			@brief			画像ファイルのハンドル取得
			@param[in]		name		登録キー名

			@return			-1			エラー発生<br>
							-1以外		グラフィックのハンドル
	*//**************************************************************************/
	int CTextureManager::GetGraphHandle(const std::string & name)
	{
		return m_GraphHandleList[name];
	}
	/*************************************************************************//*!
			@brief			画像ファイルの読み込み
			@param[in]		name		登録キー名
			@param[in]		fileName	画像ファイル名

			@return			-1			エラー発生<br>
							-1以外		グラフィックのハンドル
	*//**************************************************************************/
	int CTextureManager::LoadGraph(const std::string & name, const std::string & fileName)
	{
		m_GraphHandleList[name] = DxLib::LoadGraph(fileName.c_str());
		return m_GraphHandleList[name];
	}
	/*************************************************************************//*!
			@brief			画像ファイルの横幅を取得する
			@param[in]		name		登録キー名

			@return			画像幅
	*//**************************************************************************/
	int CTextureManager::GetWidth(const std::string & name) const
	{
		int w, h, handle;
		handle = theTextureManager.GetGraphHandle(name);
		DxLib::GetGraphSize(handle, &w, &h);
		return w;
	}
	/*************************************************************************//*!
			@brief			画像ファイルの縦幅を取得する
			@param[in]		name		登録キー名

			@return			画像高さ
	*//**************************************************************************/
	int CTextureManager::GetHeight(const std::string & name) const
	{
		int w, h, handle;
		handle = theTextureManager.GetGraphHandle(name);
		DxLib::GetGraphSize(handle, &w, &h);
		return h;
	}
	/*************************************************************************//*!
			@brief			画像ファイルの一括読み込みする
			@param[in]		list		読み込みリスト
			@param[in]		cnt			リストの配列数

			@return			None
	*//**************************************************************************/
	void CTextureManager::LoadList(TexMngInfo * list, const int & cnt)
	{
		for (int i = 0; i < cnt; i++)
		{
			theTextureManager.LoadGraph(list[i].key, list[i].file);
		}
	}
}
