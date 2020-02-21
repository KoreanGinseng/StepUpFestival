/*************************************************************************//*!

					@file	Animation.h
					@brief	アニメーションクラス

															@author	いのうえ
															@date	2020.02.21
*//**************************************************************************/

//ONCE
#pragma once

//INCLUDE
#include	"DxLib.h"
#include	"TextureManager.h"
#include	<unordered_map>

namespace DxLibPlus
{
	// ********************************************************************************
	/// <summary>
	/// アニメーションパターン構造体
	/// </summary>
	// ********************************************************************************
	struct Pattern {
		int		wait;				//!<待ちフレーム
		int		no;					//!<横
		int		step;				//!<縦
	};
	// ********************************************************************************
	/// <summary>
	/// アニメーション作成用構造体
	/// </summary>
	// ********************************************************************************
	template< int N > struct Animation {
		std::string	name;			//!<アニメーション名
		int			offsetX;		//!<画像オフセットX
		int			offsetY;		//!<画像オフセットY
		int			width;			//!<アニメーション幅
		int			height;			//!<アニメーション高さ
		bool		bLoop;			//!<高さ
		Pattern		pattern[N];		//!<アニメーションパターン
	};
	// ********************************************************************************
	/// <summary>
	/// 矩形構造体
	/// </summary>
	// ********************************************************************************
	struct Rectangle {
		int		left;				//!<左
		int		top;				//!<上
		int		right;				//!<右
		int		bottom;				//!<下
		// ********************************************************************************
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <returns>None</returns>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		Rectangle(void) :
			left(0),
			top(0),
			right(0),
			bottom(0)
		{
		}
		// ********************************************************************************
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="l">左</param>
		/// <param name="t">上</param>
		/// <param name="r">右</param>
		/// <param name="b">下</param>
		/// <returns></returns>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		Rectangle(const int& l, const int& t, const int& r, const int& b) :
			left(l),
			top(t),
			right(r),
			bottom(b)
		{
		}
		// ********************************************************************************
		/// <summary>
		/// 横幅取得
		/// </summary>
		/// <returns>矩形の横幅</returns>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		int GetWidth(void) const
		{
			return right - left;
		}
		// ********************************************************************************
		/// <summary>
		/// 縦幅取得
		/// </summary>
		/// <returns>矩形の縦幅</returns>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		int GetHeight(void) const
		{
			return bottom - top;
		}
	};

	// ********************************************************************************
	/// <summary>
	/// アニメーションクラス
	/// </summary>
	// ********************************************************************************
	template< int N > class CAnimation
	{
	private:
		int				m_NowFlame;			//!<現在のアニメーションフレーム
		int				m_NowWait;			//!<待機フレーム
		int				m_FlameCount;		//!<アニメーションフレーム最大数
		int				m_NowAnimNo;		//!<現在再生中のアニメーション番号
		int				m_MaxAnimCount;		//!<アニメーション最大数
		Animation<N>*	m_pAnim;			//!<アニメーション構造体配列
		bool			m_bShow;			//!<表示フラグ
	public:
		// ********************************************************************************
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <returns>None</returns>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		CAnimation(void) :
			m_NowFlame(0),
			m_NowWait(0),
			m_FlameCount(0),
			m_NowAnimNo(0),
			m_MaxAnimCount(0),
			m_pAnim(nullptr),
			m_bShow(false)
		{
		}
		// ********************************************************************************
		/// <summary>
		/// デストラクタ
		/// </summary>
		/// <returns>None</returns>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		~CAnimation(void) { Release(); }
		// ********************************************************************************
		/// <summary>
		/// アニメーション変更
		/// </summary>
		/// <param name="animNo">変更する番号</param>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		void ChangeMotion(const int& animNo)
		{
			m_NowAnimNo = animNo;
			m_FlameCount = N;
			m_NowFlame = 0;
			m_NowWait = 0;
		}
		// ********************************************************************************
		/// <summary>
		/// アニメーションの作成
		/// </summary>
		/// <param name="anim">作成する構造体</param>
		/// <param name="animCount">アニメーションの数</param>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		void Create(Animation<N>* anim, const int& animCount)
		{
			//必要数作成する
			m_pAnim = new Animation<N>[animCount];
			//データのコピー
			*m_pAnim = *anim;
			//最大数のセット
			m_MaxAnimCount = animCount;
		}
		// ********************************************************************************
		/// <summary>
		/// 解放
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		void Release(void)
		{
			if (m_pAnim)
			{
				delete[] m_pAnim;
				m_pAnim = nullptr;
			}
		}
		// ********************************************************************************
		/// <summary>
		/// アニメーションを進める
		/// </summary>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
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
		// ********************************************************************************
		/// <summary>
		/// モーション終了フラグ取得
		/// </summary>
		/// <returns>終了フラグ</returns>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		bool IsEndMotion(void) const
		{
			return m_pAnim->bLoop ? false : (m_NowFlame >= m_FlameCount);
		}
		// ********************************************************************************
		/// <summary>
		/// アニメーションの矩形取得
		/// </summary>
		/// <returns>アニメーション矩形</returns>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
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
		// ********************************************************************************
		/// <summary>
		/// 表示フラグの設定
		/// </summary>
		/// <param name="b">表示フラグ</param>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		void SetShow(const bool& b)
		{
			m_bShow = b;
		}
		// ********************************************************************************
		/// <summary>
		/// 表示フラグの取得
		/// </summary>
		/// <returns>表示フラグ</returns>
		/// <created>いのうえ,2020/02/21</created>
		/// <changed>いのうえ,2020/02/21</changed>
		// ********************************************************************************
		bool IsShow(void) const
		{
			return m_bShow;
		}
	};
}

