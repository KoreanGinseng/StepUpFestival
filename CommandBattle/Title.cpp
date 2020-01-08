#include "Title.h"
#include "SceneManager.h"
#include "GameDefine.h"


CTitle::CTitle(void)
{
}

CTitle::~CTitle(void)
{
}

bool CTitle::Load(void)
{
	return true;
}

void CTitle::Initialize(void)
{
}

void CTitle::Update(void)
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !CSceneManager::IsEffectIn())
	{
		CSceneManager::SceneEffectIn(SCENE_EFFECT_FADE, 2.0f);
		CSceneManager::SceneEffectOut(SCENE_EFFECT_FADE, 2.0f);
		CSceneManager::ChangeScene(SCENE_GAME);
	}
}

void CTitle::Render(void)
{
	CGraphicsUtilities::RenderString(0, 0, "タイトルシーン\nエンターキーでゲームへ");
}

void CTitle::Release(void)
{
}
