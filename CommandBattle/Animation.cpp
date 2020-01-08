/*********************************************************************************************************
 * @file		Animation.cpp
 * @brief		�A�j���[�V�����N���X�̎���
 * @author		����D�R
 * @date		2019/07/14
 *********************************************************************************************************/
#include		"Animation.h"

/*********************************************************************************************************
 * @fn
 * �A�j���[�V�����p�^�[���̕ύX�֐�
 * @brief				�A�j���[�V�����p�^�[���̕ύX
 * @param(animNo)		�A�j���[�V�����p�^�[���ԍ�
 * @return				�Ȃ�
 *********************************************************************************************************/
void CAnimation::ChangeMotion(int animNo) {
	// �A�j���[�V�����p�^�[���ԍ��Z�b�g
	m_AnimCount = animNo;
	// �A�j���[�V�����I���t���[���܂ŃJ�E���g
	int i = 0;
	while (m_pAnimFrame[m_AnimCount].Pattern[i].Wait != 999 && m_pAnimFrame[m_AnimCount].Pattern[i].No != 999 && m_pAnimFrame[m_AnimCount].Pattern[i].Step != 999) {
		i++;
	}
	// �A�j���[�V�����I���t���[�������Z�b�g
	m_FrameCount = i;
}

/*********************************************************************************************************
 * @fn
 * �A�j���[�V�����N���X�ւ̃A�j���[�V���������֐�
 * @brief				�A�j���[�V��������
 * @param(*anim)		�A�j���[�V�����p�^�[���̃|�C���^
 * @param(animCount)	�A�j���[�V�����p�^�[���̍ő吔
 * @return		�Ȃ�
 *********************************************************************************************************/
void CAnimation::Create(ANIMATIONFRAME* anim, int animCount) {
	// �A�j���[�V�����p�^�[���̃|�C���^���Z�b�g
	m_pAnimFrame = anim;
	// �A�j���[�V�����p�^�[���̍ő吔���Z�b�g
	m_MAXAnimCount = animCount;
}

/*********************************************************************************************************
 * @fn
 * ���݂̃A�j���[�V�����p�^�[���̃t���[�������Z����֐�
 * @brief		�A�j���[�V�����t���[�����Z
 * @param()		�Ȃ�
 * @return		�Ȃ�
 *********************************************************************************************************/
void CAnimation::AddTimer() { 
	// �A�j���[�V�����p�^�[�������}�C�i�X�ɂȂ�Ȃ��悤�ɂ���
	if (m_AnimCount < 0) {
		m_AnimCount = 0;
	}

	// �A�j���[�V�����p�^�[���̍ő吔�𒴂��Ȃ��悤�ɂ���
	if (m_AnimCount >= m_MAXAnimCount) {
		m_AnimCount = m_MAXAnimCount;
	}

	// �A�j���[�V�����ҋ@�t���[�����Z
	m_NowWait++;

	// �A�j���[�V�����̑ҋ@�t���[���𒴂��Ă����猻�݂̃A�j���[�V�����t���[�������Z����
	if (m_NowWait >= m_pAnimFrame[m_AnimCount].Pattern[m_NowFrame].Wait) {
		m_NowWait = 0;
		m_NowFrame++;
		// ���[�v�t���O�������Ă���΃A�j���[�V�����t���[����������
		if (m_NowFrame >= m_FrameCount) {
			m_NowFrame = m_pAnimFrame[m_AnimCount].bLoop ? 0 : m_FrameCount;
		}
	}
}

/*********************************************************************************************************
 * @fn
 * ���݂̃A�j���[�V�����̋�`���擾����֐�
 * @brief		���݂̃A�j���[�V������`�擾
 * @param()		�Ȃ�
 * @return		���݂̃A�j���[�V������`
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
