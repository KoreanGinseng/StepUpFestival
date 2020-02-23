/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	�Q�[���A�v���N���X

															@author	���̂���
															@date	2020.02.14
*//**************************************************************************/

//INCLUDE
#include "GameApp.h"
#include "GameDefine.h"
#include "Player.h"
#include "Enemy.h"

//�摜�o�^���
TexMngInfo TexFile[] = {
	{ "dragon_blue"   , "Enemy/dragon_blue.png"   },
	{ "dragon_red"    , "Enemy/dragon_red.png"    },
	{ "dragon_green"  , "Enemy/dragon_green.png"  },
	{ "dragon_komodo" , "Enemy/komodo_dragon.png" },
	{ "effect_fire"   , "Effect/Fire.png"         },
	{ "effect_ice"    , "Effect/Ice.png"          },
	{ "effect_thunder", "Effect/Thunder.png"      },
	{ "effect_slash"  , "Effect/Slash.png"        },
	{ "cursor"        , "cursor.png"              },
};

//�T�E���h�o�^���
SoundMngInfo SoundFile[] = {
	{ "bgm_battle"       , "Sound/BGM/battle.mp3"    },
	{ "bgm_clear"        , "Sound/BGM/gameclear.mp3" },
	{ "bgm_over"         , "Sound/BGM/gameover.mp3"  },
	{ "se_skill_fire"    , "Sound/SE/fire.mp3"       },
	{ "se_skill_ice"     , "Sound/SE/ice.mp3"        },
	{ "se_skill_thunder" , "Sound/SE/thunder.mp3"    },
	{ "se_skill_slash"   , "Sound/SE/slash.mp3"      },
	{ "se_select"        , "Sound/SE/select.mp3"     },
	{ "se_enter"         , "Sound/SE/enter.mp3"      },
	{ "se_enemyattack"   , "Sound/SE/enemyattack.mp3"},
};

//�G�t�F�N�g�쐬���
Animation<10> EffectAnim[] = {
	{
		"FIRE", 0, 0, 192, 192, false,
		{
			{ 5, 0, 0 }, { 5, 1, 0 },{ 5, 2, 0 }, { 5, 3, 0 }, { 5, 4, 0 },
			{ 5, 0, 1 }, { 5, 1, 1 },{ 5, 2, 1 }, { 5, 3, 1 }, { 5, 4, 1 }
		}
	},
	{
		"ICE", 0, 0, 192, 192, false,
		{
			{ 5, 0, 0 }, { 5, 1, 0 },{ 5, 2, 0 }, { 5, 3, 0 }, { 5, 4, 0 },
			{ 5, 0, 1 }, { 5, 1, 1 },{ 5, 2, 1 }, { 5, 3, 1 }, { 5, 4, 1 }
		}
	},
	{
		"THUNDER", 0, 0, 192, 192, false,
		{
			{ 5, 0, 0 }, { 5, 1, 0 },{ 5, 2, 0 }, { 5, 3, 0 }, { 5, 4, 0 },
			{ 5, 0, 1 }, { 5, 1, 1 },{ 5, 2, 1 }, { 5, 3, 1 }, { 5, 4, 1 }
		}
	},
	{
		"SLASH", 0, 0, 192, 192, false,
		{
			{ 5, 0, 0 }, { 5, 1, 0 },{ 5, 2, 0 }, { 5, 3, 0 }, { 5, 4, 0 },
			{ 5, 0, 1 }, { 5, 1, 1 },{ 5, 2, 1 }, { 5, 3, 1 }, { 5, 4, 1 }
		}
	},
};

CPlayer		gPlayer;					//!<�v���C���[
CEnemy		gEnemy;						//!<�G
bool		gbChangeTurn = false;		//!<�^�[���ύX�t���O
int			gGameState = STATE_GAME;	//!<�Q�[���̏��

std::string gMessage = "";				//!<���b�Z�[�W

namespace DxLibPlus
{
	// ********************************************************************************
	/// <summary>
	/// ������
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CGameApp::Initialize(void)
	{
		//���\�[�X�t�H���_�̎w��
		SetResourceFolder();
		
		//�摜�̓ǂݍ���
		theTextureManager.LoadList(TexFile, TEXKEY_COUNT);
		//�T�E���h�̓ǂݍ���
		for (int i = 0; i < SOUNDKEY_COUNT; i++)
		{
			theSoundManager.Load(SoundFile[i].key, SoundFile[i].file);
			if (i < SOUNDKEY_BGM_COUNT)
			{
				theSoundManager.SetLoop(SoundFile[i].key, true);
			}
		}
		//�G�t�F�N�g�̍쐬
		for (int i = 0; i < SKILL_COUNT; i++)
		{
			theEffectManager.CreateEffect(static_cast<SkillType>(i), &EffectAnim[i], 1);
		}

		//�^�[���̏�����
		theTurnManager.SetTurn(TURN_PLAYER);

		//�v���C���[�̓ǂݍ���
		gPlayer.Load();
		//�G�̓ǂݍ���
		gEnemy.Load();
		//�v���C���[�̏�����
		gPlayer.Initialize();
		//�G�̏�����
		gEnemy.Initialize();

		//�o�g��BGM�̍Đ�
		theSoundManager.Play(SoundFile[SOUNDKEY_BGM_BATTLE].key);
	}
	// ********************************************************************************
	/// <summary>
	/// �X�V
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CGameApp::Update(void)
	{
		//�Q�[���I�[�o�[���N���A�̔���
		unsigned int check = gGameState & STATE_CHECK;
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
				ReStart();
				//���艹��炷
				theSoundManager.Play(SoundFile[SOUNDKEY_SE_ENTER].key);
			}
			return;
		}

		//���݂̃^�[���擾
		Turn nowTurn = theTurnManager.GetTurn();
		//�^�[�����ς�������A�U���A�A�C�e���̏���������
		if (!gbChangeTurn && theTurnManager.IsChanged())
		{
			//�^�[���̐؂�ւ�����������
			gbChangeTurn = true;
			//���݂̃^�[�����v���C���[�Ȃ�G����̍U�������炤
			switch (nowTurn)
			{
			case TURN_PLAYER:
				DmgPlayer();
				break;
			case TURN_ENEMY:
				DmgEnemy();
				break;
			}
			//�G������ł���΃Q�[���N���A��Ԃɂ���
			if (gEnemy.IsDead() && gEnemy.GetDamageWait() <= 0)
			{
				gGameState = STATE_GAMECLEAR;
			}
			return;
		}
		//�^�[���؂�ւ������܂ł̏���
		else if (gbChangeTurn && !theTurnManager.IsChanged())
		{
			//���݂̃^�[���ɂ��邽�߂̏���
			switch (nowTurn)
			{
			case TURN_PLAYER:
				RefreshPlayer();
				break;
			case TURN_ENEMY:
				gbChangeTurn = false;
				break;
			}
			return;
		}

		//�^�[���ɂ���čX�V
		switch (nowTurn)
		{
		case TURN_PLAYER:
			gPlayer.Update();
			break;
		case TURN_ENEMY:
			gEnemy.RefreshDmg();
			gEnemy.Update();
			if (gEnemy.GetDamageWait() <= 0)
			{
				theTurnManager.SetTurn(TURN_PLAYER);
				gMessage = "�G�̍U���I";
				if (!gEnemy.IsDead())
				{
					theSoundManager.Play(SoundFile[SOUNDKEY_SE_ENEMYATTACK].key);
				}
			}
			break;
		}
		//���S�`�F�b�N
		if (gPlayer.IsDead() && (gPlayer.GetDamageWait() <= 0))
		{
			gGameState |= STATE_GAMEOVER;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �`��
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CGameApp::Render(void)
	{
		//�G�̕`��
		gEnemy.Render();
		//�R�}���h�{�b�N�X�̕`��
		DxLib::DrawBox(CommandRectX, CommandRectY, CommandRectX + CommandRectW, CommandRectY + CommandRectH, DxLib::GetColor(0, 0, 0), true);
		DxLib::DrawBox(CommandRectX, CommandRectY, CommandRectX + CommandRectW, CommandRectY + CommandRectH, DxLib::GetColor(255, 255, 255), false);
		//���b�Z�[�W�{�b�N�X�̕`��
		DxLib::DrawBox(MessageRectX, MessageRectY, MessageRectX + MessageRectW, MessageRectY + MessageRectH, DxLib::GetColor(0, 0, 0), true);
		DxLib::DrawBox(MessageRectX, MessageRectY, MessageRectX + MessageRectW, MessageRectY + MessageRectH, DxLib::GetColor(255, 255, 255), false);
		//���b�Z�[�W�̕`��
		DxLib::DrawFormatString(MessageRectX + FontSize, MessageRectY + FontMargin, DxLib::GetColor(255, 255, 255), "%s", gMessage.c_str());
		//�v���C���[�̕`��
		gPlayer.Render();
		//�v���C���[�̃X�e�[�^�X�`��
		if (gPlayer.GetDamageWait() % 10 != 1)
		{
			unsigned int Color = DxLib::GetColor(255, 255, 255);
			//����ł���ΐF��Ԃ�����
			if (gPlayer.IsDead())
			{
				Color = DxLib::GetColor(192, 64, 64);
			}
			//�X�e�[�^�X�{�b�N�X�̕`��
			DxLib::DrawBox(PlayerRectX, PlayerRectY, PlayerRectX + PlayerRectW, PlayerRectY + PlayerRectH, DxLib::GetColor(0, 0, 0), true);
			DxLib::DrawBox(PlayerRectX, PlayerRectY, PlayerRectX + PlayerRectW, PlayerRectY + PlayerRectH, Color, false);
			//�X�e�[�^�X�̕`��
			gPlayer.RenderStatus();
		}
		//�G�t�F�N�g�̕`��
		theEffectManager.Render();
	}
	// ********************************************************************************
	/// <summary>
	/// ���
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CGameApp::Release(void)
	{
		//�e�������
		gPlayer.Release();
		gEnemy.Release();
		theEffectManager.Release();
		theSoundManager.Release();
	}
	// ********************************************************************************
	/// <summary>
	/// ���\�[�X�t�H���_�̎w��
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CGameApp::SetResourceFolder(void)
	{
		//�t���p�X�擾
		char pass[MAX_PATH + 1];
		GetCurrentDirectory(MAX_PATH + 1, pass);
		std::string full = pass;
		//�J�����g�p�X�ɕϊ�
		int len = full.length();
		int lastlen = full.find_last_of("\\");
		std::string current = full.substr(lastlen + 1, len - lastlen);
		//���݂̃t�@�C���ʒu���烊�\�[�X�t�H���_�̐ݒ�
		if (current == "CommandBattle")
		{
			SetCurrentDirectory("../Resource");
		}
		else if (current == "StepUpFestival")
		{
			SetCurrentDirectory("Resource");
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �Q�[���N���A��Ԃ̏���
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CGameApp::GameStateClear(void)
	{
		//���b�Z�[�W�̕ύX
		gMessage = "�G��|�����I\nEnter�L�[�Ń��X�^�[�g�I";
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
	void CGameApp::GameStateOver(void)
	{
		//���b�Z�[�W�̕ύX
		gMessage = "����ł��܂����I\nEnter�L�[�Ń��X�^�[�g�I";
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
	void CGameApp::ReStart(void)
	{
		//�v���C���[�̏�����
		gPlayer.Initialize();
		//�G�̏�����
		gEnemy.Initialize();
		//�Q�[���̏�Ԃ̏�����
		gGameState = STATE_GAME;
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
	void CGameApp::DmgPlayer(void)
	{
		//�G������ł���΍U�������Ȃ�
		if (gEnemy.IsDead())
		{
			return;
		}
		//�G�̍U���͂��擾
		int dmg = gEnemy.GetAttack();
		//�v���C���[�Ƀ_���[�W��^����
		gPlayer.Dmg(dmg);
		//���b�Z�[�W�̕ύX
		gMessage += "\n�v���C���[��" + std::to_string(dmg) + "�̃_���[�W�I";
	}
	// ********************************************************************************
	/// <summary>
	/// �G�ւ̃_���[�W����
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CGameApp::DmgEnemy(void)
	{
		//�v���C���[�̍U���͂��擾
		int dmg = gPlayer.GetAttack();
		//�G�Ƀ_���[�W��^����
		gEnemy.Dmg(dmg);
		//���b�Z�[�W�̕ύX
		gMessage += "\n�G��" + std::to_string(dmg) + "�̃_���[�W�I";
	}
	// ********************************************************************************
	/// <summary>
	/// �v���C���[�̃^�[���ɂȂ��܂ł̏���
	/// </summary>
	/// <created>���̂���,2020/02/21</created>
	/// <changed>���̂���,2020/02/21</changed>
	// ********************************************************************************
	void CGameApp::RefreshPlayer(void)
	{
		//�v���C���[�̃_���[�W�\��
		gPlayer.RefreshDmg();
		//�_���[�W�\�����Ƀ^�[���͐؂�ւ��Ȃ�
		if (gPlayer.GetDamageWait() <= 0)
		{
			gPlayer.TurnStart();
			gbChangeTurn = false;
		}
	}
}
