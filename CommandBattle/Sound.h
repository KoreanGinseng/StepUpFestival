#pragma once
#include	"DxLibPlus.h"
#include	<string>

class CSoundBuffer {
private:
	int		m_Handle;
	float	m_Volume;
public:
	CSoundBuffer() : m_Handle(0), m_Volume(0) {}
	~CSoundBuffer() {};
	void Load(const TCHAR* Filename) { m_Handle = LoadSoundMem(Filename); }		//�T�E���h�ǂݍ���
	int Play(int PlayType) { return PlaySoundMem(m_Handle, PlayType, TRUE); }	//�T�E���h�Đ�
	int IsPlay() { return CheckSoundMem(m_Handle); }							//�Đ���������
	int Stop() { return StopSoundMem(m_Handle); }								//�T�E���h��~
	int Resume(int PlayType) { return PlaySoundMem(m_Handle, PlayType, FALSE); } //�T�E���h�ĊJ
	int Release() { return DeleteSoundMem(m_Handle); }							//�T�E���h�폜
	int ChengeVolume(int VolumePal) { m_Volume = VolumePal; return ChangeVolumeSoundMem(m_Volume, m_Handle); }//���ʒ���
	int GetVolume() { return m_Volume; }
};

//�T�E���h�G�t�F�N�g�p�N���X
class CSound
{
private:
	CSoundBuffer*	m_pSound;						//! �T�E���h
	bool			m_bPlay;						//! �Đ��t���O
public:
	CSound(void);									//! �R���X�g���N�^
	~CSound(void);									//! �f�X�g���N�^
	CSoundBuffer*	GetSoundBuffer(void);			//! �T�E���h�擾
	bool			IsPlay(void) const;				//! �Đ��t���O�擾
	void			Play(void);						//! �Đ�
	bool			Load(const std::string& str);	//! �Ǎ�
	void			Update(void);					//! �X�V
	void			Release(void);					//! ���
};

