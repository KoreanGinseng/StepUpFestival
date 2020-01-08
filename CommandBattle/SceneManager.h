#pragma once
#include	"Mof.h"
#include	"SceneBase.h"
#include	"SceneEffectBase.h"
#include	"GameDefine.h"

//�V�[���Ǘ��N���X
class CSceneManager
{
private:
	CSceneBase* m_pScenes[SCENE_COUNT];									//! �S�V�[��
	CSceneBase* m_pCurrentScene;										//! ���݂̃V�[��
	int			m_CurrentSceneNo;										//! ���݂̃V�[���ԍ�
	CSceneEffectBase* m_pEffectScenes[SCENE_EFFECT_COUNT];				//! �V�[���؂�ւ��p�S�G�t�F�N�g
	CSceneEffectBase* m_pEffectSceneIn;									//! �V�[��IN�G�t�F�N�g
	CSceneEffectBase* m_pEffectSceneOut;								//! �V�[��OUT�G�t�F�N�g
	bool		m_bEffectIn;											//! IN�G�t�F�N�g�t���O
	bool		m_bEffectOut;											//! OUT�G�t�F�N�g�t���O
	bool		m_bSceneChange;											//! �V�[���؂�ւ����t���O
	CSceneManager(void);												//! �R���X�g���N�^
	~CSceneManager(void);												//! �f�X�g���N�^
	static CSceneBase* GetScene(const int& no);							//! �w��ԍ��̃V�[���擾
	static CSceneEffectBase* GetEffectScene(const int& type);			//! �w��ԍ��̃V�[���G�t�F�N�g�擾
	static bool Load(void);												//! �Ǎ�
public:
	static CSceneManager* GetManager(void);								//! �}�l�[�W���[�Ăяo��
	static CSceneBase* GetScene(void);									//! ���݂̃V�[���擾
	static bool IsEffectIn(void);										//! IN�G�t�F�N�g�t���O�擾
	static void ChangeScene(const int& no);								//! �V�[���؂�ւ�
	static void SceneEffectIn(const int& type, const float& spd);		//! �V�[��IN�G�t�F�N�g�w��
	static void SceneEffectOut(const int& type, const float& spd);		//! �V�[��OUT�G�t�F�N�g�w��
	static bool Create(const int& no);									//! �V�[�������Ə����V�[���ݒ�
	static void Update(void);											//! �X�V
	static void Render(void);											//! �`��
	static void RenderEffect(void);										//! �V�[���G�t�F�N�g�`��
	static void Release(void);											//! ���
};

