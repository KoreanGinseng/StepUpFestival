/*************************************************************************//*!

					@file	EffectManager.cpp
					@brief	�G�t�F�N�g�}�l�[�W���[�N���X

															@author	���̂���
															@date	2020.02.21
*//**************************************************************************/

//INCLUDE
#include "EffectManager.h"
#include "GraphicsUtillities.h"
#include "GameDefine.h"

namespace DxLibPlus
{
	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <returns>None</returns>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	CEffectManager::CEffectManager(void) :
		m_EffectList(),
		m_PlayType(SKILL_FIRE)
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
	CEffectManager::~CEffectManager(void)
	{
		Release();
	}
	// ********************************************************************************
	/// <summary>
	/// �}�l�[�W���[�̎擾
	/// </summary>
	/// <returns>�}�l�[�W���[</returns>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	CEffectManager & CEffectManager::GetEffectManager(void)
	{
		static CEffectManager manager;
		return manager;
	}
	// ********************************************************************************
	/// <summary>
	/// �G�t�F�N�g�̍쐬
	/// </summary>
	/// <param name="type">�G�t�F�N�g�̃^�C�v</param>
	/// <param name="pAnim">�A�j���[�V�����\����</param>
	/// <param name="animCount">�A�j���[�V������</param>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CEffectManager::CreateEffect(const SkillType & type, Animation<10>* pAnim, const int & animCount)
	{
		m_EffectList[type].Create(pAnim, animCount);
	}
	// ********************************************************************************
	/// <summary>
	/// �G�t�F�N�g�J�n
	/// </summary>
	/// <param name="type">�J�n����G�t�F�N�g�^�C�v</param>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CEffectManager::Start(const SkillType & type)
	{
		m_EffectList[type].SetShow(true);
		m_EffectList[type].ChangeMotion(0);
		m_PlayType = type;
	}
	// ********************************************************************************
	/// <summary>
	/// �G�t�F�N�g�̍X�V
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CEffectManager::Update(void)
	{
		//�S����
		for (auto& itr : m_EffectList)
		{
			//�\���t���O�������ĂȂ���̓X�L�b�v
			if (!itr.second.IsShow())
			{
				continue;
			}
			//�A�j���[�V�����X�V
			itr.second.AddTimer();
			//�A�j���[�V�������I�����Ă���Ε\���t���O�����Ƃɖ߂�
			if (itr.second.IsEndMotion())
			{
				itr.second.SetShow(false);
			}
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �G�t�F�N�g�̕`��
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CEffectManager::Render(void)
	{
		//�\���t���O�������ĂȂ���͕\�����Ȃ�
		if (!m_EffectList[m_PlayType].IsShow())
		{
			return;
		}
		//�\������G�t�F�N�g���擾����
		TextureKey texKey;
		switch (m_PlayType)
		{
		case SKILL_FIRE:
			texKey = TEXKEY_EFFECT_FIRE;
			break;
		case SKILL_ICE:
			texKey = TEXKEY_EFFECT_ICE;
			break;
		case SKILL_SLASH:
			texKey = TEXKEY_EFFECT_SLASH;
			break;
		case SKILL_THUNDER:
			texKey = TEXKEY_EFFECT_THUNDER;
			break;
		}
		//�摜�n���h���擾
		int graphHandle = theTextureManager.GetGraphHandle(TexFile[texKey].key);
		//�\���ʒu�𒆉��ɂ���
		float x = (CGraphicsUtillities::GetTargetWidth() - 192) * 0.5f;
		//��`�擾
		Rectangle rect = m_EffectList[m_PlayType].GetSrcRect();
		//�摜�̋�`�����̂ݕ\��(�A�j���[�V����)
		DxLib::DrawRectGraph(static_cast<int>(x), PlayerRectW, rect.left, rect.top, rect.GetWidth(), rect.GetHeight(), graphHandle, true);
	}
	// ********************************************************************************
	/// <summary>
	/// ���
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CEffectManager::Release(void)
	{
		for (auto& itr : m_EffectList)
		{
			itr.second.Release();
		}
		m_EffectList.clear();
	}
}