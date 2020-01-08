#include "Sound.h"



CSound::CSound(void) :
m_pSound(nullptr),
m_bPlay(false)
{
}


CSound::~CSound(void)
{
}

CSoundBuffer * CSound::GetSoundBuffer(void)
{
	return m_pSound;
}

bool CSound::IsPlay(void) const
{
	return m_bPlay;
}

void CSound::Play(const int& playType)
{
	m_pSound->Play(playType);
	m_bPlay = true;
}

bool CSound::Load(const std::string & str)
{
	m_pSound = new CSoundBuffer();
	m_pSound->Load(str.c_str());
	return true;
}

void CSound::Update(void)
{
	//�Đ��t���O�������Ă��Ȃ��ꍇ�X�L�b�v
	if (!m_bPlay)
	{
		return;
	}
	//�Đ��I�����Ă���Ȃ�t���O��܂�
	if (!m_pSound->IsPlay())
	{
		m_bPlay = false;
	}
}

void CSound::Release(void)
{
	m_pSound->Release();
	if (m_pSound)
	{
		delete m_pSound;
		m_pSound = nullptr;
	}
}
