#pragma once

namespace DxLibPlus
{
	enum Turn {
		TURN_PLAYER,
		TURN_ENEMY,
	};
	class CTurnManager
	{
	private:
		Turn		m_Turn;
		Turn		m_PrevTurn;
		bool		m_bChange;
		CTurnManager(void);
		~CTurnManager(void);
	public:
		static CTurnManager& GetTurnManager(void);
		void RefreshTurn(void);
		void SetTurn(const Turn& turn);
		Turn GetTurn(void) const;
		bool IsChanged(void) const;
	};
#define	theTurnManager CTurnManager::GetTurnManager()
}