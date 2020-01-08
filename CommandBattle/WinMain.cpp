#include "DxLib.h"

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
	
	while (ProcessMessage() == 0)
	{
		//�X�V


		//�`��
		//��ʃN���A
		if (ClearDrawScreen() == -1)
		{
			return -1;
		}



		//����ʂ�\��ʂɔ��f
		if (ScreenFlip() == -1)
		{
			return -1;
		}
	}


	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I�� 
}