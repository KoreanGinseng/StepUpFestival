#include "Animation.h"

namespace DxLibPlus
{
	template<int N>
	CAnimation<N>::CAnimation(void) :
		m_NowFrame(0),
		m_NowWait(0),
		m_FrameCount(0),
		m_NowAnimNo(0),
		m_MAXAnimCount(0),
		m_pAnimFrame(nullptr)
	{
	}

	template<int N>
	CAnimation<N>::~CAnimation(void)
	{
	}
	
	template<int N>
	void CAnimation<N>::ChangeMotion(const int & animNo)
	{
		m_NowAnimNo = animNo;
		m_FlameCount = N;
	}
	
	template<int N>
	void CAnimation<N>::Create(Animation<N>* anim, const int & animCount)
	{
		m_pAnim = new Animation<N>()[animCount];
		m_pAnim = *anim;
		m_MaxAnimCount = animCount;
	}
	
	template<int N>
	void CAnimation<N>::AddTimer(void)
	{
		if (++m_NowWait >= m_pAnim[m_NowAnimNo].pattern[m_NowFlame].wait)
		{
			m_NowWait = 0;
			if (++m_NowFlame >= m_FlameCount)
			{
				m_NowFlame = m_pAnim[m_NowAnimNo].bLoop ? 0 : m_FlameCount;
			}
		}
	}
	
	template<int N>
	Rectangle CAnimation<N>::GetSrcRect(void) const
	{
		int x = m_pAnim[m_NowAnimNo].offsetX + m_pAnim[m_NowAnimNo].width * m_pAnim[m_NowAnimNo].pattern[m_NowFrame].no;
		int y = m_pAnim[m_NowAnimNo].offsetY + m_pAnim[m_NowAnimNo].height * m_pAnim[m_NowAnimNo].pattern[m_NowFrame].step;
		return Rectangle(
			x,
			y,
			x + m_pAnim[m_NowAnimNo].width,
			y + m_pAnim[m_NowAnimNo].height
		);
	}
}