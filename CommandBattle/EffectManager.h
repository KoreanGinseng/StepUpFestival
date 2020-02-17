#pragma once
#include	"Animation.h"
#include	"TextureManager.h"

namespace DxLibPlus
{
	enum EffectType {
		SKILL_FIRE,
		SKILL_ICE,
		SKILL_THUNDER,
	};

	class CEffectManager
	{
	private:
		std::unordered_map<EffectType, CAnimation<10>>	m_EffectList;
		CEffectManager(void) = default;
		~CEffectManager(void) = default;
	public:
		CEffectManager& GetEffectManager(void);
		void CreateEffect(const EffectType & type, Animation<10>* pAnim, const int& animCount);
		void Start(void);
		void SetEffect(const EffectType& type);
		void Update(void);
	};
}

