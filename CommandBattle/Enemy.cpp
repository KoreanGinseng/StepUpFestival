/*************************************************************************//*!

					@file	Enemy.cpp
					@brief	�G�N���X

															@author	���̂���
															@date	2020.02.21
*//**************************************************************************/

//INCLUDE
#include "Enemy.h"

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
	CEnemy::CEnemy(void) :
		CChara(),
		m_Type(ENE_RED)
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
	CEnemy::~CEnemy(void)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// �ǂݍ���
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	bool CEnemy::Load(void)
	{
		//�t�@�C�����J��
		std::wifstream ifs("EnemyStatus.txt", std::ios::in);
		//�J���Ȃ��ꍇerror
		if (!ifs)
		{
			return false;
		}
		//�t�@�C���̏I�[�܂œǂݍ���
		ifs.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
		std::wstring wstr((std::istreambuf_iterator<wchar_t>(ifs)), std::istreambuf_iterator<wchar_t>());
		std::string buff = CDxLibUtillities::WStringToString(wstr);
		int length = buff.length();
		int indentCnt = 0;
		int strlen = 0;
		std::string str = "";
		while (length > indentCnt && strlen >= 0)
		{
			//���s��؂�ŕ�����擾
			strlen = buff.find_first_of("\n", indentCnt) - indentCnt;
			str = buff.substr(indentCnt, strlen);
			indentCnt += strlen + 1;
			//�X�e�[�^�X�R�}���h�̏ꍇ
			if (str == "status")
			{
				//HP�̎擾
				strlen = buff.find_first_of("\n", indentCnt) - indentCnt;
				str = buff.substr(indentCnt, strlen);
				indentCnt += strlen + 1;
				m_Status.hp = std::atoi(str.c_str());
				m_OffsetHp = m_Status.hp;
				//ATTACK�̎擾
				strlen = buff.find_first_of("\n", indentCnt) - indentCnt;
				str = buff.substr(indentCnt, strlen);
				indentCnt += strlen + 1;
				m_Status.attack = std::atoi(str.c_str());
			}
		}
		return true;
	}
	// ********************************************************************************
	/// <summary>
	/// ������
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CEnemy::Initialize(void)
	{
		//�G�̎�ނ������_���Ō��߂�
		m_Type = static_cast<EnemyType>(CDxLibUtillities::Random(ENE_COUNT) - 1);
		//�摜�̃L�[���擾���Ă���
		m_TexKey;
		switch (m_Type)
		{
		case ENE_RED:
			m_TexKey = TEXKEY_DRAGON_RED;
			break;
		case ENE_GREEN:
			m_TexKey = TEXKEY_DRAGON_GREEN;
			break;
		case ENE_BLUE:
			m_TexKey = TEXKEY_DRAGON_BLUE;
			break;
		case ENE_KOMODO:
			m_TexKey = TEXKEY_DRAGON_KOMODO;
			break;
		}
		//�摜�n���h�����擾����
		m_GraphHandle = theTextureManager.GetGraphHandle(TexFile[m_TexKey].key);
		//���S�t���O�̏�����
		m_bDead = false;
		//�̗͂̃Z�b�g
		m_Status.hp = m_OffsetHp;
		//�_���[�W�ҋ@���Ԃ̏�����
		m_DamageWait = 0;
	}
	// ********************************************************************************
	/// <summary>
	/// �X�V
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CEnemy::Update(void)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// �`��
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CEnemy::Render(void)
	{
		//�_���[�W��������Ă���Ԃ������́A����ł���Ε\�����Ȃ�
		if ((m_DamageWait % 3 == 1) || (m_bDead && m_DamageWait <= 0))
		{
			return;
		}
		//�\���ʒu�v�Z(������)
		float x = (CGraphicsUtillities::GetTargetWidth() - theTextureManager.GetWidth(TexFile[m_TexKey].key)) * 0.5f;
		//�h���S���̕`��
		DxLib::DrawGraph(static_cast<int>(x), PlayerRectH, m_GraphHandle, true);
	}
}

