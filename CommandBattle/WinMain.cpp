#include "GameApp.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�C���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);

	//��ʃT�C�Y�̕ύX
	SetGraphMode(640, 480, 16);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;				// �G���[���N�����璼���ɏI��
	}

	// �`����ʂ𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);
	
	//�Q�[���{��
	CGameApp	gameApp;
	//�Q�[���̏�����
	if (gameApp.Initialize() != 0)
	{
		return -1;
	}

	//�Q�[�����[�v
	while (ProcessMessage() == 0)
	{
		//FPS�̌v��
		g_pFps->Update();
		//�X�V
		gameApp.Update();

		//�`��
		//��ʃN���A
		if (ClearDrawScreen() == -1)
		{
			return -1;
		}

		gameApp.Render();

		//����ʂ�\��ʂɔ��f
		if (ScreenFlip() == -1)
		{
			return -1;
		}

		//FPS�̒���
		g_pFps->Wait();
	}

	gameApp.Release();
	DxLib::DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I�� 
}