/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	�Q�[���A�v���N���X

															@author	���̂���
															@date	2020.02.14
*//**************************************************************************/

#include "GameApp.h"
#include "GameDefine.h"
#include "GameScene.h"
#include "TitleScene.h"

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

//�V�[���̐���
CSceneBase* CreateScene(const SceneName& scene);

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

		// �V�[���̍쐬
		m_pScene = CreateScene(SCENE_TITLE);
		m_pScene->Initialize();
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
		m_pScene->Update();

		if (m_pScene->IsEnd())
		{
			SceneName nextScene = (SceneName)m_pScene->GetNextScene();
			m_pScene->Release();
			delete m_pScene;
			m_pScene = CreateScene(nextScene);
			m_pScene->Initialize();
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
		m_pScene->Render();
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
		theEffectManager.Release();
		theSoundManager.Release();
		if (m_pScene)
		{
			m_pScene->Release();
			delete m_pScene;
			m_pScene = nullptr;
		}
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
		int len = (int)full.length();
		int lastlen = (int)full.find_last_of("\\");
		std::string current = full.substr(lastlen + 1, len - lastlen);
		//���݂̃t�@�C���ʒu���烊�\�[�X�t�H���_�̐ݒ�
		if (current == "CommandBattle")
		{
			SetCurrentDirectory("../Resource");
		}
		else
		{
			SetCurrentDirectory("Resource");
		}
	}
}



CSceneBase* CreateScene(const SceneName & scene)
{
	switch (scene)
	{
	case SCENE_TITLE:
		return new CTitleScene();
	case SCENE_GAME:
		return new CGameScene();
	case SCENE_GAMEOVER:
		return nullptr;
	case SCENE_GAMECLEAR:
		return nullptr;
	default:
		return nullptr;
	}
	return nullptr;
}