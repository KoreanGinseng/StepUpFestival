/*************************************************************************//*!

					@file	EffectManager.cpp
					@brief	エフェクトマネージャークラス

															@author	いのうえ
															@date	2020.02.21
*//**************************************************************************/

//INCLUDE
#include "EffectManager.h"
#include "GraphicsUtillities.h"
#include "GameDefine.h"

namespace DxLibPlus
{
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <returns>None</returns>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	CEffectManager::CEffectManager(void) :
		m_EffectList(),
		m_PlayType(SKILL_FIRE)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <returns>None</returns>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	CEffectManager::~CEffectManager(void)
	{
		Release();
	}
	// ********************************************************************************
	/// <summary>
	/// マネージャーの取得
	/// </summary>
	/// <returns>マネージャー</returns>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	CEffectManager & CEffectManager::GetEffectManager(void)
	{
		static CEffectManager manager;
		return manager;
	}
	// ********************************************************************************
	/// <summary>
	/// エフェクトの作成
	/// </summary>
	/// <param name="type">エフェクトのタイプ</param>
	/// <param name="pAnim">アニメーション構造体</param>
	/// <param name="animCount">アニメーション数</param>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CEffectManager::CreateEffect(const SkillType & type, Animation<10>* pAnim, const int & animCount)
	{
		m_EffectList[type].Create(pAnim, animCount);
	}
	// ********************************************************************************
	/// <summary>
	/// エフェクト開始
	/// </summary>
	/// <param name="type">開始するエフェクトタイプ</param>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CEffectManager::Start(const SkillType & type)
	{
		m_EffectList[type].SetShow(true);
		m_EffectList[type].ChangeMotion(0);
		m_PlayType = type;
	}
	// ********************************************************************************
	/// <summary>
	/// エフェクトの更新
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CEffectManager::Update(void)
	{
		//全件回す
		for (auto& itr : m_EffectList)
		{
			//表示フラグが立ってないやつはスキップ
			if (!itr.second.IsShow())
			{
				continue;
			}
			//アニメーション更新
			itr.second.AddTimer();
			//アニメーションが終了していれば表示フラグをもとに戻す
			if (itr.second.IsEndMotion())
			{
				itr.second.SetShow(false);
			}
		}
	}
	// ********************************************************************************
	/// <summary>
	/// エフェクトの描画
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CEffectManager::Render(void)
	{
		//表示フラグが立ってないやつは表示しない
		if (!m_EffectList[m_PlayType].IsShow())
		{
			return;
		}
		//表示するエフェクトを取得する
		TextureKey texKey;
		switch (m_PlayType)
		{
		case SKILL_FIRE:
			texKey = TEXKEY_EFFECT_FIRE;
			break;
		case SKILL_ICE:
			texKey = TEXKEY_EFFECT_ICE;
			break;
		case SKILL_SLASH:
			texKey = TEXKEY_EFFECT_SLASH;
			break;
		case SKILL_THUNDER:
			texKey = TEXKEY_EFFECT_THUNDER;
			break;
		}
		//画像ハンドル取得
		int graphHandle = theTextureManager.GetGraphHandle(TexFile[texKey].key);
		//表示位置を中央にする
		float x = (CGraphicsUtillities::GetTargetWidth() - 192) * 0.5f;
		//矩形取得
		Rectangle rect = m_EffectList[m_PlayType].GetSrcRect();
		//画像の矩形部分のみ表示(アニメーション)
		DxLib::DrawRectGraph(static_cast<int>(x), PlayerRectW, rect.left, rect.top, rect.GetWidth(), rect.GetHeight(), graphHandle, true);
	}
	// ********************************************************************************
	/// <summary>
	/// 解放
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CEffectManager::Release(void)
	{
		for (auto& itr : m_EffectList)
		{
			itr.second.Release();
		}
		m_EffectList.clear();
	}
}