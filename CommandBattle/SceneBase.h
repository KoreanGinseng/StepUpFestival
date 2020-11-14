#pragma once

namespace DxLibPlus
{
	//�V�[����ՃN���X
	class CSceneBase
	{
	public:
		//�R���X�g���N�^
		CSceneBase(void) {}
		//�f�X�g���N�^
		virtual ~CSceneBase(void) {}
		//������
		virtual void Initialize(void) = 0;
		//�X�V
		virtual void Update(void) = 0;
		//�`��
		virtual void Render(void) = 0;
		//���
		virtual void Release(void) = 0;
	};
}

