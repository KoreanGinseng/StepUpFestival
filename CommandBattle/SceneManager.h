#pragma once
#include	"DxLibPlus.h"
#include	"SceneBase.h"
#include	"GameDefine.h"

//�V�[���Ǘ��N���X
class CSceneManager
{
private:
	CSceneBase* m_pScenes[SCENE_COUNT];									//! �S�V�[��
	CSceneBase* m_pCurrentScene;										//! ���݂̃V�[��
	int			m_CurrentSceneNo;										//! ���݂̃V�[���ԍ�
	CSceneManager(void);												//! �R���X�g���N�^
	~CSceneManager(void);												//! �f�X�g���N�^
	static CSceneBase* GetScene(const int& no);							//! �w��ԍ��̃V�[���擾
	static bool Load(void);												//! �Ǎ�
public:
	static CSceneManager* GetManager(void);								//! �}�l�[�W���[�Ăяo��
	static CSceneBase* GetScene(void);									//! ���݂̃V�[���擾
	static void ChangeScene(const int& no);								//! �V�[���؂�ւ�
	static bool Create(const int& no);									//! �V�[�������Ə����V�[���ݒ�
	static void Update(void);											//! �X�V
	static void Render(void);											//! �`��
	static void Release(void);											//! ���
};

