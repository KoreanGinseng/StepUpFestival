#include "TextureManager.h"



CTextureManager::CTextureManager(void)
{
}


CTextureManager::~CTextureManager(void)
{
}

CTextureManager * CTextureManager::GetTexture(void)
{
	static CTextureManager obj;
	return &obj;
}

CTexture * CTextureManager::GetTexture(const std::string & str)
{
	return CTextureManager::GetTexture()->m_Resource[str];
}

bool CTextureManager::Load(const std::string& str)
{
	CTextureManager::GetTexture()->m_Resource[str] = new CTexture();
	CTextureManager::GetTexture()->m_Resource[str]->Load(str.c_str());
	return true;
}

void CTextureManager::Release(void)
{
	for (auto& itr : CTextureManager::GetTexture()->m_Resource)
	{
		itr.second->Release();
		delete itr.second;
		itr.second = nullptr;
	}
	CTextureManager::GetTexture()->m_Resource.clear();
}
