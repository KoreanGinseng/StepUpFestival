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
		/// �ǂݍ���
		/// </summary>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		virtual bool Load(void) override;
		// ********************************************************************************
		/// <summary>
		/// ������
		/// </summary>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		virtual void Initialize(void) override;
		// ********************************************************************************
		/// <summary>
		/// �X�V
		/// </summary>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		virtual void Update(void) override;
		// ********************************************************************************
		/// <summary>
		/// �`��
		/// </summary>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		virtual void Render(void) override;

	};
}

