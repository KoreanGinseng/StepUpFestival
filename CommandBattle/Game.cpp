#include "Game.h"
#include "SceneManager.h"
#include "GameDefine.h"

CGame::CGame(void)
{
}

CGame::~CGame(void)
{
}

bool CGame::Load(void)
{
	return true;
}

void CGame::Initialize(void)
{
}

void CGame::Update(void)
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !CSceneManager::IsEffectIn())
	{
		CSceneManager::SceneEffectIn(SCENE_EFFECT_FADE, 3.0f);
		CSceneManager::ChangeScene(SCENE_TITLE);
	}
}

void CGame::Render(void)
{
	CGraphicsUtilities::RenderString(0, 0, "ゲームシーン\nエンターキーでタイトルへ");
}

void CGame::Release(void)
{
}
