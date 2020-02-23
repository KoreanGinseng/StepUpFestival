/*************************************************************************//*!

					@file	Sound.cpp
					@brief	�T�E���h�N���X

															@author	���̂���
															@date	2020.02.21
*//**************************************************************************/

//INCLUDE
#include "Sound.h"

namespace DxLibPlus
{
	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <returns>None</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	CSound::CSound(void) :
		m_SoundHandle(0),
		m_bLoop(false)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <returns>None</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	CSound::~CSound(void)
	{
		Release();
	}
	// ********************************************************************************
	/// <summary>
	/// �ǂݍ���
	/// </summary>
	/// <param name="file">�t�@�C����</param>
	/// <returns></returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	bool CSound::Load(const std::string & file)
	{
		m_SoundHandle = DxLib::LoadSoundMem(file.c_str());
		if (m_SoundHandle == -1)
		{
			return false;
		}
		return true;
	}
	// ********************************************************************************
	/// <summary>
	/// �Đ�����
	/// </summary>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	void CSound::Play(void)
	{
		int playType = m_bLoop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK;
		DxLib::PlaySoundMem(m_SoundHandle, playType);
	}
	// ********************************************************************************
	/// <summary>
	/// �Đ������`�F�b�N����
	/// </summary>
	/// <returns>�Đ������ǂ����̃t���O</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	bool CSound::IsPlay(void) const
	{
		return DxLib::CheckSoundMem(m_SoundHandle) ? true : false;
	}
	// ********************************************************************************
	/// <summary>
	/// �~�߂�
	/// </summary>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	void CSound::Stop(void)
	{
		DxLib::StopSoundMem(m_SoundHandle);
	}
	// ********************************************************************************
	/// <summary>
	/// ���[�v�ݒ�
	/// </summary>
	/// <param name="b">���[�v�t���O</param>
	/// <param name="loopTime">���[�v�Đ�����J�n����(�~���b)</param>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	void CSound::SetLoop(const bool & b, const int& loopTime)
	{
		m_bLoop = b;
		DxLib::SetLoopPosSoundMem(loopTime, m_SoundHandle);
	}
	// ********************************************************************************
	/// <summary>
	/// ���
	/// </summary>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	void CSound::Release(void)
	{
		DxLib::DeleteSoundMem(m_SoundHandle);
	}
}
