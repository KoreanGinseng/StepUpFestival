#include "EffectManager.h"

namespace DxLibPlus
{
	CEffectManager & CEffectManager::GetEffectManager(void)
	{
		static CEffectManager manager;
		return manager;
	}

	void CEffectManager::CreateEffect(const EffectType & type, Animation<10>* pAnim, const int & animCount)
	{

	}
	
	void CEffectManager::Start(void)
	{
	}
	
	void CEffectManager::SetEffect(const EffectType & type)
	{
	}
	
	void CEffectManager::Update(void)
	{

	}
}