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
		/// ì«Ç›çûÇ›
		/// </summary>
		/// <created>Ç¢ÇÃÇ§Ç¶,2020/02/21</created>
		/// <changed>Ç¢ÇÃÇ§Ç¶,2020/02/21</changed>
		// ********************************************************************************
		virtual bool Load(void) override;
		// ********************************************************************************
		/// <summary>
		/// èâä˙âª
		/// </summary>
		/// <created>Ç¢ÇÃÇ§Ç¶,2020/02/21</created>
		/// <changed>Ç¢ÇÃÇ§Ç¶,2020/02/21</changed>
		// ********************************************************************************
		virtual void Initialize(void) override;
		// ********************************************************************************
		/// <summary>
		/// çXêV
		/// </summary>
		/// <created>Ç¢ÇÃÇ§Ç¶,2020/02/21</created>
		/// <changed>Ç¢ÇÃÇ§Ç¶,2020/02/21</changed>
		// ********************************************************************************
		virtual void Update(void) override;
		// ********************************************************************************
		/// <summary>
		/// ï`âÊ
		/// </summary>
		/// <created>Ç¢ÇÃÇ§Ç¶,2020/02/21</created>
		/// <changed>Ç¢ÇÃÇ§Ç¶,2020/02/21</changed>
		// ********************************************************************************
		virtual void Render(void) override;

	};
}

