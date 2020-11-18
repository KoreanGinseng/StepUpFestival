#include "GameScene.h"
#include "TurnManager.h"

std::string DxLibPlus::CGameScene::m_Message = "";

namespace DxLibPlus
{
	CGameScene::CGameScene(void)
		: CSceneBase()
	{
		//�T�E���h�S�X�g�b�v
		theSoundManager.Stop();
	}

	CGameScene::~CGameScene(void)
	{
	}

	void CGameScene::Initialize(void)
	{
		//�^�[���̏�����
		theTurnManager.SetTurn(TURN_PLAYER);

		//�v���C���[�̓ǂݍ���
		m_Player.Load();
		//�G�̓ǂݍ���
		m_Enemy.Load();
		//�v���C���[�̏�����
		m_Player.Initialize();
		//�G�̏�����
		m_Enemy.Initialize();

		//�o�g��BGM�̍Đ�
		theSoundManager.Play(SoundFile[SOUNDKEY_BGM_BATTLE].key);
	}

	void CGameScene::Update(void)
	{
		//�Q�[���I�[�o�[���N���A�̔���
		unsigned int check = m_GameState & STATE_CHECK;
		//��ԕʂɃ��b�Z�[�W��ݒ肷��
		switch (check)
		{
		case STATE_GAMECLEAR:
			GameStateClear();
			break;
		case STATE_GAMEOVER:
			GameStateOver();
			break;
		}
		//�Q�[���I�[�o�[���Q�[���N���A�ŃG���^�[�L�[�������ƃ��X�^�[�g
		if (check)
		{
			if (theInput.IsKeyPush(KEY_INPUT_RETURN))
			{
				//���X�^�[�g�̏���
				//ReStart();
				//���艹��炷
				theSoundManager.Play(SoundFile[SOUNDKEY_SE_ENTER].key);
				m_bEnd = true;
				m_NextScene = SCENE_TITLE;
			}
			return;
		}

		//���݂̃^�[���擾
		Turn nowTurn = theTurnManager.GetTurn();
		//�^�[�����ς�������A�U���̏���������
		if (!m_bChangeTurn && theTurnManager.IsChanged())
		{
			RefreshChangeTurn(nowTurn);
			return;
		}
		//�^�[���؂�ւ������܂ł̏���
		else if (m_bChangeTurn && !theTurnManager.IsChanged())
		{
			//���݂̃^�[���ɂ��邽�߂̏���
			switch (nowTurn)
			{
			case TURN_PLAYER:
				RefreshPlayer();
				break;
			case TURN_ENEMY:
				m_bChangeTurn = false;
				break;
			}
			return;
		}

		//�^�[���ɂ���čX�V
		switch (nowTurn)
		{
		case TURN_PLAYER:
			m_Player.Update();
			m_bEnd = m_Player.IsEnd();
			if (m_bEnd)
			{
				m_NextScene = SCENE_TITLE;
			}
			break;
		case TURN_ENEMY:
			//�_���[�W�̏���
			m_Enemy.RefreshDmg();
			//�G�̍X�V
			m_Enemy.Update();
			break;
		}
		CheckGameOver();
	}

	void CGameScene::Render(void)
	{
		//�G�̕`��
		m_Enemy.Render();
		//�R�}���h�{�b�N�X�̕`��
		DxLib::DrawBox(CommandRectX, CommandRectY, CommandRectX + CommandRectW, CommandRectY + CommandRectH, DxLib::GetColor(0, 0, 0), true);
		DxLib::DrawBox(CommandRectX, CommandRectY, CommandRectX + CommandRectW, CommandRectY + CommandRectH, DxLib::GetColor(255, 255, 255), false);
		//���b�Z�[�W�{�b�N�X�̕`��
		DxLib::DrawBox(MessageRectX, MessageRectY, MessageRectX + MessageRectW, MessageRectY + MessageRectH, DxLib::GetColor(0, 0, 0), true);
		DxLib::DrawBox(MessageRectX, MessageRectY, MessageRectX + MessageRectW, MessageRectY + MessageRectH, DxLib::GetColor(255, 255, 255), false);
		//���b�Z�[�W�̕`��
		DxLib::DrawFormatString(MessageRectX + FontSize, MessageRectY + FontMargin, DxLib::GetColor(255, 255, 255), "%s", m_Message.c_str());
		//�v���C���[�̕`��
		m_Player.Render();
		//�v���C���[�̃X�e�[�^�X�`��
		if (m_Player.GetDamageWait() % 10 != 1)
		{
			unsigned int Color = DxLib::GetColor(255, 255, 255);
			//����ł���ΐF��Ԃ�����
			if (m_Player.IsDead())
			{
				Color = DxLib::GetColor(192, 64, 64);
			}
			//�X�e�[�^�X�{�b�N�X�̕`��
			DxLib::DrawBox(PlayerRectX, PlayerRectY, PlayerRectX + PlayerRectW, PlayerRectY + PlayerRectH, DxLib::GetColor(0, 0, 0), true);
			DxLib::DrawBox(PlayerRectX, PlayerRectY, PlayerRectX + PlayerRectW, PlayerRectY + PlayerRectH, Color, false);
			//�X�e�[�^�X�̕`��
			m_Player.RenderStatus();
		}
		//�G�t�F�N�g�̕`��
		theEffectManager.Render();
	}

	void CGameScene::Release(void)
	{
		//�e�������
		m_Player.Release();
		m_Enemy.Release();
	}

