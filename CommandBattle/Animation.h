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
		CAnimation(void);
		~CAnimation(void);
		void ChangeMotion(const int& animNo);
		void Create(Animation<N>* anim, const int& animCount);
		void AddTimer(void);
		Rectangle GetSrcRect(void) const;
	};
}

