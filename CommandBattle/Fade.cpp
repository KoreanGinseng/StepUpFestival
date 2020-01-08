#include "Fade.h"
#include "GameDefine.h"
#include "Mof.h"

CFade::CFade(void)
{
}


CFade::~CFade(void)
{
}

void CFade::Update(void)
{
	switch (m_Type)
	{
	case EFFECTTYPE_IN:
	{
		m_Alpha -= m_Spd;
		if (m_Alpha < 0)
		{
			m_bEnd = true;
		}
		break;
	}
	case EFFECTTYPE_OUT:
	{
		m_Alpha += m_Spd;
		if (m_Alpha > 255)
		{
			m_bEnd = true;
		}
		break;
	}
	default:
		break;
	}
}

void CFade::Render(void)
{
	CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_ARGB(static_cast<int>(m_Alpha), 0, 0, 0));
}