	std::string & CGameScene::GetMessage(void)
	{
		return m_Message;
	}

	void CGameScene::SetMessage(const std::string & str)
	{
		m_Message = str;
	}

	// ********************************************************************************
	/// <summary>
	/// �Q�[���N���A��Ԃ̏���
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CGameScene::GameStateClear(void)
	{
		//���b�Z�[�W�̕ύX
		m_Message = "�G��|�����I\nEnter�L�[�Ń^�C�g���ցI";
		//�o�g��BGM�����Ă���Ύ~�߂�
		if (theSoundManager.IsPlay(SoundFile[SOUNDKEY_BGM_BATTLE].key))
		{
			theSoundManager.Stop(SoundFile[SOUNDKEY_BGM_BATTLE].key);
		}
		//�N���A���y�����Ă��Ȃ���΂Ȃ炷
		if (!theSoundManager.IsPlay(SoundFile[SOUNDKEY_BGM_CLEAR].key))
		{
			theSoundManager.Play(SoundFile[SOUNDKEY_BGM_CLEAR].key);
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �Q�[���I�[�o�[��Ԃ̏���
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CGameScene::GameStateOver(void)
	{
		//���b�Z�[�W�̕ύX
		m_Message = "����ł��܂����I\nEnter�L�[�Ń^�C�g���ցI";
		//�o�g��BGM�����Ă���Ύ~�߂�
		if (theSoundManager.IsPlay(SoundFile[SOUNDKEY_BGM_BATTLE].key))
		{
			theSoundManager.Stop(SoundFile[SOUNDKEY_BGM_BATTLE].key);
		}
		//�Q�[���I�[�o�[���y�����Ă��Ȃ���΂Ȃ炷
		if (!theSoundManager.IsPlay(SoundFile[SOUNDKEY_BGM_OVER].key))
		{
			theSoundManager.Play(SoundFile[SOUNDKEY_BGM_OVER].key);
		}
	}
	// ********************************************************************************
	/// <summary>
	/// ���X�^�[�g���̏�����
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CGameScene::ReStart(void)
	{
		//�v���C���[�̏�����
		m_Player.Initialize();
		//�G�̏�����
		m_Enemy.Initialize();
		//�Q�[���̏�Ԃ̏�����
		m_GameState = STATE_GAME;
		//�^�[���̏�����
		theTurnManager.SetTurn(TURN_PLAYER);
		//�T�E���h�S�X�g�b�v
		theSoundManager.Stop();
		//�o�g��BGM�̍Đ�
		theSoundManager.Play(SoundFile[SOUNDKEY_BGM_BATTLE].key);
	}
	// ********************************************************************************
	/// <summary>
	/// �v���C���[�ւ̃_���[�W����
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CGameScene::DmgPlayer(void)
	{
		//�G������ł���΍U�������Ȃ�
		if (m_Enemy.IsDead())
		{
			return;
		}
		//�G�̍U���͂��擾
		int dmg = m_Enemy.GetAttack();
		//�v���C���[�Ƀ_���[�W��^����
		m_Player.Dmg(dmg);
		//���b�Z�[�W�̕ύX
		m_Message += "\n�v���C���[��" + std::to_string(dmg) + "�̃_���[�W�I";
	}
	// ********************************************************************************
	/// <summary>
	/// �G�ւ̃_���[�W����
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CGameScene::DmgEnemy(void)
	{
		//�v���C���[�̍U���͂��擾
		int dmg = m_Player.GetAttack();
		//�G�Ƀ_���[�W��^����
		m_Enemy.Dmg(dmg);
		//���b�Z�[�W�̕ύX
		m_Message += "\n�G��" + std::to_string(dmg) + "�̃_���[�W�I";
	}
	// ********************************************************************************
	/// <summary>
	/// �v���C���[�̃^�[���ɂȂ��܂ł̏���
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CGameScene::RefreshPlayer(void)
	{
		//�v���C���[�̃_���[�W�\��
		m_Player.RefreshDmg();
		//�_���[�W�\�����Ƀ^�[���͐؂�ւ��Ȃ�
		if (m_Player.GetDamageWait() <= 0)
		{
			m_Player.TurnStart();
			m_bChangeTurn = false;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �^�[�����ς�������̎��̃^�[���܂łȂ�����
	/// </summary>
	/// <param name="turn">���݂̃^�[��</param>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	void CGameScene::RefreshChangeTurn(const Turn & turn)
	{
		//�^�[���̐؂�ւ�����������
		m_bChangeTurn = true;
		//���݂̃^�[�����v���C���[�Ȃ�G����̍U�������炤
		switch (turn)
		{
		case TURN_PLAYER:
			DmgPlayer();
			break;
		case TURN_ENEMY:
			DmgEnemy();
			break;
		}
		//�G������ł���΃Q�[���N���A��Ԃɂ���
		if (m_Enemy.IsDead() && m_Enemy.GetDamageWait() <= 0)
		{
			m_GameState = STATE_GAMECLEAR;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �Q�[���I�[�o�[�̊Ď�
	/// </summary>
	/// <created>���̂���,2020/02/23</created>
	/// <changed>���̂���,2020/02/23</changed>
	// ********************************************************************************
	void CGameScene::CheckGameOver(void)
	{
		//���S�`�F�b�N
		if (m_Player.IsDead() && (m_Player.GetDamageWait() <= 0))
		{
			m_GameState |= STATE_GAMEOVER;
		}
	}
}
