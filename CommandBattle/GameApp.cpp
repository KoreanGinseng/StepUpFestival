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
			theEffectManager.CreateEffect(static_cast<EffectType>(i), &EffectAnim[i], 1);
		}

		//�^�[���̏�����
		theTurnManager.SetTurn(TURN_PLAYER);

		gPlayer.Load();
		gEnemy.Load();
		gPlayer.Initialize();
		gEnemy.Initialize();
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
			gMessage = "�G��|�����I\nEnter�L�[�Ń��X�^�[�g�I";
			if (theSoundManager.IsPlay(SoundFile[SOUNDKEY_BGM_BATTLE].key))
			{
				theSoundManager.Stop(SoundFile[SOUNDKEY_BGM_BATTLE].key);
			}
			if (!theSoundManager.IsPlay(SoundFile[SOUNDKEY_BGM_CLEAR].key))
			{
				theSoundManager.Play(SoundFile[SOUNDKEY_BGM_CLEAR].key);
			}
			break;
		case STATE_GAMEOVER:
			gMessage = "����ł��܂����I\nEnter�L�[�Ń��X�^�[�g�I";
			if (theSoundManager.IsPlay(SoundFile[SOUNDKEY_BGM_BATTLE].key))
			{
				theSoundManager.Stop(SoundFile[SOUNDKEY_BGM_BATTLE].key);
			}
			if (!theSoundManager.IsPlay(SoundFile[SOUNDKEY_BGM_OVER].key))
			{
				theSoundManager.Play(SoundFile[SOUNDKEY_BGM_OVER].key);
			}
			break;
		}
		//���X�^�[�g�̏���
		if (check)
		{
			if (theInput.IsKeyPush(KEY_INPUT_RETURN))
			{
				gPlayer.Initialize();
				gEnemy.Initialize();
				gGameState = STATE_GAME;
				theTurnManager.SetTurn(TURN_PLAYER);
				theSoundManager.Stop();
				theSoundManager.Play(SoundFile[SOUNDKEY_SE_ENTER].key);
				theSoundManager.Play(SoundFile[SOUNDKEY_BGM_BATTLE].key);
			}
			return;
		}

		//���݂̃^�[���擾
		Turn nowTurn = theTurnManager.GetTurn();
		//�^�[�����ς�������A�U���A�A�C�e���̏���������
		if (!gbChangeTurn && theTurnManager.IsChanged())
		{
			gbChangeTurn = true;
			switch (nowTurn)
			{
			case TURN_PLAYER:
				{
					if (gEnemy.IsDead())
					{
						break;
					}
					int dmg = gEnemy.GetAttack();
					gPlayer.Dmg(dmg);
					gMessage += "\n�v���C���[��" + std::to_string(dmg) + "�̃_���[�W�I";
					break;
				}
			case TURN_ENEMY:
				{
					int dmg = gPlayer.GetAttack();
					gEnemy.Dmg(dmg);
					gMessage += "\n�G��" + std::to_string(dmg) + "�̃_���[�W�I";
					break;
				}
			}
			//�G������ł��邩�̔���
			if (gEnemy.IsDead())
			{
				if (gEnemy.GetDamageWait() <= 0)
				{
					gGameState |= STATE_GAMECLEAR;
				}
			}
			return;
		}
		else if (gbChangeTurn && !theTurnManager.IsChanged())
		{
			switch (nowTurn)
			{
			case TURN_PLAYER:
				gPlayer.RefreshDmg();
				if (gPlayer.GetDamageWait() <= 0)
				{
					gPlayer.TurnStart();
					gbChangeTurn = false;
				}
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
				gMessage = "�G�̍U���I";
				theSoundManager.Play(SoundFile[SOUNDKEY_SE_ENEMYATTACK].key);
				theTurnManager.SetTurn(TURN_PLAYER);
			}
			break;
		}
		//���S�`�F�b�N
		if (gPlayer.IsDead() && (gPlayer.GetDamageWait() <= 0))
		{
			gGameState |= STATE_GAMEOVER;
		}
	}
	/*************************************************************************//*!
			@brief			�`��
			@param			None

			@return			None
	*//**************************************************************************/
	void CGameApp::Render(void)
	{
		gEnemy.Render();

		//�R�}���h�l�p�̕`��
		DxLib::DrawBox(CommandRectX, CommandRectY, CommandRectX + CommandRectW, CommandRectY + CommandRectH, DxLib::GetColor(0, 0, 0), true);
		DxLib::DrawBox(CommandRectX, CommandRectY, CommandRectX + CommandRectW, CommandRectY + CommandRectH, DxLib::GetColor(255, 255, 255), false);
		DxLib::DrawBox(MessageRectX, MessageRectY, MessageRectX + MessageRectW, MessageRectY + MessageRectH, DxLib::GetColor(0, 0, 0), true);
		DxLib::DrawBox(MessageRectX, MessageRectY, MessageRectX + MessageRectW, MessageRectY + MessageRectH, DxLib::GetColor(255, 255, 255), false);
		DxLib::DrawFormatString(MessageRectX + FontSize, MessageRectY + FontMargin, DxLib::GetColor(255, 255, 255), "%s", gMessage.c_str());
		gPlayer.Render();
		if (gPlayer.GetDamageWait() % 10 != 1)
		{
			unsigned int Color = DxLib::GetColor(255, 255, 255);
			if (gPlayer.IsDead())
			{
				Color = DxLib::GetColor(192, 64, 64);
			}
			DxLib::DrawBox(PlayerRectX, PlayerRectY, PlayerRectX + PlayerRectW, PlayerRectY + PlayerRectH, DxLib::GetColor(0, 0, 0), true);
			DxLib::DrawBox(PlayerRectX, PlayerRectY, PlayerRectX + PlayerRectW, PlayerRectY + PlayerRectH, Color, false);
			gPlayer.RenderStatus();
		}

		theEffectManager.Render();
	}
	/*************************************************************************//*!
			@brief			���
			@param			None

			@return			None
	*//**************************************************************************/
	void CGameApp::Release(void)
	{
		gPlayer.Release();
		gEnemy.Release();
		theEffectManager.Release();
		theSoundManager.Release();
	}
}
