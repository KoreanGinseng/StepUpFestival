#pragma once
#include "SceneBase.h"

//�V�[���G�t�F�N�g�x�[�X�N���X
class CSceneEffectBase : public CSceneBase
{
protected:
	int			m_Type;							//! 0 = IN, 1 = OUT
	float		m_Alpha;						//! �A���t�@�l
	float		m_Spd;							//! �؂�ւ����x
	bool		m_bEnd;							//! �؂�ւ��I���t���O
public:
	CSceneEffectBase(void);						//! �R���X�g���N�^
	virtual ~CSceneEffectBase(void);			//! �f�X�g���N�^
	virtual bool Load(void) override;			//! �Ǎ�
	virtual void Initialize(void) override;		//! ������
	virtual void Release(void) override {}		//! ���
	void	SetType(const int& type);			//! �t�F�[�h�^�C�v�̐ݒ�
	void	SetSpd(const float& spd);			//! �؂�ւ����x�̐ݒ�
	int		GetType(void) const;				//! �t�F�[�h�^�C�v�擾
	float	GetSpd(void) const;					//! �؂�ւ����x�擾
	bool	IsEnd(void) const;					//! �؂�ւ��I���t���O�擾
};

