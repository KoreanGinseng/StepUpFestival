#include "EffectManager.h"
#include "GraphicsUtillities.h"
#include "GameDefine.h"

namespace DxLibPlus
{
	CEffectManager::CEffectManager(void) :
		m_EffectList(),
		m_PlayType(SKILL_FIRE)
	{
	}

	CEffectManager::~CEffectManager(void)
	{
		Release();
	}

	CEffectManager & CEffectManager::GetEffectManager(void)
	{
		static CEffectManager manager;
		return manager;
	}

	void CEffectManager::CreateEffect(const EffectType & type, Animation<10>* pAnim, const int & animCount)
	{
		m_EffectList[type].Create(pAnim, animCount);
	}
	
	void CEffectManager::Start(const EffectType & type)
	{
		m_EffectList[type].SetShow(true);
		m_EffectList[type].ChangeMotion(0);
		m_PlayType = type;
	}
	
	void CEffectManager::Update(void)
	{
		for (auto& itr : m_EffectList)
		{
			if (!itr.second.IsShow())
			{
				continue;
			}
			itr.second.AddTimer();
			if (itr.second.IsEndMotion())
			{
				itr.second.SetShow(false);
			}
		}
	}
	
	void CEffectManager::Render(void)
	{
		if (!m_EffectList[m_PlayType].IsShow())
		{
			return;
		}
		std::string key;
		switch (m_PlayType)
		{
		case SKILL_FIRE:
			key = TexFile[TEXKEY_EFFECT_FIRE].key;
			break;
		case SKILL_ICE:
			key = TexFile[TEXKEY_EFFECT_ICE].key;
			break;
		case SKILL_SLASH:
			key = TexFile[TEXKEY_EFFECT_SLASH].key;
			break;
		case SKILL_THUNDER:
			key = TexFile[TEXKEY_EFFECT_THUNDER].key;
			break;
		}
		int graphHandle = theTextureManager.GetGraphHandle(key);
		float x = (CGraphicsUtillities::GetTargetWidth() - 192) * 0.5f;
		Rectangle rect = m_EffectList[m_PlayType].GetSrcRect();
		DxLib::DrawRectGraph(static_cast<int>(x), PlayerRectW, rect.left, rect.top, rect.GetWidth(), rect.GetHeight(), graphHandle, true);
	}

	void CEffectManager::Release(void)
	{
		for (auto& itr : m_EffectList)
		{
			itr.second.Release();
		}
		m_EffectList.clear();
	}
}