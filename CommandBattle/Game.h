#pragma once
#include "SceneBase.h"
#include "Mof.h"

//�Q�[���N���X
class CGame : public CSceneBase
{
public:
	CGame(void);								//! �R���X�g���N�^
	virtual ~CGame(void);						//! �f�X�g���N�^
	virtual bool Load(void) override;			//! �Ǎ�
	virtual void Initialize(void) override;		//! ������
	virtual void Update(void) override;			//! �X�V
	virtual void Render(void) override;			//! �`��
	virtual void Release(void) override;		//! ���
};

