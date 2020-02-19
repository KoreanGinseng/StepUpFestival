#include "Player.h"

std::string gCommandList[] = {
	"��������",
	"�Ƃ���",
	"�ǂ���",
};

namespace DxLibPlus
{
	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <returns>None</returns>
	/// <created>���̂���,2020/02/17</created>
	/// <changed>���̂���,2020/02/17</changed>
	// ********************************************************************************
	CPlayer::CPlayer(void) :
		CChara(),
		m_Cursor(0),
		m_State(COMMAND_WAIT)
	{
	}

	// ********************************************************************************
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <returns>None</returns>
	/// <created>���̂���,2020/02/17</created>
	/// <changed>���̂���,2020/02/17</changed>
	// ********************************************************************************
	CPlayer::~CPlayer(void)
	{
	}

	// ********************************************************************************
	/// <summary>
	/// �ǂݍ���
	/// </summary>
	/// <returns>true  ����</param>
	/// 			 false ���s</returns>
	/// <created>���̂���,2020/02/17</created>
	/// <changed>���̂���,2020/02/17</changed>
	// ********************************************************************************
	bool CPlayer::Load(void)
	{
		//�t�@�C�����J��
		FILE* fp = fopen("PlayerStatus.txt", "rt");
		//�J���Ȃ������ꍇerror
		if (fp == NULL)
		{
			return false;
		}
		//���������荞��
		std::string buff;
		//�X�e�[�^�X����ǂݍ���
		fscanf(fp, "%s,", buff);	//status,
		if (buff == "status")
		{
			//�̗͍U���̏��Ԃœǂ�
			fscanf(fp, "%d,", &m_Status.hp);
			fscanf(fp, "%d,", &m_Status.attack);
		}
		//�擪�ɃX�e�[�^�X���L�q����Ă��Ȃ��ꍇerror
		else
		{
			fclose(fp);
			return false;
		}
		//�X�L����ǂݍ���
		fscanf(fp, "%s,", buff);	//skill,
		if (buff == "skill")
		{
			//�X�L���̐����擾����
			int skillCnt;
			fscanf(fp, "%d,", &skillCnt);
			//�X�L���̐������ǂݍ���
			for (int i = 0; i < skillCnt; i++)
			{
				Skill addData;
				fscanf(fp, "%s,", &addData.name);
				fscanf(fp, "%f,", &addData.rate);
				fscanf(fp, "%s,", buff);
				addData.effect = (buff == "FIRE") ? SKILL_FIRE : (buff == "ICE") ? SKILL_ICE : SKILL_THUNDER;
				m_SkillList.push_back(addData);
			}
		}
		fclose(fp);
		return true;
	}

	// ********************************************************************************
	/// <summary>
	/// ������
	/// </summary>
	/// <created>���̂���,2020/02/17</created>
	/// <changed>���̂���,2020/02/17</changed>
	// ********************************************************************************
	void CPlayer::Initialize(void)
	{
		m_Cursor = 0;
		m_State = COMMAND_WAIT;
	}

	// ********************************************************************************
	/// <summary>
	/// �X�V
	/// </summary>
	/// <created>���̂���,2020/02/19</created>
	/// <changed>���̂���,2020/02/19</changed>
	// ********************************************************************************
	void CPlayer::Update(void)
	{
		//��L�[����������I������ɂ���
		if (DxLib::CheckHitKey(KEY_INPUT_UP))
		{
			m_Cursor--;
		}
		//���L�[����������I�������ɂ���
		else if (DxLib::CheckHitKey(KEY_INPUT_DOWN))
		{
			m_Cursor++;
		}
		//�I���ł���ő�
		int listmax = 0;
		//��Ԃ��Ƃɑ����ς���
		switch (m_State)
		{
		case COMMAND_ATTACK:
		case COMMAND_WAIT:
			listmax = 2;
			break;
		case COMMAND_SKILL:
			listmax = static_cast<int>(m_SkillList.size());
			break;
		default:
			break;
		}
		//�I�����g�O�ɍs���Ȃ��悤�ɂ���
		if (m_Cursor < 0)
		{
			m_Cursor = listmax;
		}
		else if (m_Cursor > listmax)
		{
			m_Cursor = 0;
		}
		//��Ԃ��ƂɃG���^�[�L�[���������Ƃ��̑���𕪂���
		if (DxLib::CheckHitKey(KEY_INPUT_RETURN))
		{
			switch (m_State)
			{
			case COMMAND_WAIT:
				m_State = static_cast<CommandState>(m_Cursor + 1);
				if (m_State == COMMAND_ATTACK)
				{
					m_AttackRate = 1.0f;
					theTurnManager.SetTurn(TURN_ENEMY);
				}
				break;
			case COMMAND_SKILL:
				m_State = COMMAND_ATTACK;
				m_AttackRate = m_SkillList[m_Cursor].rate;
				break;
			default:
				break;
			}
		}
	}

	// ********************************************************************************
	/// <summary>
	/// �`��
	/// </summary>
	/// <created>���̂���,2020/02/19</created>
	/// <changed>���̂���,2020/02/19</changed>
	// ********************************************************************************
	void CPlayer::Render(void)
	{
		switch (m_State)
		{
		case COMMAND_WAIT:
			for (int i = 0; i < 3; i++)
			{
				DxLib::DrawFormatString(CommandRectX, CommandRectY + i * 24, GetColor(255, 255, 255), "%s", gCommandList[i].c_str());
			}
			break;
		case COMMAND_ATTACK:
			break;
		case COMMAND_SKILL:
			break;
		case COMMAND_ITEM:
			break;
		default:
			break;
		}
	}

	// ********************************************************************************
	/// <summary>
	/// ���
	/// </summary>
	/// <created>���̂���,2020/02/19</created>
	/// <changed>���̂���,2020/02/19</changed>
	// ********************************************************************************
	void CPlayer::Release(void)
	{
		m_SkillList.clear();
	}
}

