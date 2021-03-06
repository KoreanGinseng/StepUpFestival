#define _CRT_SECURE_NO_WARNINGS
#include "GameApp.h"
#include "GameDefine.h"
#include "resource.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	DxLib::SetOutApplicationLogValidFlag(false);

	//ゲーム本体
	CGameApp gameApp;

	//初期化
	CGraphicsUtillities::ChangeWindowMode(true);
	CGraphicsUtillities::SetWindowSize(1024, 768);
	CGraphicsUtillities::SetWindowTitle("コマンドバトル");
	CGraphicsUtillities::SetWindowIcon(IDI_ICON1);

	//ＤＸライブラリ初期化処理
	if (CDxLibUtilities::DxLibInit() == -1)
	{
		return -1;
	}

	//初期化
	CGraphicsUtillities::SetDrawScreen(DX_SCREEN_BACK);
	CGraphicsUtillities::SetFontSize(FontSize);
	gameApp.Initialize();

	//ゲームループ
	while (CDxLibUtilities::ProcessMessage() == 0)
	{
		//更新
		theInput.RefreshKey();
		//エスケープキーで終了処理
		if (theInput.IsKeyPush(KEY_INPUT_ESCAPE))
		{
			PostQuitMessage(0);
		}
		theTurnManager.RefreshTurn();
		theEffectManager.Update();
		gameApp.Update();

		//描画
		CGraphicsUtillities::ClearDrawScreen();
		gameApp.Render();
		CGraphicsUtillities::ScreenFlip();
	}

	//解放
	gameApp.Release();

	//ＤＸライブラリ使用の終了処理
	CDxLibUtilities::DxLibEnd();
	return 0;
}