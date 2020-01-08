/*********************************************************************************************************
 * @file		Animation.cpp
 * @brief		アニメーションクラスの実装
 * @author		井上颯騎
 * @date		2019/07/14
 *********************************************************************************************************/
#include		"Animation.h"

/*********************************************************************************************************
 * @fn
 * アニメーションパターンの変更関数
 * @brief				アニメーションパターンの変更
 * @param(animNo)		アニメーションパターン番号
 * @return				なし
 *********************************************************************************************************/
void CAnimation::ChangeMotion(int animNo) {
	// アニメーションパターン番号セット
	m_AnimCount = animNo;
	// アニメーション終了フレームまでカウント
	int i = 0;
	while (m_pAnimFrame[m_AnimCount].Pattern[i].Wait != 999 && m_pAnimFrame[m_AnimCount].Pattern[i].No != 999 && m_pAnimFrame[m_AnimCount].Pattern[i].Step != 999) {
		i++;
	}
	// アニメーション終了フレーム数をセット
	m_FrameCount = i;
}

/*********************************************************************************************************
 * @fn
 * アニメーションクラスへのアニメーション生成関数
 * @brief				アニメーション生成
 * @param(*anim)		アニメーションパターンのポインタ
 * @param(animCount)	アニメーションパターンの最大数
 * @return		なし
 *********************************************************************************************************/
void CAnimation::Create(ANIMATIONFRAME* anim, int animCount) {
	// アニメーションパターンのポインタをセット
	m_pAnimFrame = anim;
	// アニメーションパターンの最大数をセット
	m_MAXAnimCount = animCount;
}

/*********************************************************************************************************
 * @fn
 * 現在のアニメーションパターンのフレームを加算する関数
 * @brief		アニメーションフレーム加算
 * @param()		なし
 * @return		なし
 *********************************************************************************************************/
void CAnimation::AddTimer() { 
	// アニメーションパターン数がマイナスにならないようにする
	if (m_AnimCount < 0) {
		m_AnimCount = 0;
	}

	// アニメーションパターンの最大数を超えないようにする
	if (m_AnimCount >= m_MAXAnimCount) {
		m_AnimCount = m_MAXAnimCount;
	}

	// アニメーション待機フレーム加算
	m_NowWait++;

	// アニメーションの待機フレームを超えていたら現在のアニメーションフレームを加算する
	if (m_NowWait >= m_pAnimFrame[m_AnimCount].Pattern[m_NowFrame].Wait) {
		m_NowWait = 0;
		m_NowFrame++;
		// ループフラグが立っていればアニメーションフレームを初期化
		if (m_NowFrame >= m_FrameCount) {
			m_NowFrame = m_pAnimFrame[m_AnimCount].bLoop ? 0 : m_FrameCount;
		}
	}
}

/*********************************************************************************************************
 * @fn
 * 現在のアニメーションの矩形を取得する関数
 * @brief		現在のアニメーション矩形取得
 * @param()		なし
 * @return		現在のアニメーション矩形
 *********************************************************************************************************/
SRectangle	CAnimation::GetSrcRect() {
	return SRectGet(m_pAnimFrame[m_AnimCount].OffsetX + m_pAnimFrame[m_AnimCount].Width * m_pAnimFrame[m_AnimCount].Pattern[m_NowFrame].No,
		m_pAnimFrame[m_AnimCount].OffsetY + m_pAnimFrame[m_AnimCount].Height * m_pAnimFrame[m_AnimCount].Pattern[m_NowFrame].Step,
		m_pAnimFrame[m_AnimCount].Width,
		m_pAnimFrame[m_AnimCount].Height);
}

void CAnimation::SetTime(const int & time)
{
	m_NowFrame = time;
	m_NowWait = 0;
}

bool CAnimation::IsEndMotion(void)
{
	return m_pAnimFrame[m_AnimCount].bLoop ? false : m_NowFrame == m_FrameCount ? true : false;
}
