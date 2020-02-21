#include "SoundManager.h"

namespace DxLibPlus
{
	CSoundManager::CSoundManager(void) :
		m_List()
	{
	}

	CSoundManager::~CSoundManager(void)
	{
		Release();
	}

	CSoundManager & CSoundManager::GetSoundManager(void)
	{
		static CSoundManager manager;
		return manager;
	}

	bool CSoundManager::Load(const std::string & key, const std::string & file)
	{
		return m_List[key].Load(file);
	}
	
	void CSoundManager::Play(const std::string & key)
	{
		m_List[key].Play();
	}
	
	bool CSoundManager::IsPlay(const std::string & key)
	{
		return m_List[key].IsPlay();
	}
	
	void CSoundManager::Stop(const std::string & key)
	{
		m_List[key].Stop();
	}

	void CSoundManager::Stop(void)
	{
		for (auto& itr : m_List)
		{
			itr.second.Stop();
		}
	}
	
	void CSoundManager::SetLoop(const std::string & key, const bool & b, const int& time)
	{
		m_List[key].SetLoop(b, time);
	}
	
	void CSoundManager::Release(void)
	{
		DxLib::InitSoundMem();
	}
}