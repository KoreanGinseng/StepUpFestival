#include "Game.h"
#include "SceneManager.h"
#include "GameDefine.h"

const char battleTitle[] = "たたかう";
const char* battleMenu[] = {
	"こうげき",
	"にげる1",
	"にげる2",
	"にげる3",
	"にげる4",
	"にげる5",
	"にげる6",
};

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
	m_Battle.Create(battleTitle, battleMenu, 7);
	m_Battle.Show(100, 100);
}

void CGame::Update(void)
{
	if (g_pInput->IsKeyPush(KEY_INPUT_RETURN))
	{
		CSceneManager::ChangeScene(SCENE_TITLE);
	}
	if (m_Battle.IsShow())
	{
		m_Battle.Update();
	}
}

void CGame::Render(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ゲームシーン\nエンターキーでタイトルへ");
	m_Battle.Render();
}

void CGame::Release(void)
{
	m_Battle.Release();
}
