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
	if (g_pInput->IsKeyPush(KEY_INPUT_RETURN))
	{
		CSceneManager::ChangeScene(SCENE_GAME);
	}
}

void CTitle::Render(void)
{
	DrawFormatString(0, 0, COLOR_WHITE, "タイトルシーン\nエンターキーでゲームへ");
}

void CTitle::Release(void)
{
}
