#pragma once
#include "GameAppBase.h"
#include "GameDefine.h"

namespace DxLibPlus
{
	class CChara : public CGameAppBase
	{
	protected:
		Status		m_Status;
	public:
		/*************************************************************************//*!
				@brief			�R���X�g���N�^
				@param			None

				@return			None
		*//**************************************************************************/
		CChara(void);
		/*************************************************************************//*!
				@brief			�f�X�g���N�^
				@param			None

				@return			None
		*//**************************************************************************/
		~CChara(void);
		/*************************************************************************//*!
				@brief			������
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Initialize(void) = 0;
		/*************************************************************************//*!
				@brief			�X�V
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Update(void) = 0;
		/*************************************************************************//*!
				@brief			�`��
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Render(void) = 0;
		/*************************************************************************//*!
				@brief			���
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Release(void) override;

		void Dmg(const int& dmg);
		int GetAttack(void) const;
		int GetHp(void) const;
	};
}

