#include "TextureManager.h"


namespace DxLibPlus
{
	/*************************************************************************//*!
			@brief			�R���X�g���N�^
			@param			None

			@return			None
	*//**************************************************************************/
	CTextureManager::CTextureManager(void) :
		m_GraphHandleList()
	{
	}
	/*************************************************************************//*!
			@brief			�f�X�g���N�^
			@param			None

			@return			None
	*//**************************************************************************/
	CTextureManager::~CTextureManager(void)
	{
		for (auto& itr : m_GraphHandleList)
		{
			DxLib::DeleteGraph(itr.second);
		}
	}
	/*************************************************************************//*!
			@brief			�}�l�[�W���[�Ăяo��
			@param			None

			@return			�}�l�[�W���[
	*//**************************************************************************/
	CTextureManager & CTextureManager::GetTextureManager(void)
	{
		static CTextureManager manager;
		return manager;
	}
	/*************************************************************************//*!
			@brief			�摜�t�@�C���̃n���h���擾
			@param[in]		name		�o�^�L�[��

			@return			-1			�G���[����<br>
							-1�ȊO		�O���t�B�b�N�̃n���h��
	*//**************************************************************************/
	int CTextureManager::GetGraphHandle(const std::string & name)
	{
		return m_GraphHandleList[name];
	}
	/*************************************************************************//*!
			@brief			�摜�t�@�C���̓ǂݍ���
			@param[in]		name		�o�^�L�[��
			@param[in]		fileName	�摜�t�@�C����

			@return			-1			�G���[����<br>
							-1�ȊO		�O���t�B�b�N�̃n���h��
	*//**************************************************************************/
	int CTextureManager::LoadGraph(const std::string & name, const std::string & fileName)
	{
		m_GraphHandleList[name] = DxLib::LoadGraph(fileName.c_str());
		return m_GraphHandleList[name];
	}
	/*************************************************************************//*!
			@brief			�摜�t�@�C���̉������擾����
			@param[in]		name		�o�^�L�[��

			@return			�摜��
	*//**************************************************************************/
	int CTextureManager::GetWidth(const std::string & name) const
	{
		int w, h, handle;
		handle = theTextureManager.GetGraphHandle(name);
		DxLib::GetGraphSize(handle, &w, &h);
		return w;
	}
	/*************************************************************************//*!
			@brief			�摜�t�@�C���̏c�����擾����
			@param[in]		name		�o�^�L�[��

			@return			�摜����
	*//**************************************************************************/
	int CTextureManager::GetHeight(const std::string & name) const
	{
		int w, h, handle;
		handle = theTextureManager.GetGraphHandle(name);
		DxLib::GetGraphSize(handle, &w, &h);
		return h;
	}
	/*************************************************************************//*!
			@brief			�摜�t�@�C���̈ꊇ�ǂݍ��݂���
			@param[in]		list		�ǂݍ��݃��X�g
			@param[in]		cnt			���X�g�̔z��

			@return			None
	*//**************************************************************************/
	void CTextureManager::LoadList(TexMngInfo * list, const int & cnt)
	{
		for (int i = 0; i < cnt; i++)
		{
			theTextureManager.LoadGraph(list[i].key, list[i].file);
		}
	}
}
