#include "SceneManager.h"

CSceneManager::CSceneManager(void) :
m_pScenes(),
m_pCurrentScene(nullptr),
m_CurrentSceneNo(0)
{
	for (int i = 0; i < SCENE_COUNT; i++)
	{
		m_pScenes[i] = nullptr;
	}
}

CSceneManager::~CSceneManager(void)
{
}

CSceneManager * CSceneManager::GetManager(void)
{
	static CSceneManager obj;
	return &obj;
}

CSceneBase * CSceneManager::GetScene(void)
{
	return CSceneManager::GetManager()->m_pCurrentScene;
}
CSceneBase * CSceneManager::GetScene(const int & no)
{
	return CSceneManager::GetManager()->m_pScenes[no];
}

void CSceneManager::ChangeScene(const int & no)
{
	//現在のシーンを変更
	CSceneManager::GetManager()->m_CurrentSceneNo = no;
	//次のシーンに変更
	CSceneManager::GetManager()->m_pCurrentScene = CSceneManager::GetScene(no);
	CSceneManager::GetManager()->m_pCurrentScene->Initialize();
}

bool CSceneManager::Create(const int & no)
{
	CSceneManager::Release();
	if (!CSceneManager::Load())
	{
		return false;
	}
	CSceneManager::ChangeScene(no);
	return true;
}

void CSceneManager::Update(void)
{
	CSceneManager::GetManager()->m_pCurrentScene->Update();
}

void CSceneManager::Render(void)
{
	CSceneManager::GetManager()->m_pCurrentScene->Render();
}

void CSceneManager::Release(void)
{
	for (int i = 0; i < SCENE_COUNT; i++)
	{
		if (CSceneManager::GetManager()->m_pScenes[i] == nullptr)
		{
			continue;
		}
		CSceneManager::GetManager()->m_pScenes[i]->Release();
		if (CSceneManager::GetManager()->m_pScenes[i])
		{
			delete CSceneManager::GetManager()->m_pScenes[i];
			CSceneManager::GetManager()->m_pScenes[i] = nullptr;
		}
	}
}
