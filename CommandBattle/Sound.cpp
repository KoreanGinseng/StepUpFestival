#include "Sound.h"

namespace DxLibPlus
{
	CSound::CSound(void) :
		m_SoundHandle(0),
		m_bLoop(false)
	{
	}

	CSound::~CSound(void)
	{
		Release();
	}
	
	bool CSound::Load(const std::string & file)
	{
		m_SoundHandle = DxLib::LoadSoundMem(file.c_str());
		if (m_SoundHandle == -1)
		{
			return false;
		}
		return true;
	}
	
	void CSound::Play(void)
	{
		int playType = m_bLoop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK;
		DxLib::PlaySoundMem(m_SoundHandle, playType);
	}

	bool CSound::IsPlay(void) const
	{
		return DxLib::CheckSoundMem(m_SoundHandle) ? true : false;
	}
	
	void CSound::Stop(void)
	{
		DxLib::StopSoundMem(m_SoundHandle);
	}
	
	void CSound::SetLoop(const bool & b, const int& loopTime)
	{
		m_bLoop = b;
		DxLib::SetLoopPosSoundMem(loopTime, m_SoundHandle);
	}
	
	void CSound::Release(void)
	{
		DxLib::DeleteSoundMem(m_SoundHandle);
	}
}
