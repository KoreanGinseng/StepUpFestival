#include "Game.h"
#include "SceneManager.h"
#include "GameDefine.h"

const char battleTitle[] = "��������";
const char* battleMenu[] = {
	"��������",
	"�ɂ���",
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
	m_Battle.Create(battleTitle, battleMenu, 2);
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
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�Q�[���V�[��\n�G���^�[�L�[�Ń^�C�g����");
	m_Battle.Render();
}

void CGame::Release(void)
{
	m_Battle.Release();
}
