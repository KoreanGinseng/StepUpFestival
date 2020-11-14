/*************************************************************************//*!

					@file	DxLibUtillities.h
					@brief	DxLib���[�e�B���e�B�N���X

															@author	���̂���
															@date	2020.02.14
*//**************************************************************************/

//INCLUDE
#include "DxLibUtilities.h"


namespace DxLibPlus
{
	// ********************************************************************************
	/// <summary>
	/// ���C�u�����̏�����
	/// </summary>
	/// <returns>����(0)���G���[(-1)</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	int CDxLibUtilities::DxLibInit(void)
	{
		return DxLib::DxLib_Init();
	}
	// ********************************************************************************
	/// <summary>
	/// ���C�u�����g�p�̏I��
	/// </summary>
	/// <returns>����(0)���G���[(-1)</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	int CDxLibUtilities::DxLibEnd(void)
	{
		return DxLib::DxLib_End();
	}
	// ********************************************************************************
	/// <summary>
	/// �E�B���h�E�̃��b�Z�[�W����������
	/// </summary>
	/// <returns>����(0)���G���[(-1)</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	int CDxLibUtilities::ProcessMessage(void)
	{
		return DxLib::ProcessMessage();
	}
	// ********************************************************************************
	/// <summary>
	/// �w��̎��Ԃ����������~�߂�
	/// </summary>
	/// <param name="t">�~�߂鎞��(�~���b�P��)</param>
	/// <returns>����(0)���G���[(-1)</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	int CDxLibUtilities::WaitTimer(const int & t)
	{
		return DxLib::WaitTimer(t);
	}
	// ********************************************************************************
	/// <summary>
	/// �������擾����
	/// </summary>
	/// <param name="max">�擾���闐���̍ő�l</param>
	/// <returns>0~�ő�l�܂ł̗���</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	int CDxLibUtilities::Random(const int & max)
	{
		return DxLib::GetRand(max);
	}
	// ********************************************************************************
	/// <summary>
	/// �������擾����
	/// </summary>
	/// <param name="min">�擾���闐���̍ŏ��l</param>
	/// <param name="max">�擾���闐���̍ő�l</param>
	/// <returns>�ŏ��l~�ő�l�܂ł̗���</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	int CDxLibUtilities::Random(const int & min, const int & max)
	{
		return DxLib::GetRand(max - min) + min;
	}
	// ********************************************************************************
	/// <summary>
	/// �������擾����
	/// </summary>
	/// <returns>0.0f~1.0f�܂ł̗���(���񌅂܂�)</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	float CDxLibUtilities::RandomFloat(void)
	{
		return static_cast<float>(DxLib::GetRand(100)) * 0.01f;
	}
	// ********************************************************************************
	/// <summary>
	/// �����̏����l��ݒ肷��
	/// </summary>
	/// <param name="seed">�����̏����l</param>
	/// <returns>����(0)���G���[(-1)</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	int CDxLibUtilities::SetRandom(const int & seed)
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
	std::string CDxLibUtilities::WStringToString(std::wstring oWString)
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
	// ********************************************************************************
	/// <summary>
	/// �����񕪊�
	/// </summary>
	/// <param name="buff">�������镶����</param>
	/// <param name="spa">��������L�[</param>
	/// <param name="outstrlen">�����o��</param>
	/// <param name="outindent">������C���f���g�o��</param>
	/// <returns>�����㕶����</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	std::string CDxLibUtilities::GetSpalateString(const std::string & buff, const std::string & spa, int & outstrlen, int & outindent)
	{
		std::string re = "";
		outstrlen = buff.find_first_of("\n", outindent) - outindent;
		re = buff.substr(outindent, outstrlen);
		outindent += outstrlen + 1;
		return re;
	}
}