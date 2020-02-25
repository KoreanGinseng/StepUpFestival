/*************************************************************************//*!

					@file	TextureManager.h
					@brief	�e�N�X�`���Ǘ��N���X

															@author	���̂���
															@date	2020.02.15
*//**************************************************************************/

//ONCE
#pragma once

//INCLUDE
#include	"DxLib.h"
#include	<unordered_map>
#include	<string>

namespace DxLibPlus
{
	//STRUCT
	// ********************************************************************************
	/// <summary>
	/// �e�N�X�`���ǂݍ��ݍ\����
	/// </summary>
	// ********************************************************************************
	typedef struct tag_TEXMNGINFO {
		std::string	key;	//!<�����p�L�[
		std::string	file;	//!<�ǂݍ��݃t�@�C����
	}TexMngInfo;

	// ********************************************************************************
	/// <summary>
	/// �e�N�X�`���Ǘ��N���X
	/// </summary>
	// ********************************************************************************
	class CTextureManager
	{
	private:
		std::unordered_map<std::string, int>	m_GraphHandleList;	//!<�O���t�B�b�N�n���h��

		// ********************************************************************************
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <returns>None</returns>
		/// <created>���̂���,2020/02/23</created>
		/// <changed>���̂���,2020/02/23</changed>
		// ********************************************************************************
		CTextureManager(void);
		// ********************************************************************************
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		/// <returns>None</returns>
		/// <created>���̂���,2020/02/23</created>
		/// <changed>���̂���,2020/02/23</changed>
		// ********************************************************************************
		~CTextureManager(void);
	public:
		// ********************************************************************************
		/// <summary>
		/// �}�l�[�W���[�Ăяo��
		/// </summary>
		/// <returns>�}�l�[�W���[</returns>
		/// <created>���̂���,2020/02/23</created>
		/// <changed>���̂���,2020/02/23</changed>
		// ********************************************************************************
		static CTextureManager& GetTextureManager(void);
		// ********************************************************************************
		/// <summary>
		/// �摜�t�@�C���̃n���h�����擾����
		/// </summary>
		/// <param name="name">�o�^�L�[��</param>
		/// <returns>�O���t�B�b�N�̃n���h��</returns>
		/// <created>���̂���,2020/02/23</created>
		/// <changed>���̂���,2020/02/23</changed>
		// ********************************************************************************
		int GetGraphHandle(const std::string& name);
		// ********************************************************************************
		/// <summary>
		/// �摜�t�@�C���̓ǂݍ���
		/// </summary>
		/// <param name="name">�o�^�L�[��</param>
		/// <param name="fileName">�摜�t�@�C����</param>
		/// <returns>�O���t�B�b�N�̃n���h��</returns>
		/// <created>���̂���,2020/02/23</created>
		/// <changed>���̂���,2020/02/23</changed>
		// ********************************************************************************
		int LoadGraph(const std::string& name, const std::string& fileName);
		// ********************************************************************************
		/// <summary>
		/// �摜�t�@�C���̉������擾����
		/// </summary>
		/// <param name="name">�o�^�L�[��</param>
		/// <returns>�摜��</returns>
		/// <created>���̂���,2020/02/23</created>
		/// <changed>���̂���,2020/02/23</changed>
		// ********************************************************************************
		int GetWidth(const std::string& name) const;
		// ********************************************************************************
		/// <summary>
		/// �摜�t�@�C���̏c�����擾����
		/// </summary>
		/// <param name="name">�o�^�L�[��</param>
		/// <returns>�摜����</returns>
		/// <created>���̂���,2020/02/23</created>
		/// <changed>���̂���,2020/02/23</changed>
		// ********************************************************************************
		int GetHeight(const std::string& name) const;
		// ********************************************************************************
		/// <summary>
		/// �摜�t�@�C���̈ꊇ�ǂݍ��݂���
		/// </summary>
		/// <param name="list">�ǂݍ��݃��X�g</param>
		/// <param name="cnt">���X�g�̔z��</param>
		/// <created>���̂���,2020/02/23</created>
		/// <changed>���̂���,2020/02/23</changed>
		// ********************************************************************************
		void LoadList(TexMngInfo* list, const int& cnt);
	};

#define	theTextureManager	CTextureManager::GetTextureManager()
}