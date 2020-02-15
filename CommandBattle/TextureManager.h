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
	/*******************************//*!
	@brief	�e�N�X�`���ǂݍ��ݍ\����

	@author	���̂���
	*//********************************/
	typedef struct tag_TEXMNGINFO {
		std::string	key;	//!<�����p�L�[
		std::string	file;	//!<�ǂݍ��݃t�@�C����
	}TexMngInfo;

	/*******************************//*!
	@brief	�e�N�X�`���Ǘ��N���X

	@author	���̂���
	*//********************************/
	class CTextureManager
	{
	private:
		std::unordered_map<std::string, int>	m_GraphHandleList;	//!<�O���t�B�b�N�n���h��

		/*************************************************************************//*!
				@brief			�R���X�g���N�^
				@param			None

				@return			None
		*//**************************************************************************/
		CTextureManager(void);
		/*************************************************************************//*!
				@brief			�f�X�g���N�^
				@param			None

				@return			None
		*//**************************************************************************/
		~CTextureManager(void);
	public:
		/*************************************************************************//*!
				@brief			�}�l�[�W���[�Ăяo��
				@param			None

				@return			�}�l�[�W���[
		*//**************************************************************************/
		static CTextureManager& GetTextureManager(void);
		/*************************************************************************//*!
				@brief			�摜�t�@�C���̃n���h�����擾����
				@param[in]		name		�o�^�L�[��

				@return			-1			�G���[����<br>
								-1�ȊO		�O���t�B�b�N�̃n���h��
		*//**************************************************************************/
		int GetGraphHandle(const std::string& name);
		/*************************************************************************//*!
				@brief			�摜�t�@�C���̓ǂݍ���
				@param[in]		name		�o�^�L�[��
				@param[in]		fileName	�摜�t�@�C����

				@return			-1			�G���[����<br>
								-1�ȊO		�O���t�B�b�N�̃n���h��
		*//**************************************************************************/
		int LoadGraph(const std::string& name, const std::string& fileName);
		/*************************************************************************//*!
				@brief			�摜�t�@�C���̉������擾����
				@param[in]		name		�o�^�L�[��

				@return			�摜��
		*//**************************************************************************/
		int GetWidth(const std::string& name) const;
		/*************************************************************************//*!
				@brief			�摜�t�@�C���̏c�����擾����
				@param[in]		name		�o�^�L�[��

				@return			�摜����
		*//**************************************************************************/
		int GetHeight(const std::string& name) const;
		/*************************************************************************//*!
				@brief			�摜�t�@�C���̈ꊇ�ǂݍ��݂���
				@param[in]		list		�ǂݍ��݃��X�g
				@param[in]		cnt			���X�g�̔z��

				@return			None
		*//**************************************************************************/
		void LoadList(TexMngInfo* list, const int& cnt);
	};

#define	theTextureManager	CTextureManager::GetTextureManager()
}