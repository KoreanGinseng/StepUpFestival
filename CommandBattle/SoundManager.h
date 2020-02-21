#pragma once
#include	"Sound.h"
#include	<unordered_map>

namespace DxLibPlus 
{
	class CSoundManager
	{
	private:
		std::unordered_map<std::string, CSound>	m_List;
		CSoundManager(void);
		~CSoundManager(void);
	public:
		static CSoundManager& GetSoundManager(void);
		bool Load(const std::string& key, const std::string& file);
		void Play(const std::string& key);
		bool IsPlay(const std::string& key);
		void Stop(const std::string& key);
		void Stop(void);
		void SetLoop(const std::string& key, const bool& b, const int& time = 0);
		void Release(void);
	};
#define theSoundManager CSoundManager::GetSoundManager()
}

