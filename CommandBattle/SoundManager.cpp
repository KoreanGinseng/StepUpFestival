/*************************************************************************//*!

					@file	SoundManager.cpp
					@brief	サウンド管理クラス

															@author	いのうえ
															@date	2020.02.21
*//**************************************************************************/

//INCLUDE
#include "SoundManager.h"

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
	CSoundManager::CSoundManager(void) :
		m_List()
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
	CSoundManager::~CSoundManager(void)
	{
		Release();
	}
	// ********************************************************************************
	/// <summary>
	/// マネージャ取得
	/// </summary>
	/// <returns>マネージャ</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	CSoundManager & CSoundManager::GetSoundManager(void)
	{
		static CSoundManager manager;
		return manager;
	}
	// ********************************************************************************
	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="key">呼び出し用キー</param>
	/// <param name="file">ファイル名</param>
	/// <returns>成功(0)か失敗(-1)</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	bool CSoundManager::Load(const std::string & key, const std::string & file)
	{
		return m_List[key].Load(file);
	}
	// ********************************************************************************
	/// <summary>
	/// 再生する
	/// </summary>
	/// <param name="key">呼び出し用キー</param>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	void CSoundManager::Play(const std::string & key)
	{
		m_List[key].Play();
	}
	// ********************************************************************************
	/// <summary>
	/// 再生中かどうかチェックする
	/// </summary>
	/// <param name="key">呼び出し用キー</param>
	/// <returns>再生中かどうかのフラグ</returns>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	bool CSoundManager::IsPlay(const std::string & key)
	{
		return m_List[key].IsPlay();
	}
	// ********************************************************************************
	/// <summary>
	/// 止める
	/// </summary>
	/// <param name="key">呼び出し用キー</param>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	void CSoundManager::Stop(const std::string & key)
	{
		m_List[key].Stop();
	}
	// ********************************************************************************
	/// <summary>
	/// すべての音を止める
	/// </summary>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	void CSoundManager::Stop(void)
	{
		for (auto& itr : m_List)
		{
			itr.second.Stop();
		}
	}
	// ********************************************************************************
	/// <summary>
	/// ループ設定
	/// </summary>
	/// <param name="key">呼び出し用キー</param>
	/// <param name="b">ループフラグ</param>
	/// <param name="time">ループする開始時間(ミリ秒)</param>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	void CSoundManager::SetLoop(const std::string & key, const bool & b, const int& time)
	{
		m_List[key].SetLoop(b, time);
	}
	// ********************************************************************************
	/// <summary>
	/// 解放
	/// </summary>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	void CSoundManager::Release(void)
	{
		DxLib::InitSoundMem();
	}
}