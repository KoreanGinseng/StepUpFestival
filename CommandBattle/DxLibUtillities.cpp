/*************************************************************************//*!

					@file	DxLibUtillities.h
					@brief	DxLib���[�e�B���e�B�N���X

															@author	���̂���
															@date	2020.02.14
*//**************************************************************************/

//INCLUDE
#include "DxLibUtillities.h"


namespace DxLibPlus
{
	/*************************************************************************//*!
			@brief			���C�u�����̏�����
			@param			None

			@return			0			����<br>
							-1			�G���[����
	*//**************************************************************************/
	int CDxLibUtillities::DxLibInit(void)
	{
		return DxLib::DxLib_Init();
	}
	/*************************************************************************//*!
			@brief			���C�u�����g�p�̏I��
			@param			None

			@return			0			����<br>
							-1			�G���[����
	*//**************************************************************************/
	int CDxLibUtillities::DxLibEnd(void)
	{
		return DxLib::DxLib_End();
	}
	/*************************************************************************//*!
			@brief			�E�B���h�E�̃��b�Z�[�W����������
			@param			None

			@return			0			����<br>
							-1			�G���[�����E�Ⴕ���̓E�B���h�E������ꂽ
	*//**************************************************************************/
	int CDxLibUtillities::ProcessMessage(void)
	{
		return DxLib::ProcessMessage();
	}
	/*************************************************************************//*!
			@brief			�w��̎��Ԃ����������~�߂�
			@param[in]		t			�~�߂鎞��(�~���b�P��)

			@return			0			����<br>
							-1			�G���[����
	*//**************************************************************************/
	int CDxLibUtillities::WaitTimer(const int & t)
	{
		return DxLib::WaitTimer(t);
	}
	/*************************************************************************//*!
			@brief			�������擾����
			@param[in]		max			�擾���闐���̍ő�l

			@return			0~�ő�l�܂ł̗���
	*//**************************************************************************/
	int CDxLibUtillities::Random(const int & max)
	{
		return DxLib::GetRand(max);
	}
	/*************************************************************************//*!
			@brief			�������擾����
			@param[in]		min			�擾���闐���̍ŏ��l
			@param[in]		max			�擾���闐���̍ő�l

			@return			�ŏ��l~�ő�l�܂ł̗���
	*//**************************************************************************/
	int CDxLibUtillities::Random(const int & min, const int & max)
	{
		return DxLib::GetRand(max - min) + min;
	}
	/*************************************************************************//*!
			@brief			�������擾����
			@param			None

			@return			0.0f~1.0f�܂ł̗���(���񌅂܂�)
	*//**************************************************************************/
	float CDxLibUtillities::RandomFloat(void)
	{
		return static_cast<float>(DxLib::GetRand(100)) * 0.01f;
	}
	/*************************************************************************//*!
			@brief			�����̏����l��ݒ肷��
			@param[in]		seed		�����̏����l

			@return			0			����<br>
							-1			�G���[����
	*//**************************************************************************/
	int CDxLibUtillities::SetRandom(const int & seed)
	{
		return DxLib::SRand(seed);
	}
	// ********************************************************************************
	/// <summary>
	/// wstring��string�֕ϊ�
	/// </summary>
	/// <param name="oWString">���C�h������</param>
	/// <returns>�}���`�o�C�g������</returns>
	/// <created>���̂���,2020/02/19</created>
	/// <changed>���̂���,2020/02/19</changed>
	// ********************************************************************************
	std::string CDxLibUtillities::WStringToString(std::wstring oWString)
	{
		// wstring �� SJIS
		int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str()
			, -1, (char *)NULL, 0, NULL, NULL);

		// �o�b�t�@�̎擾
		CHAR* cpMultiByte = new CHAR[iBufferSize];

		// wstring �� SJIS
		WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, cpMultiByte
			, iBufferSize, NULL, NULL);

		// string�̐���
		std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);

		// �o�b�t�@�̔j��
		delete[] cpMultiByte;

		// �ϊ����ʂ�Ԃ�
		return(oRet);
	}
}