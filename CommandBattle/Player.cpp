/*************************************************************************//*!

					@file	Player.cpp
					@brief	�v���C���[�N���X

															@author	���̂���
															@date	2020.02.21
*//**************************************************************************/

//INCLUDE
#include "Player.h"
#include "GameScene.h"

//�R�}���h���X�g
std::string gCommandList[] = {
	"��������",
	"�Ƃ���",
	"�ɂ���",
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
		std::string buff = CDxLibUtilities::WStringToString(wstr);
		int length = (int)buff.length();
		int indentCnt = 0;
		int strlen = 0;
		std::string str = "";
		while (length > indentCnt && strlen >= 0)
		{
			//���s��؂�ŕ�����擾
			str = CDxLibUtilities::GetSpalateString(buff, "\n", strlen, indentCnt);
			//�X�e�[�^�X�R�}���h�̏ꍇ
			if (str == "status")
			{
				//HP�̎擾
				str = CDxLibUtilities::GetSpalateString(buff, "\n", strlen, indentCnt);
				m_Status.hp = std::atoi(str.c_str());
				m_OffsetHp = m_Status.hp;
				//ATTACK�̎擾
				str = CDxLibUtilities::GetSpalateString(buff, "\n", strlen, indentCnt);
				m_Status.attack = std::atoi(str.c_str());
			}
			//�X�L���R�}���h�̏ꍇ
			else if (str == "skill")
			{
				Skill addData;
				//�X�L�����擾
				str = CDxLibUtilities::GetSpalateString(buff, "\n", strlen, indentCnt);
				addData.name = str;
				//�X�L���U���{���擾
				str = CDxLibUtilities::GetSpalateString(buff, "\n", strlen, indentCnt);
				addData.rate = static_cast<float>(std::atof(str.c_str()));
				//�G�t�F�N�g�̎�ގ擾
				str = CDxLibUtilities::GetSpalateString(buff, "\n", strlen, indentCnt);
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
		CGameScene::SetMessage("�ǂ�����H");
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
		//�J�[�\���𓮂���
		CursorMove();

		//�I�����g�O�ɍs���Ȃ��悤�ɂ���
		CursorOver();

		//��Ԃ��ƂɃG���^�[�L�[���������Ƃ��̑���𕪂���
		if (theInput.IsKeyPush(KEY_INPUT_RETURN))
		{
			//���艹��炷
			theSoundManager.Play(SoundFile[SOUNDKEY_SE_ENTER].key);
			switch (m_State)
			{
			case COMMAND_WAIT:
				EnterWait();
				break;
			case COMMAND_SKILL:
				EnterSkill();
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
		//��Ԃɂ���ĕ\���F��ς���
		switch (m_State)
		{
		case COMMAND_ATTACK:
			Color = DxLib::GetColor(128, 128, 128);
		case COMMAND_WAIT:
			if (m_bDead)
			{
				Color = DxLib::GetColor(192, 64, 64);
			}
			for (int i = 0; i < 3; i++)
			{
				DxLib::DrawFormatString(CommandRectX + FontSize, CommandRectY + i * (FontSize + FontMargin) + FontMargin, Color, "%s", gCommandList[i].c_str());
			}
			break;
			//�X�L���y�[�W�̕\��
		case COMMAND_SKILL:
			for (int i = 0; i < static_cast<int>(m_SkillList.size()); i++)
			{
				//�X�L�����X�g���\�����𒴂��Ă���ꍇ�y�[�W�؂�ւ��ł���悤�ɂ���
				int scrlCnt = (m_Cursor / LineMax);
				if (scrlCnt)
				{
					scroll = 0;
					scroll = ((FontSize + FontMargin) * LineMax) * scrlCnt;
					if (i < LineMax * scrlCnt)
					{
						continue;
					}
				}
				DxLib::DrawFormatString(CommandRectX + FontSize, CommandRectY + i * (FontSize + FontMargin) + FontMargin - scroll, Color, "%s", m_SkillList[i].name.c_str());
			}
			break;
		default:
			break;
		}
		//�J�[�\���̕\��
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
		DxLib::DrawFormatString(PlayerRectX + static_cast<int>((PlayerRectW - FontSize * 5) * 0.5f), PlayerRectY + (FontSize + FontMargin) * 1, Color, "HP  : %4d", (m_Status.hp <= 9999) ? m_Status.hp : 9999);
		DxLib::DrawFormatString(PlayerRectX + static_cast<int>((PlayerRectW - FontSize * 5) * 0.5f), PlayerRectY + (FontSize + FontMargin) * 2, Color, "ATK : %4d", (m_Status.attack <= 9999) ? m_Status.attack : 9999);
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
	// ********************************************************************************
	/// <summary>
	/// �؂�ւ�����
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CPlayer::TurnStart(void)
	{
		//�J�[�\������ԏ�ɃZ�b�g����
		m_Cursor = 0;
		//�ҋ@���
		m_State = COMMAND_WAIT;
		//���b�Z�[�W�ύX
		CGameScene::SetMessage("�ǂ�����H");

	}
	// ********************************************************************************
	/// <summary>
	/// �J�[�\���ړ�����
	/// </summary>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	void CPlayer::CursorMove(void)
	{
		//��L�[����������I������ɂ���
		if (theInput.IsKeyPush(KEY_INPUT_UP))
		{
			m_Cursor--;
			theSoundManager.Play(SoundFile[SOUNDKEY_SE_SELECT].key);
		}
		//���L�[����������I�������ɂ���
		else if (theInput.IsKeyPush(KEY_INPUT_DOWN))
		{
			m_Cursor++;
			theSoundManager.Play(SoundFile[SOUNDKEY_SE_SELECT].key);
		}
		//���L�[����������I����1�y�[�W����ɂ���
		else if (theInput.IsKeyPush(KEY_INPUT_LEFT))
		{
			m_Cursor -= LineMax;
			theSoundManager.Play(SoundFile[SOUNDKEY_SE_SELECT].key);
		}
		//�E�L�[����������I����1�y�[�W�����ɂ���
		else if (theInput.IsKeyPush(KEY_INPUT_RIGHT))
		{
			m_Cursor += LineMax;
			theSoundManager.Play(SoundFile[SOUNDKEY_SE_SELECT].key);
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �J�[�\�������X�g���ȏ㒴���Ȃ��悤�ɂ��鏈��
	/// </summary>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	void CPlayer::CursorOver(void)
	{
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
	}
	// ********************************************************************************
	/// <summary>
	/// ����{�^�����������Ƃ��I�񂾃R�}���h�ɂ���ď�Ԃ�ω������鏈��
	/// </summary>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	void CPlayer::EnterWait(void)
	{
		//��Ԏ擾
		m_State = static_cast<CommandState>(m_Cursor + 1);
		//�ʏ�U���̏ꍇ
		if (m_State == COMMAND_ATTACK)
		{
			//�U���{��1�{
			m_AttackRate = 1.0f;
			//�a���G�t�F�N�g�J�n
			theEffectManager.Start(SKILL_SLASH);
			//�a������炷
			theSoundManager.Play(SoundFile[SOUNDKEY_SE_SLASH].key);
			//�s���I���Ȃ̂œG�̃^�[���ֈڍs����
			theTurnManager.SetTurn(TURN_ENEMY);
			//���b�Z�[�W��ύX
			CGameScene::SetMessage("�v���C���[�̍U���I");
		}
		//�I���������ꂽ�ꍇ
		else if (m_State == COMMAND_EXIT)
		{
			//�A�v���I��
			m_bEnd = true;
			//PostQuitMessage(0);
		}
		//��L�ȊO�̓J�[�\����߂�����
		else
		{
			m_Cursor = 0;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �X�L�������߂��Ƃ��̏���
	/// </summary>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	void CPlayer::EnterSkill(void)
	{
		//�X�L���̈�ԍŌ�(�߂�R�}���h)�Ȃ��߂�
		if (m_Cursor == m_SkillList.size() - 1)
		{
			m_State = COMMAND_WAIT;
			return;
		}
		//��Ԃ��U���ɕύX
		m_State = COMMAND_ATTACK;
		//�U���{����I�񂾃X�L���̔{���ɃZ�b�g����
		m_AttackRate = m_SkillList[m_Cursor].rate;
		//�I�񂾃X�L���̃G�t�F�N�g�𔭐�������
		theEffectManager.Start(m_SkillList[m_Cursor].effect);
		//���̔ԍ����擾
		int sound = SOUNDKEY_BGM_COUNT + m_SkillList[m_Cursor].effect;
		//�X�L���ɂ���������炷
		theSoundManager.Play(SoundFile[sound].key);
		//�s���I���Ȃ̂œG�̃^�[���ֈڍs����
		theTurnManager.SetTurn(TURN_ENEMY);
		//���b�Z�[�W�ɃX�L������\��������
		CGameScene::SetMessage("�v���C���[��" + m_SkillList[m_Cursor].name + "�I");
		//�J�[�\���̃��Z�b�g
		m_Cursor = 0;
	}
}

