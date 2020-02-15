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
				@brief			初期化
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Initialize(void) override;
		/*************************************************************************//*!
				@brief			更新
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Update(void) override;
		/*************************************************************************//*!
				@brief			描画
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Render(void) override;
		/*************************************************************************//*!
				@brief			解放
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Release(void) override;
	};
}