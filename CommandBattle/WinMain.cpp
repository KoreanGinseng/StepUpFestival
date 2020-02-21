#define _CRT_SECURE_NO_WARNINGS
#include "GameApp.h"
#include "GameDefine.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//�Q�[���{��
	CGameApp gameApp;

	//������
	CGraphicsUtillities::ChangeWindowMode(true);
	CGraphicsUtillities::SetWindowSize(1024, 768);
	CGraphicsUtillities::SetWindowTitle("�R�}���h�o�g��");

	//�c�w���C�u��������������
	if (CDxLibUtillities::DxLibInit() == -1)
	{
		return -1;
	}

	//������
	CGraphicsUtillities::SetDrawScreen(DX_SCREEN_BACK);
	CGraphicsUtillities::SetFontSize(FontSize);
	gameApp.Initialize();

	//�Q�[�����[�v
	while (CDxLibUtillities::ProcessMessage() == 0)
	{
		//�X�V
		theInput.RefreshKey();
		//�G�X�P�[�v�L�[�ŏI������
		if (theInput.IsKeyPush(KEY_INPUT_ESCAPE))
		{
			PostQuitMessage(0);
		}
		theTurnManager.RefreshTurn();
		theEffectManager.Update();
		gameApp.Update();

		//�`��
		CGraphicsUtillities::ClearDrawScreen();
		gameApp.Render();
		CGraphicsUtillities::ScreenFlip();
	}

	//���
	gameApp.Release();

	//�c�w���C�u�����g�p�̏I������
	CDxLibUtillities::DxLibEnd();
	return 0;
}