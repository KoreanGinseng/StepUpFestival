#pragma once
#include "Chara.h"
#include <iostream>
#include <fstream>
#include <codecvt>

namespace DxLibPlus
{
	enum EnemyType {
		ENE_RED,
		ENE_GREEN,
		ENE_BLUE,
		ENE_KOMODO,

		ENE_COUNT,
	};

	class CEnemy : public CChara
	{
	private:
		EnemyType	m_Type;
		int			m_GraphHandle;
		TextureKey  m_TexKey;
	public:
		CEnemy(void);
		~CEnemy(void);
		// ********************************************************************************
		/// <summary>
		/// 読み込み
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		virtual bool Load(void) override;
		// ********************************************************************************
		/// <summary>
		/// 初期化
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		virtual void Initialize(void) override;
		// ********************************************************************************
		/// <summary>
		/// 更新
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		virtual void Update(void) override;
		// ********************************************************************************
		/// <summary>
		/// 描画
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		virtual void Render(void) override;

	};
}

