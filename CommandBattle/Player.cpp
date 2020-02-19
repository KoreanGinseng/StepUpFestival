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
		std::wifstream ifs("PlayerStatus.txt", std::ios::in);
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
		while (length > indentCnt)
		{
			int strlen = buff.find_first_of("\n", indentCnt) - indentCnt;
			std::string str = buff.substr(indentCnt, strlen);
			indentCnt += strlen + 1;
			//�X�e�[�^�X�R�}���h�̏ꍇ
			if (str == "status")
			{

			}
			//�X�L���R�}���h�̏ꍇ
			else if (str == "skill")
			{
				Skill addData;
				addData.effect = (str == "FIRE") ? SKILL_FIRE : (str == "ICE") ? SKILL_ICE : SKILL_THUNDER;
				//�X�L���̓o�^
				m_SkillList.push_back(addData);
			}
		}
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
		//if (DxLib::CheckHitKey(KEY_INPUT_RETURN))
		if (theInput.IsKeyPush(KEY_INPUT_RETURN))
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
				DxLib::DrawFormatString(CommandRectX + 24, CommandRectY + i * 24 + 4 + i * 4, GetColor(255, 255, 255), "%s", gCommandList[i].c_str());
			}
			break;
		case COMMAND_ATTACK:
			for (int i = 0; i < 3; i++)
			{
				DxLib::DrawFormatString(CommandRectX + 24, CommandRectY + i * 24 + 4 + i * 4, GetColor(128, 128, 128), "%s", gCommandList[i].c_str());
			}
			break;
		case COMMAND_SKILL:
			for (int i = 0; i < m_SkillList.size(); i++)
			{
				DxLib::DrawFormatString(CommandRectX + 24, CommandRectY + i * 24 + 4 + i * 4, GetColor(255, 255, 255), "%s", m_SkillList[i].name.c_str());
			}
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

