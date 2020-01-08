#pragma once
#include	"DxLibPlus.h"
#include	<unordered_map>

class CTextureManager
{
private:
	std::unordered_map<std::string, CTexture*> m_Resource;		//! データ
	CTextureManager(void);
	~CTextureManager(void);
public:
	static CTextureManager* GetTexture(void);					//! マネージャー呼び出し
	static CTexture* GetTexture(const std::string& str);		//! 画像取得
	static bool Load(const std::string& str);					//! 読込
	static void Release(void);									//! 解放
};

