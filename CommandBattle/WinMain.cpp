#include "GameApp.h"

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
	gameApp.Initialize();

	//�Q�[�����[�v
	while (CDxLibUtillities::ProcessMessage() == 0)
	{
		//�X�V
		theTurnManager.RefreshTurn();
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