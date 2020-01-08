#include "SceneEffectBase.h"
#include "GameDefine.h"


CSceneEffectBase::CSceneEffectBase(void) :
m_Type(0),
m_Alpha(0),
m_bEnd(false),
m_Spd(1)
{
}

CSceneEffectBase::~CSceneEffectBase(void)
{
}

bool CSceneEffectBase::Load(void)
{
	return true;
}

void CSceneEffectBase::Initialize(void)
{
	switch (m_Type)
	{
	case EFFECTTYPE_IN:
	{
		m_Alpha = 255;
		break;
	}
	case EFFECTTYPE_OUT:
	{
		m_Alpha = 0;
		break;
	}
	default:
		break;
	}
	m_bEnd = false;
}

void CSceneEffectBase::SetType(const int & type)
{
	m_Type = type;
}

void CSceneEffectBase::SetSpd(const float & spd)
{
	m_Spd = spd;
}

int CSceneEffectBase::GetType(void) const
{
	return m_Type;
}

float CSceneEffectBase::GetSpd(void) const
{
	return m_Spd;
}

bool CSceneEffectBase::IsEnd(void) const
{
	return m_bEnd;
}
