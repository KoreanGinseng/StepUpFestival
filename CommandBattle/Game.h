#pragma once
#include "SceneBase.h"
#include "DxLibPlus.h"
#include "Menu.h"

//�Q�[���N���X
class CGame : public CSceneBase
{
private:
	CMenu	m_Battle;
public:
	CGame(void);								//! �R���X�g���N�^
	virtual ~CGame(void);						//! �f�X�g���N�^
	virtual bool Load(void) override;			//! �Ǎ�
	virtual void Initialize(void) override;		//! ������
	virtual void Update(void) override;			//! �X�V
	virtual void Render(void) override;			//! �`��
	virtual void Release(void) override;		//! ���
};

