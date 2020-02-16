#include "Chara.h"

namespace DxLibPlus
{
	CChara::CChara(void) :
		CGameAppBase()
	{
		m_Status.hp = 0;
		m_Status.attack = 0;
	}

	CChara::~CChara(void)
	{
	}

	void CChara::Release(void)
	{
	}

	void CChara::Dmg(const int & dmg)
	{
		m_Status.hp -= dmg;
	}

	int CChara::GetAttack(void) const
	{
		return m_Status.attack;
	}

	int CChara::GetHp(void) const
	{
		return m_Status.hp;
	}
}
