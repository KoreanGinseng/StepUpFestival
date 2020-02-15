#include "GameApp.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//ゲーム本体
	CGameApp gameApp;

	//初期化
	CGraphicsUtillities::ChangeWindowMode(true);
	CGraphicsUtillities::SetWindowSize(1024, 768);
	CGraphicsUtillities::SetWindowTitle("コマンドバトル");

	//ＤＸライブラリ初期化処理
	if (CDxLibUtillities::DxLibInit() == -1)
	{
		return -1;
	}

	//初期化
	gameApp.Initialize();

	//ゲームループ
	while (CDxLibUtillities::ProcessMessage() == 0)
	{
		//更新
		gameApp.Update();

		//描画

		gameApp.Render();
	}

	//解放
	gameApp.Release();

	//ＤＸライブラリ使用の終了処理
	CDxLibUtillities::DxLibEnd();
	return 0;
}