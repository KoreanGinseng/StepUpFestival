#include "SoundManager.h"



CSoundManager::CSoundManager(void)
{
}

CSoundManager::~CSoundManager(void)
{
}

CSoundManager * CSoundManager::GetSound(void)
{
	static CSoundManager obj;
	return &obj;
}

CSound * CSoundManager::GetSoundSE(const std::string & str)
{
	if (CSoundManager::GetSound()->m_ResourceSE[str].size() <= 0)
	{
		CSoundManager::LoadSE(str);
	}
	CSound* re;
	int c = CSoundManager::GetSound()->m_ResourceSE[str].size();
	bool bFind = false;
	//再生可能のサウンドを探す
	for (int i = 0; i < c; i++)
	{
		re = CSoundManager::GetSound()->m_ResourceSE[str][i];
		//再生中なら次
		if (re->IsPlay())
		{
			continue;
		}
		//見つけたらぬける
		bFind = true;
		break;
	}
	//見つからなかった場合追加する
	if (!bFind)
	{
		//サウンドの大きさを取得
		float vol = CSoundManager::GetSound()->m_ResourceSE[str][0]->GetSoundBuffer()->GetVolume();
		//追加
		CSoundManager::GetSound()->m_ResourceSE[str].push_back(NEW CSound());
		CSoundManager::GetSound()->m_ResourceSE[str][c]->Load(str.c_str());
		//サウンドの大きさを合わせる
		CSoundManager::GetSound()->m_ResourceSE[str][c]->GetSoundBuffer()->SetVolume(vol);
		re = CSoundManager::GetSound()->m_ResourceSE[str][c];
	}
	return re;
}

CSoundBuffer * CSoundManager::GetSoundBGM(const std::string & str)
{
	if (CSoundManager::GetSound()->m_ResourceBGM[str] == nullptr)
	{
		CSoundManager::LoadBGM(str);
	}
	return CSoundManager::GetSound()->m_ResourceBGM[str];
}

CSoundBuffer * CSoundManager::GetSoundBuffer(const std::string & str)
{
	CSoundBuffer* re = CSoundManager::GetSoundSE(str)->GetSoundBuffer();
	if (re == nullptr)
	{
		re = CSoundManager::GetSoundBGM(str);
	}
	return re;
}

void CSoundManager::PlaySE(const std::string & str, const int& playType)
{
	CSoundManager::GetSoundSE(str)->Play(playType);
}

void CSoundManager::PlayBGM(const std::string & str, const int& playType)
{
	CSoundManager::GetSoundBGM(str)->Play(playType);
}

void CSoundManager::SetVolumeSE(const std::string & str, const float & vol)
{
	int c = CSoundManager::GetSound()->m_ResourceSE[str].size();
	for (int i = 0; i < c; i++)
	{
		CSoundManager::GetSound()->m_ResourceSE[str][i]->GetSoundBuffer()->SetVolume(vol);
	}
}

void CSoundManager::SetVolumeBGM(const std::string & str, const float & vol)
{
	CSoundManager::GetSoundBGM(str)->SetVolume(vol);
}

bool CSoundManager::LoadSE(const std::string& str)
{
	for (int i = 0; i < DefSoundPool; i++)
	{
		CSoundManager::GetSound()->m_ResourceSE[str].push_back(NEW CSound());
		if (!CSoundManager::GetSound()->m_ResourceSE[str][i]->Load(str))
		{
			return false;
		}
	}
	return true;
}

bool CSoundManager::LoadBGM(const std::string & str)
{
	if (CSoundManager::GetSound()->m_ResourceBGM[str] != nullptr)
	{
		return true;
	}
	CSoundManager::GetSound()->m_ResourceBGM[str] = new CSoundBuffer();
	CSoundManager::GetSound()->m_ResourceBGM[str]->Load(str.c_str());
	//CSoundManager::GetSound()->m_ResourceBGM[str]->SetLoop(TRUE);
	return true;
}

void CSoundManager::Update(void)
{
	for (auto& itr : CSoundManager::GetSound()->m_ResourceSE)
	{
		int c = itr.second.size();
		for (int i = 0; i < c; i++)
		{
			itr.second[i]->Update();
		}
	}
}

void CSoundManager::Release(void)
{
	for (auto& itr : CSoundManager::GetSound()->m_ResourceSE)
	{
		int c = itr.second.size();
		for (int i = 0; i < c; i++)
		{
			itr.second[i]->Release();
			delete itr.second[i];
			itr.second[i] = nullptr;
		}
		itr.second.clear();
	}
	for (auto& itr : CSoundManager::GetSound()->m_ResourceBGM)
	{
			itr.second->Release();
			delete itr.second;
			itr.second = nullptr;
	}
	CSoundManager::GetSound()->m_ResourceBGM.clear();
}
