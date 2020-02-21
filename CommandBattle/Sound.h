#pragma once
#include	"DxLib.h"
#include	<string>

namespace DxLibPlus
{
	class CSound
	{
	private:
		int m_SoundHandle;
		bool m_bLoop;
	public:
		CSound(void);
		~CSound(void);
		bool Load(const std::string& file);
		void Play(void);
		bool IsPlay(void) const;
		void Stop(void);
		void SetLoop(const bool& b, const int& loopTime = 0);
		void Release(void);
	};
}

