#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウインドウモードで起動
	ChangeWindowMode(TRUE);

	//画面サイズの変更
	SetGraphMode(640, 480, 16);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}

	// 描画先画面を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);
	
	while (ProcessMessage() == 0)
	{
		//更新


		//描画
		//画面クリア
		if (ClearDrawScreen() == -1)
		{
			return -1;
		}



		//裏画面を表画面に反映
		if (ScreenFlip() == -1)
		{
			return -1;
		}
	}


	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了 
}