#pragma once
#include	"GameAppBase.h"

namespace DxLibPlus
{
	class CTurnManager : public CGameAppBase
	{
	public:
		CTurnManager(void);
		~CTurnManager(void);
		/*************************************************************************//*!
				@brief			������
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Initialize(void) override;
		/*************************************************************************//*!
				@brief			�X�V
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Update(void) override;
		/*************************************************************************//*!
				@brief			�`��
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Render(void) override;
		/*************************************************************************//*!
				@brief			���
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Release(void) override;
	};
}