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
	if (g_pInput->IsKeyPush(KEY_INPUT_RETURN))
	{
		CSceneManager::ChangeScene(SCENE_TITLE);
	}
}

void CGame::Render(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ゲームシーン\nエンターキーでタイトルへ");
}

void CGame::Release(void)
{
}
