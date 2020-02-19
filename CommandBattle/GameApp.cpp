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

//�摜�o�^���
TexMngInfo TexFile[] = {
   { "dragon_blue"   , "Enemy/dragon_blue.png"   },
   { "dragon_red"    , "Enemy/dragon_red.png"    },
   { "dragon_green"  , "Enemy/dragon_green.png"  },
   { "dragon_komodo" , "Enemy/komodo_dragon.png" },
};

CPlayer		gPlayer;

namespace DxLibPlus
{
	/*************************************************************************//*!
			@brief			������
			@param			None

			@return			None
	*//**************************************************************************/
	void CGameApp::Initialize(void)
	{
		//���\�[�X�t�H���_�̐ݒ�
		SetCurrentDirectory("../Resource");
		//�摜�̓ǂݍ���
		theTextureManager.LoadList(TexFile, TEXKEY_COUNT);

		//�^�[���̏�����
		theTurnManager.SetTurn(TURN_PLAYER);

		gPlayer.Load();
		gPlayer.Initialize();
	}
	/*************************************************************************//*!
			@brief			�X�V
			@param			None

			@return			None
	*//**************************************************************************/
	void CGameApp::Update(void)
	{
		//���݂̃^�[���擾
		Turn nowTurn = theTurnManager.GetTurn();
		//�^�[���ɂ���čX�V
		switch (nowTurn)
		{
		case TURN_PLAYER:
			gPlayer.Update();
			break;
		case TURN_ENEMY:

			break;
		default:
			break;
		}
	}
	/*************************************************************************//*!
			@brief			�`��
			@param			None

			@return			None
	*//**************************************************************************/
	void CGameApp::Render(void)
	{
		//�\���ʒu�v�Z(������)
		int x = (CGraphicsUtillities::GetTargetWidth() - theTextureManager.GetWidth(TexFile[TEXKEY_DRAGON_KOMODO].key)) * 0.5f;
		//�h���S���̕`��
		DxLib::DrawGraph(x, PlayerRectW, theTextureManager.GetGraphHandle(TexFile[TEXKEY_DRAGON_KOMODO].key), true);
		//�R�}���h�l�p�̕`��
		DxLib::DrawBox(CommandRectX, CommandRectY, CommandRectX + CommandRectW, CommandRectY + CommandRectH, DxLib::GetColor(255, 255, 255), false);
		DxLib::DrawBox(MessageRectX, MessageRectY, MessageRectX + MessageRectW, MessageRectY + MessageRectH, DxLib::GetColor(255, 255, 255), false);
		DxLib::DrawBox(PlayerRectX, PlayerRectY, PlayerRectX + PlayerRectW, PlayerRectY + PlayerRectH, DxLib::GetColor(255, 255, 255), false);

		gPlayer.Render();
	}
	/*************************************************************************//*!
			@brief			���
			@param			None

			@return			None
	*//**************************************************************************/
	void CGameApp::Release(void)
	{
		gPlayer.Release();
	}
}
