#pragma once
#include "SceneEffectBase.h"

//�t�F�[�h�N���X
class CFade : public CSceneEffectBase
{
public:
	CFade(void);							//! �R���X�g���N�^
	virtual ~CFade(void);					//! �f�X�g���N�^
	virtual void Update(void) override;		//! �X�V
	virtual void Render(void) override;		//! �`��
};

