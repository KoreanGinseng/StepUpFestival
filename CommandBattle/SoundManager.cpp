/*************************************************************************//*!

					@file	SoundManager.cpp
					@brief	�T�E���h�Ǘ��N���X

															@author	���̂���
															@date	2020.02.21
*//**************************************************************************/

//INCLUDE
#include "SoundManager.h"

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
	CSoundManager::CSoundManager(void) :
		m_List()
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
	CSoundManager::~CSoundManager(void)
	{
		Release();
	}
	// ********************************************************************************
	/// <summary>
	/// �}�l�[�W���擾
	/// </summary>
	/// <returns>�}�l�[�W��</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	CSoundManager & CSoundManager::GetSoundManager(void)
	{
		static CSoundManager manager;
		return manager;
	}
	// ********************************************************************************
	/// <summary>
	/// �ǂݍ���
	/// </summary>
	/// <param name="key">�Ăяo���p�L�[</param>
	/// <param name="file">�t�@�C����</param>
	/// <returns>����(0)�����s(-1)</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	bool CSoundManager::Load(const std::string & key, const std::string & file)
	{
		return m_List[key].Load(file);
	}
	// ********************************************************************************
	/// <summary>
	/// �Đ�����
	/// </summary>
	/// <param name="key">�Ăяo���p�L�[</param>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	void CSoundManager::Play(const std::string & key)
	{
		m_List[key].Play();
	}
	// ********************************************************************************
	/// <summary>
	/// �Đ������ǂ����`�F�b�N����
	/// </summary>
	/// <param name="key">�Ăяo���p�L�[</param>
	/// <returns>�Đ������ǂ����̃t���O</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	bool CSoundManager::IsPlay(const std::string & key)
	{
		return m_List[key].IsPlay();
	}
	// ********************************************************************************
	/// <summary>
	/// �~�߂�
	/// </summary>
	/// <param name="key">�Ăяo���p�L�[</param>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	void CSoundManager::Stop(const std::string & key)
	{
		m_List[key].Stop();
	}
	// ********************************************************************************
	/// <summary>
	/// ���ׂẲ����~�߂�
	/// </summary>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	void CSoundManager::Stop(void)
	{
		for (auto& itr : m_List)
		{
			itr.second.Stop();
		}
	}
	// ********************************************************************************
	/// <summary>
	/// ���[�v�ݒ�
	/// </summary>
	/// <param name="key">�Ăяo���p�L�[</param>
	/// <param name="b">���[�v�t���O</param>
	/// <param name="time">���[�v����J�n����(�~���b)</param>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	void CSoundManager::SetLoop(const std::string & key, const bool & b, const int& time)
	{
		m_List[key].SetLoop(b, time);
	}
	// ********************************************************************************
	/// <summary>
	/// ���
	/// </summary>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	void CSoundManager::Release(void)
	{
		DxLib::InitSoundMem();
	}
}