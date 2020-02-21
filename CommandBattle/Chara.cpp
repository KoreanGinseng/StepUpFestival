#include "Chara.h"

namespace DxLibPlus
{
	CChara::CChara(void) :
		CGameAppBase(),
		m_AttackRate(1.0f),
		m_bDead(false),
		m_DamageWait(0),
		m_OffsetHp(0)
	{
		m_Status.hp = 0;
		m_Status.attack = 0;
	}

	CChara::~CChara(void)
	{
	}

	bool CChara::Load(void)
	{
		return true;
	}

	void CChara::Release(void)
	{
	}

	void CChara::Dmg(const int & dmg)
	{
		m_Status.hp -= dmg;
		m_DamageWait = 60;
		if (m_Status.hp <= 0)
		{
			m_Status.hp = 0;
			m_bDead = true;
		}
	}

	int CChara::GetAttack(void) const
	{
		return static_cast<int>(m_Status.attack * m_AttackRate * (CDxLibUtillities::Random(8, 12) * 0.1f));
	}

	int CChara::GetHp(void) const
	{
		return m_Status.hp;
	}
	
	bool CChara::IsDead(void) const
	{
		return m_bDead;
	}

	int CChara::GetDamageWait(void) const
	{
		return m_DamageWait;
	}

	void CChara::RefreshDmg(void)
	{
		if (--m_DamageWait < 0)
		{
			m_DamageWait = 0;
		}
	}
}
