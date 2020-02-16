#include "TurnManager.h"

namespace DxLibPlus
{
	CTurnManager::CTurnManager(void) :
		m_Turn(TURN_PLAYER),
		m_PrevTurn(m_Turn),
		m_bChange(false)
	{
	}

	CTurnManager::~CTurnManager(void)
	{
	}

	CTurnManager & CTurnManager::GetTurnManager(void)
	{
		static CTurnManager manager;
		return manager;
	}

	void CTurnManager::RefreshTurn(void)
	{
		//変更フラグのセット
		m_bChange = false;
		//前フレームから変更があった場合フラグを立てる
		if (m_Turn != m_PrevTurn)
		{
			m_bChange = true;
		}
		//更新
		m_PrevTurn = m_Turn;
	}

	void CTurnManager::SetTurn(const Turn & turn)
	{
		m_Turn = turn;
	}

	Turn CTurnManager::GetTurn(void) const
	{
		return m_Turn;
	}
	bool CTurnManager::IsChanged(void) const
	{
		return m_bChange;
	}
}