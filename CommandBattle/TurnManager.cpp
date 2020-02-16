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
		//�ύX�t���O�̃Z�b�g
		m_bChange = false;
		//�O�t���[������ύX���������ꍇ�t���O�𗧂Ă�
		if (m_Turn != m_PrevTurn)
		{
			m_bChange = true;
		}
		//�X�V
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