/*************************************************************************//*!

					@file	EffectManager.h
					@brief	エフェクトマネージャークラス

															@author	いのうえ
															@date	2020.02.21
*//**************************************************************************/

//ONCE
#pragma once

//INCLUDE
#include	"Animation.h"
#include	"TextureManager.h"

namespace DxLibPlus
{
	/// <summary>スキルの列挙</summary>
	enum SkillType {
		SKILL_FIRE,		//!<炎
		SKILL_ICE,		//!<氷
		SKILL_THUNDER,	//!<雷
		SKILL_SLASH,	//!<斬撃

		SKILL_COUNT,	//!<スキル最大数
	};

	// ********************************************************************************
	/// <summary>
	/// エフェクトマネージャークラス
	/// </summary>
	// ********************************************************************************
	class CEffectManager
	{
	private:
		std::unordered_map<SkillType, CAnimation<10>>	m_EffectList;	//!<リスト
		SkillType										m_PlayType;		//!<再生スキル

		// ********************************************************************************
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <returns>None</returns>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		CEffectManager(void);
		// ********************************************************************************
		/// <summary>
		/// デストラクタ
		/// </summary>
		/// <returns>None</returns>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		~CEffectManager(void);
	public:
		// ********************************************************************************
		/// <summary>
		/// マネージャーの取得
		/// </summary>
		/// <returns>マネージャー</returns>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		static CEffectManager& GetEffectManager(void);
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
		void CreateEffect(const SkillType & type, Animation<10>* pAnim, const int& animCount);
		// ********************************************************************************
		/// <summary>
		/// エフェクト開始
		/// </summary>
		/// <param name="type">開始するエフェクトタイプ</param>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		void Start(const SkillType & type);
		// ********************************************************************************
		/// <summary>
		/// エフェクトの更新
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		void Update(void);
		// ********************************************************************************
		/// <summary>
		/// エフェクトの描画
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		void Render(void);
		// ********************************************************************************
		/// <summary>
		/// 解放
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		void Release(void);
	};
#define theEffectManager CEffectManager::GetEffectManager()
}

