/*************************************************************************//*!

					@file	Sound.cpp
					@brief	サウンドクラス

															@author	いのうえ
															@date	2020.02.21
*//**************************************************************************/

//INCLUDE
#include "Sound.h"

namespace DxLibPlus
{
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <returns>None</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	CSound::CSound(void) :
		m_SoundHandle(0),
		m_bLoop(false)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <returns>None</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	CSound::~CSound(void)
	{
		Release();
	}
	// ********************************************************************************
	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="file">ファイル名</param>
	/// <returns></returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	bool CSound::Load(const std::string & file)
	{
		m_SoundHandle = DxLib::LoadSoundMem(file.c_str());
		if (m_SoundHandle == -1)
		{
			return false;
		}
		return true;
	}
	// ********************************************************************************
	/// <summary>
	/// 再生する
	/// </summary>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	void CSound::Play(void)
	{
		int playType = m_bLoop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK;
		DxLib::PlaySoundMem(m_SoundHandle, playType);
	}
	// ********************************************************************************
	/// <summary>
	/// 再生中かチェックする
	/// </summary>
	/// <returns>再生中かどうかのフラグ</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	bool CSound::IsPlay(void) const
	{
		return DxLib::CheckSoundMem(m_SoundHandle) ? true : false;
	}
	// ********************************************************************************
	/// <summary>
	/// 止める
	/// </summary>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	void CSound::Stop(void)
	{
		DxLib::StopSoundMem(m_SoundHandle);
	}
	// ********************************************************************************
	/// <summary>
	/// ループ設定
	/// </summary>
	/// <param name="b">ループフラグ</param>
	/// <param name="loopTime">ループ再生する開始時間(ミリ秒)</param>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	void CSound::SetLoop(const bool & b, const int& loopTime)
	{
		m_bLoop = b;
		DxLib::SetLoopPosSoundMem(loopTime, m_SoundHandle);
	}
	// ********************************************************************************
	/// <summary>
	/// 解放
	/// </summary>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	void CSound::Release(void)
	{
		DxLib::DeleteSoundMem(m_SoundHandle);
	}
}
