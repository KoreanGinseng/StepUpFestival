#pragma once

//�V�[���x�[�X�N���X
class CSceneBase
{
protected:
public:
	CSceneBase(void);					//! �R���X�g���N�^
	virtual ~CSceneBase(void);			//! �f�X�g���N�^
	virtual bool Load(void) = 0;		//! �Ǎ�
	virtual void Initialize(void) = 0;	//! ������
	virtual void Update(void) = 0;		//! �X�V
	virtual void Render(void) = 0;		//! �`��
	virtual void RenderDebug(void) {}	//! �f�o�b�O�`��
	virtual void Release(void) = 0;		//! ���
};

