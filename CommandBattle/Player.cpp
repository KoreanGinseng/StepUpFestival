#include "Player.h"

std::string gCommandList[] = {
	"��������",
	"�Ƃ���",
	"�ǂ���",
	"�Q�[���I��",
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
			//�X�L���R�}���h�̏ꍇ
			else if (str == "skill")
			{
				Skill addData;
				//�X�L�����擾
				strlen = buff.find_first_of("\n", indentCnt) - indentCnt;
				str = buff.substr(indentCnt, strlen);
				indentCnt += strlen + 1;
				addData.name = str;
				//�X�L���U���{���擾
				strlen = buff.find_first_of("\n", indentCnt) - indentCnt;
				str = buff.substr(indentCnt, strlen);
				indentCnt += strlen + 1;
				addData.rate = static_cast<float>(std::atof(str.c_str()));
				//�G�t�F�N�g�̎�ގ擾
				strlen = buff.find_first_of("\n", indentCnt) - indentCnt;
				str = buff.substr(indentCnt, strlen);
				indentCnt += strlen + 1;
				addData.effect = (str == "FIRE") ? SKILL_FIRE : (str == "ICE") ? SKILL_ICE : (str == "THUNDER") ? SKILL_THUNDER : SKILL_SLASH;
				//�X�L���̓o�^
				m_SkillList.push_back(addData);
			}
		}
		//�X�L����Ō�ɖ߂�R�}���h��ǉ�����
		Skill backCommand;
		backCommand.name = "�߂�";
		backCommand.rate = 0.0f;
		backCommand.effect = SKILL_SLASH;
		m_SkillList.push_back(backCommand);
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
		m_bDead = false;
		m_Status.hp = m_OffsetHp;
		m_Cursor = 0;
		m_State = COMMAND_WAIT;
		gMessage = "�ǂ�����H";
		m_DamageWait = 0;
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
		if (theInput.IsKeyPush(KEY_INPUT_UP))
		{
			m_Cursor--;
		}
		//���L�[����������I�������ɂ���
		else if (theInput.IsKeyPush(KEY_INPUT_DOWN))
		{
			m_Cursor++;
		}
		//���L�[����������I����1�y�[�W����ɂ���
		else if (theInput.IsKeyPush(KEY_INPUT_LEFT))
		{
			m_Cursor -= LineMax;
		}
		//�E�L�[����������I����1�y�[�W�����ɂ���
		else if (theInput.IsKeyPush(KEY_INPUT_RIGHT))
		{
			m_Cursor += LineMax;
		}
		//�I���ł���ő�
		int listmax = 0;
		//��Ԃ��Ƃɑ����ς���
		switch (m_State)
		{
		case COMMAND_ATTACK:
		case COMMAND_WAIT:
			listmax = 3;
			break;
		case COMMAND_SKILL:
			listmax = static_cast<int>(m_SkillList.size()) - 1;
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
		if (theInput.IsKeyPush(KEY_INPUT_RETURN))
		{
			switch (m_State)
			{
			case COMMAND_WAIT:
				m_State = static_cast<CommandState>(m_Cursor + 1);
				if (m_State == COMMAND_ATTACK)
				{
					m_AttackRate = 1.0f;
					theEffectManager.Start(SKILL_SLASH);
					theTurnManager.SetTurn(TURN_ENEMY);
					gMessage = "�v���C���[�̍U���I";
				}
				else if (m_State == COMMAND_EXIT)
				{
					PostQuitMessage(0);
				}
				else
				{
					m_Cursor = 0;
				}
				break;
			case COMMAND_SKILL:
				//�X�L���̈�ԍŌ�(�߂�R�}���h)�Ȃ��߂�
				if (m_Cursor == m_SkillList.size() - 1)
				{
					m_State = COMMAND_WAIT;
					break;
				}
				m_State = COMMAND_ATTACK;
				m_AttackRate = m_SkillList[m_Cursor].rate;
				theEffectManager.Start(m_SkillList[m_Cursor].effect);
				theTurnManager.SetTurn(TURN_ENEMY);
				gMessage = "�v���C���[��" + m_SkillList[m_Cursor].name + "�I";
				m_Cursor = 0;
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
		//�R�}���h�����̕\��
		unsigned int Color = DxLib::GetColor(255, 255, 255);
		int scroll = 0;
		switch (m_State)
		{
		case COMMAND_ATTACK:
			Color = DxLib::GetColor(128, 128, 128);
		case COMMAND_WAIT:
			if (m_bDead)
			{
				Color = DxLib::GetColor(192, 64, 64);
			}
			for (int i = 0; i < 4; i++)
			{
				DxLib::DrawFormatString(CommandRectX + FontSize, CommandRectY + i * (FontSize + FontMargin) + FontMargin, Color, "%s", gCommandList[i].c_str());
			}
			break;
		case COMMAND_SKILL:
			for (int i = 0; i < static_cast<int>(m_SkillList.size()); i++)
			{
				//�X�L�����X�g���\�����𒴂��Ă���ꍇ�y�[�W�؂�ւ��ł���悤�ɂ���
				int scrlCnt = (m_Cursor / LineMax);
				if (scrlCnt)
				{
					scroll = 0;
					scroll = ((FontSize + FontMargin) * LineMax) * scrlCnt;
					if (i < LineMax)
					{
						continue;
					}
				}
				DxLib::DrawFormatString(CommandRectX + FontSize, CommandRectY + i * (FontSize + FontMargin) + FontMargin - scroll, Color, "%s", m_SkillList[i].name.c_str());
			}
			break;
		case COMMAND_ITEM:
			break;
		default:
			break;
		}
		int cursorGraph = theTextureManager.GetGraphHandle(TexFile[TEXKEY_CURSOR].key);
		DxLib::DrawGraph(CommandRectX, CommandRectY + m_Cursor * (FontSize + FontMargin) + FontMargin - scroll, cursorGraph, true);
	}

	// ********************************************************************************
	/// <summary>
	/// �X�e�[�^�X�`��
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CPlayer::RenderStatus(void)
	{
		unsigned int Color = DxLib::GetColor(255, 255, 255);
		if (m_bDead)
		{
			Color = DxLib::GetColor(192, 64, 64);
		}
		DxLib::DrawFormatString(PlayerRectX + static_cast<int>((PlayerRectW - FontSize * 5) * 0.5f), PlayerRectY, Color, "�X�e�[�^�X");
		DxLib::DrawFormatString(PlayerRectX + FontSize, PlayerRectY + (FontSize + FontMargin) * 1, Color, "HP  : %d", m_Status.hp);
		DxLib::DrawFormatString(PlayerRectX + FontSize, PlayerRectY + (FontSize + FontMargin) * 2, Color, "ATK : %d", m_Status.attack);
		DxLib::DrawFormatString(PlayerRectX + static_cast<int>((PlayerRectW - FontSize * 3.5f) * 0.5f), PlayerRectY + 28 * 4, Color, "PLAYER1");
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

	void CPlayer::TurnStart(void)
	{
		m_Cursor = 0;
		m_State = COMMAND_WAIT;
		gMessage = "�ǂ�����H";

	}
}

