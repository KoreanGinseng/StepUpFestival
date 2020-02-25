/*************************************************************************//*!

					@file	TextureManager.cpp
					@brief	�e�N�X�`���Ǘ��N���X

															@author	���̂���
															@date	2020.02.15
*//**************************************************************************/

//INCLUDE
#include "TextureManager.h"


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
	CTextureManager::CTextureManager(void) :
		m_GraphHandleList()
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
	CTextureManager::~CTextureManager(void)
	{
		for (auto& itr : m_GraphHandleList)
		{
			DxLib::DeleteGraph(itr.second);
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �}�l�[�W���[�Ăяo��
	/// </summary>
	/// <returns>�}�l�[�W���[</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	CTextureManager & CTextureManager::GetTextureManager(void)
	{
		static CTextureManager manager;
		return manager;
	}
	// ********************************************************************************
	/// <summary>
	/// �摜�t�@�C���̃n���h�����擾����
	/// </summary>
	/// <param name="name">�o�^�L�[��</param>
	/// <returns>�O���t�B�b�N�̃n���h��</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	int CTextureManager::GetGraphHandle(const std::string & name)
	{
		return m_GraphHandleList[name];
	}
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
	int CTextureManager::LoadGraph(const std::string & name, const std::string & fileName)
	{
		m_GraphHandleList[name] = DxLib::LoadGraph(fileName.c_str());
		return m_GraphHandleList[name];
	}
	// ********************************************************************************
	/// <summary>
	/// �摜�t�@�C���̉������擾����
	/// </summary>
	/// <param name="name">�o�^�L�[��</param>
	/// <returns>�摜��</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	int CTextureManager::GetWidth(const std::string & name) const
	{
		int w, h, handle;
		handle = theTextureManager.GetGraphHandle(name);
		DxLib::GetGraphSize(handle, &w, &h);
		return w;
	}
	// ********************************************************************************
	/// <summary>
	/// �摜�t�@�C���̏c�����擾����
	/// </summary>
	/// <param name="name">�o�^�L�[��</param>
	/// <returns>�摜����</returns>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	int CTextureManager::GetHeight(const std::string & name) const
	{
		int w, h, handle;
		handle = theTextureManager.GetGraphHandle(name);
		DxLib::GetGraphSize(handle, &w, &h);
		return h;
	}
	// ********************************************************************************
	/// <summary>
	/// �摜�t�@�C���̈ꊇ�ǂݍ��݂���
	/// </summary>
	/// <param name="list">�ǂݍ��݃��X�g</param>
	/// <param name="cnt">���X�g�̔z��</param>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	void CTextureManager::LoadList(TexMngInfo * list, const int & cnt)
	{
		for (int i = 0; i < cnt; i++)
		{
			theTextureManager.LoadGraph(list[i].key, list[i].file);
		}
	}
}
