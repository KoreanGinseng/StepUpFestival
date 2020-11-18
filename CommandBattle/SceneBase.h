#pragma once

namespace DxLibPlus
{
	//�V�[����ՃN���X
	class CSceneBase
	{
	protected:

		int  m_NextScene{    -1 }; //!< ���̃V�[���ԍ�
		bool m_bEnd     { false }; //!< �V�[���I���t���O

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
		// ���̃V�[���擾
		virtual int GetNextScene(void) const { return m_NextScene; }
		// �V�[���I���t���O�̎擾
		virtual bool IsEnd(void) const { return m_bEnd; }
	};
}

