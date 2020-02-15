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
				@brief			‰Šú‰»
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Initialize(void) override;
		/*************************************************************************//*!
				@brief			XV
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Update(void) override;
		/*************************************************************************//*!
				@brief			•`‰æ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Render(void) override;
		/*************************************************************************//*!
				@brief			‰ğ•ú
				@param			None

				@return			None
		*//**************************************************************************/
		virtual void Release(void) override;
	};
}