#pragma once
#include	"DxLib.h"

namespace DxLibPlus
{
	class CKeyInput
	{
	private:
		bool m_Now[256];
		bool m_Prev[256];
		CKeyInput(void) = default;
		~CKeyInput(void) = default;
	public:
		static CKeyInput& GetKeyInput(void);
		void RefreshKey(void);
		bool IsKeyPush(const int& keycode) const;
		bool IsKeyHold(const int& keycode) const;
		bool IsKeyPull(const int& keycode) const;
	};
#define	theInput CKeyInput::GetKeyInput()
}

