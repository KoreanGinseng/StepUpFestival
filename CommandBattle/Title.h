#pragma once
#include "SceneBase.h"
#include "Mof.h"

//�^�C�g���N���X
class CTitle : public CSceneBase
{
public:
	CTitle(void);								//! �R���X�g���N�^
	virtual ~CTitle(void);						//! �f�X�g���N�^
	virtual bool Load(void) override;			//! �Ǎ�
	virtual void Initialize(void) override;		//! ������
	virtual void Update(void) override;			//! �X�V
	virtual void Render(void) override;			//! �`��
	virtual void Release(void) override;		//! ���
};

