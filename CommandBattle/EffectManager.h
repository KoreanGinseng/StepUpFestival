#pragma once
#include	"Animation.h"
#include	"TextureManager.h"

namespace DxLibPlus
{
	enum EffectType {
		SKILL_FIRE,
		SKILL_ICE,
		SKILL_THUNDER,
		SKILL_SLASH,

		SKILL_COUNT,
	};

	class CEffectManager
	{
	private:
		std::unordered_map<EffectType, CAnimation<10>>	m_EffectList;
		EffectType										m_PlayType;
		CEffectManager(void);
		~CEffectManager(void);
	public:
		static CEffectManager& GetEffectManager(void);
		void CreateEffect(const EffectType & type, Animation<10>* pAnim, const int& animCount);
		void Start(const EffectType & type);
		void Update(void);
		void Render(void);
		void Release(void);
	};
#define theEffectManager CEffectManager::GetEffectManager()
}

