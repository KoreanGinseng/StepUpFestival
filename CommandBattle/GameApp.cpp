#include "GameApp.h"
#include "SceneManager.h"


CGameApp::CGameApp(void)
{
}


CGameApp::~CGameApp(void)
{
}

int CGameApp::Initialize(void)
{
	CSceneManager::Create(SCENE_TITLE);
	return 0;
}

void CGameApp::Update(void)
{
	CSceneManager::Update();
}

void CGameApp::Render(void)
{
	CSceneManager::Render();
}

void CGameApp::Release(void)
{
	CSceneManager::Release();
}
