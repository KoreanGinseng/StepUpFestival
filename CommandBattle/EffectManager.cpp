#include "EffectManager.h"



CEffectManager::CEffectManager(void)
{
}


CEffectManager::~CEffectManager(void)
{
}

CEffectManager * CEffectManager::GetEffect(void)
{
	static CEffectManager obj;
	return &obj;
}

CEffect * CEffectManager::GetEffect(const std::string & str)
{
	CEffect* re;
	int c = CEffectManager::GetEffect()->m_Resource[str].size();
	bool bFind = false;
	for (int i = 0; i < c; i++)
	{
		re = CEffectManager::GetEffect()->m_Resource[str][i];
		if (re->IsShow())
		{
			continue;
		}
		bFind = true;
		break;
	}
	if (!bFind)
	{
		CEffectManager::GetEffect()->m_Resource[str].push_back(NEW CEffect());
		CEffectManager::GetEffect()->m_Resource[str][c]->Load(str.c_str());
		re = CEffectManager::GetEffect()->m_Resource[str][c];
	}
	return re;
}

void CEffectManager::Start(const std::string & str, const Vector2<float> & pos)
{
	CEffectManager::GetEffect(str)->Start(pos);
}

void CEffectManager::Start(const std::string & str, const float & x, const float & y)
{
	CEffectManager::Start(str, Vector2Get<float>(x, y));
}

bool CEffectManager::Load(const std::string& str)
{
	for (int i = 0; i < DefEffectPool; i++)
	{
		CEffectManager::GetEffect()->m_Resource[str].push_back(NEW CEffect());
		if (!CEffectManager::GetEffect()->m_Resource[str][i]->Load(str))
		{
			return false;
		}
	}
	return true;
}

void CEffectManager::Update(void)
{
	for (auto& itr : CEffectManager::GetEffect()->m_Resource)
	{
		int c = itr.second.size();
		for (int i = 0; i < c; i++)
		{
			itr.second[i]->Update();
		}
	}
}

void CEffectManager::Render(void)
{
	for (auto& itr : CEffectManager::GetEffect()->m_Resource)
	{
		int c = itr.second.size();
		for (int i = 0; i < c; i++)
		{
			itr.second[i]->Render();
		}
	}
}

void CEffectManager::Release(void)
{
	for (auto& itr : CEffectManager::GetEffect()->m_Resource)
	{
		int c = itr.second.size();
		for (int i = 0; i < c; i++)
		{
			itr.second[i]->Release();
			delete itr.second[i];
			itr.second[i] = nullptr;
		}
		itr.second.clear();
	}
	CEffectManager::GetEffect()->m_Resource.clear();
}
