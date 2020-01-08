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
	void Load(const TCHAR* Filename) { m_Handle = LoadSoundMem(Filename); }		//サウンド読み込み
	int Play(int PlayType) { return PlaySoundMem(m_Handle, PlayType, TRUE); }	//サウンド再生
	int IsPlay() { return CheckSoundMem(m_Handle); }							//再生中か判定
	int Stop() { return StopSoundMem(m_Handle); }								//サウンド停止
	int Resume(int PlayType) { return PlaySoundMem(m_Handle, PlayType, FALSE); } //サウンド再開
	int Release() { return DeleteSoundMem(m_Handle); }							//サウンド削除
	int ChengeVolume(int VolumePal) { m_Volume = VolumePal; return ChangeVolumeSoundMem(m_Volume, m_Handle); }//音量調整
	int GetVolume() { return m_Volume; }
};

//サウンドエフェクト用クラス
class CSound
{
private:
	CSoundBuffer*	m_pSound;						//! サウンド
	bool			m_bPlay;						//! 再生フラグ
public:
	CSound(void);									//! コンストラクタ
	~CSound(void);									//! デストラクタ
	CSoundBuffer*	GetSoundBuffer(void);			//! サウンド取得
	bool			IsPlay(void) const;				//! 再生フラグ取得
	void			Play(void);						//! 再生
	bool			Load(const std::string& str);	//! 読込
	void			Update(void);					//! 更新
	void			Release(void);					//! 解放
};

