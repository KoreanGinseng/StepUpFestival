/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	ゲームアプリクラス

															@author	いのうえ
															@date	2020.02.14
*//**************************************************************************/

//INCLUDE
#include "GameApp.h"
#include "GameDefine.h"

//画像登録情報
TexMngInfo TexFile[] = {
   { "dragon_blue"   , "Enemy/dragon_blue.png"   },
   { "dragon_red"    , "Enemy/dragon_red.png"    },
   { "dragon_green"  , "Enemy/dragon_green.png"  },
   { "dragon_komodo" , "Enemy/komodo_dragon.png" },
};

namespace DxLibPlus
{
	/*************************************************************************//*!
			@brief			初期化
			@param			None

			@return			None
	*//**************************************************************************/
	void CGameApp::Initialize(void)
	{
		//リソースフォルダの設定
		SetCurrentDirectory("../Resource");
		//画像の読み込み
		theTextureManager.LoadList(TexFile, TEXKEY_COUNT);
	}
	/*************************************************************************//*!
			@brief			更新
			@param			None

			@return			None
	*//**************************************************************************/
	void CGameApp::Update(void)
	{

	}
	/*************************************************************************//*!
			@brief			描画
			@param			None

			@return			None
	*//**************************************************************************/
	void CGameApp::Render(void)
	{
		//表示位置計算(中央寄せ)
		int x = (CGraphicsUtillities::GetTargetWidth() - theTextureManager.GetWidth(TexFile[TEXKEY_DRAGON_KOMODO].key)) * 0.5f;
		//ドラゴンの描画
		DxLib::DrawGraph(x, PlayerRectW, theTextureManager.GetGraphHandle(TexFile[TEXKEY_DRAGON_KOMODO].key), true);
		//コマンド四角の描画
		DxLib::DrawBox(CommandRectX, CommandRectY, CommandRectX + CommandRectW, CommandRectY + CommandRectH, DxLib::GetColor(255, 255, 255), false);
		DxLib::DrawBox(MessageRectX, MessageRectY, MessageRectX + MessageRectW, MessageRectY + MessageRectH, DxLib::GetColor(255, 255, 255), false);
		DxLib::DrawBox(PlayerRectX, PlayerRectY, PlayerRectX + PlayerRectW, PlayerRectY + PlayerRectH, DxLib::GetColor(255, 255, 255), false);
	}
	/*************************************************************************//*!
			@brief			解放
			@param			None

			@return			None
	*//**************************************************************************/
	void CGameApp::Release(void)
	{
	}
}
