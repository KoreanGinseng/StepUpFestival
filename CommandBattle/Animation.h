#pragma once
#include	"DxLib.h"
#include	"TextureManager.h"
#include	<unordered_map>

namespace DxLibPlus
{
	struct Pattern {
		int		wait;
		int		no;
		int		step;
	};
	template< int N > struct Animation {
		std::string	name;
		int			offsetX;
		int			offsetY;
		int			width;
		int			height;
		bool		bLoop;
		Pattern		pattern[N];
	};
	struct Rectangle {
		int		left;
		int		top;
		int		right;
		int		bottom;
		Rectangle(void) :
			left(0),
			top(0),
			right(0),
			bottom(0)
		{
		}
		Rectangle(const int& l, const int& t, const int& r, const int& b) :
			left(l),
			top(t),
			right(r),
			bottom(b)
		{
		}
		int GetWidth(void) const
		{
			return right - left;
		}
		int GetHeight(void) const
		{
			return bottom - top;
		}
	};

	template< int N > class CAnimation
	{
	private:
		int				m_NowFlame;
		int				m_NowWait;
		int				m_FlameCount;
		int				m_NowAnimNo;
		int				m_MaxAnimCount;
		Animation<N>*	m_pAnim;
	public:
		CAnimation(void) :
			m_NowFlame(0),
			m_NowWait(0),
			m_FlameCount(0),
			m_NowAnimNo(0),
			m_MaxAnimCount(0),
			m_pAnim(nullptr)
		{
		}
		~CAnimation(void) {}
		void ChangeMotion(const int& animNo)
		{
			m_NowAnimNo = animNo;
			m_FlameCount = N;
		}
		void Create(Animation<N>* anim, const int& animCount)
		{
			m_pAnim = new Animation<N>()[animCount];
			m_pAnim = *anim;
			m_MaxAnimCount = animCount;
		}
		void AddTimer(void)
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
		Rectangle GetSrcRect(void) const
		{
			int x = m_pAnim[m_NowAnimNo].offsetX + m_pAnim[m_NowAnimNo].width * m_pAnim[m_NowAnimNo].pattern[m_NowFlame].no;
			int y = m_pAnim[m_NowAnimNo].offsetY + m_pAnim[m_NowAnimNo].height * m_pAnim[m_NowAnimNo].pattern[m_NowFlame].step;
			return Rectangle(
				x,
				y,
				x + m_pAnim[m_NowAnimNo].width,
				y + m_pAnim[m_NowAnimNo].height
			);
		}
	};
}

