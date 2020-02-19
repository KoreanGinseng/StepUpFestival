#include "KeyInput.h"


namespace DxLibPlus
{
	CKeyInput & CKeyInput::GetKeyInput(void)
	{
		static CKeyInput obj;
		return obj;
	}
	void CKeyInput::RefreshKey(void)
	{
		for (int i = 0; i < 256; i++)
		{
			m_Prev[i] = m_Now[i];
		}
		for (int i = 0; i < 256; i++)
		{
			m_Now[i] = DxLib::CheckHitKey(i);
		}
	}
	bool CKeyInput::IsKeyPush(const int & keycode) const
	{
		return (!m_Prev[keycode] && m_Now[keycode]);
	}
	bool CKeyInput::IsKeyHold(const int & keycode) const
	{
		return (m_Now[keycode]);
	}
	bool CKeyInput::IsKeyPull(const int & keycode) const
	{
		return (m_Prev[keycode] && !m_Now[keycode]);
	}
}
