/*************************************************************************//*!

					@file	Animation.h
					@brief	�A�j���[�V�����N���X

															@author	���̂���
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
	/// �A�j���[�V�����p�^�[���\����
	/// </summary>
	// ********************************************************************************
	struct Pattern {
		int		wait;				//!<�҂��t���[��
		int		no;					//!<��
		int		step;				//!<�c
	};
	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����쐬�p�\����
	/// </summary>
	// ********************************************************************************
	template< int N > struct Animation {
		std::string	name;			//!<�A�j���[�V������
		int			offsetX;		//!<�摜�I�t�Z�b�gX
		int			offsetY;		//!<�摜�I�t�Z�b�gY
		int			width;			//!<�A�j���[�V������
		int			height;			//!<�A�j���[�V��������
		bool		bLoop;			//!<����
		Pattern		pattern[N];		//!<�A�j���[�V�����p�^�[��
	};
	// ********************************************************************************
	/// <summary>
	/// ��`�\����
	/// </summary>
	// ********************************************************************************
	struct Rectangle {
		int		left;				//!<��
		int		top;				//!<��
		int		right;				//!<�E
		int		bottom;				//!<��
		// ********************************************************************************
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <returns>None</returns>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
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
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="l">��</param>
		/// <param name="t">��</param>
		/// <param name="r">�E</param>
		/// <param name="b">��</param>
		/// <returns></returns>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
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
		/// �����擾
		/// </summary>
		/// <returns>��`�̉���</returns>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		int GetWidth(void) const
		{
			return right - left;
		}
		// ********************************************************************************
		/// <summary>
		/// �c���擾
		/// </summary>
		/// <returns>��`�̏c��</returns>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		int GetHeight(void) const
		{
			return bottom - top;
		}
	};

	// ********************************************************************************
	/// <summary>
	/// �A�j���[�V�����N���X
	/// </summary>
	// ********************************************************************************
	template< int N > class CAnimation
	{
	private:
		int				m_NowFlame;			//!<���݂̃A�j���[�V�����t���[��
		int				m_NowWait;			//!<�ҋ@�t���[��
		int				m_FlameCount;		//!<�A�j���[�V�����t���[���ő吔
		int				m_NowAnimNo;		//!<���ݍĐ����̃A�j���[�V�����ԍ�
		int				m_MaxAnimCount;		//!<�A�j���[�V�����ő吔
		Animation<N>*	m_pAnim;			//!<�A�j���[�V�����\���̔z��
		bool			m_bShow;			//!<�\���t���O
	public:
		// ********************************************************************************
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <returns>None</returns>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
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
		/// �f�X�g���N�^
		/// </summary>
		/// <returns>None</returns>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		~CAnimation(void) { Release(); }
		// ********************************************************************************
		/// <summary>
		/// �A�j���[�V�����ύX
		/// </summary>
		/// <param name="animNo">�ύX����ԍ�</param>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
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
		/// �A�j���[�V�����̍쐬
		/// </summary>
		/// <param name="anim">�쐬����\����</param>
		/// <param name="animCount">�A�j���[�V�����̐�</param>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		void Create(Animation<N>* anim, const int& animCount)
		{
			//�K�v���쐬����
			m_pAnim = new Animation<N>[animCount];
			//�f�[�^�̃R�s�[
			*m_pAnim = *anim;
			//�ő吔�̃Z�b�g
			m_MaxAnimCount = animCount;
		}
		// ********************************************************************************
		/// <summary>
		/// ���
		/// </summary>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
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
		/// �A�j���[�V������i�߂�
		/// </summary>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
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
		/// ���[�V�����I���t���O�擾
		/// </summary>
		/// <returns>�I���t���O</returns>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		bool IsEndMotion(void) const
		{
			return m_pAnim->bLoop ? false : (m_NowFlame >= m_FlameCount);
		}
		// ********************************************************************************
		/// <summary>
		/// �A�j���[�V�����̋�`�擾
		/// </summary>
		/// <returns>�A�j���[�V������`</returns>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
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
		/// �\���t���O�̐ݒ�
		/// </summary>
		/// <param name="b">�\���t���O</param>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		void SetShow(const bool& b)
		{
			m_bShow = b;
		}
		// ********************************************************************************
		/// <summary>
		/// �\���t���O�̎擾
		/// </summary>
		/// <returns>�\���t���O</returns>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		bool IsShow(void) const
		{
			return m_bShow;
		}
	};
}

