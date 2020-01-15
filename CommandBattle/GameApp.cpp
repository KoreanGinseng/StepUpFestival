//INCLUDE
#include	"GameApp.h"

//MGR
#include	"SceneManager.h"
#include	"AnimationManager.h"
#include	"TextureManager.h"
#include	"SoundManager.h"
#include	"EffectManager.h"


CGameApp::CGameApp(void)
{
}


CGameApp::~CGameApp(void)
{
}

int CGameApp::Initialize(void)
{
	SetCurrentDirectory("../Resource");
	if (!CTextureManager::Load("bomc.png"))
	{
		return -1;
	}
	if (!CSoundManager::LoadSE("explosion.mp3"))
	{
		return -1;
	}

	CSceneManager::Create(SCENE_TITLE);

	return 0;
}

void CGameApp::Update(void)
{
	//if (g_pInput->IsKeyPush(KEY_INPUT_X))
	//{
	//	CSoundManager::PlaySE("explosion.mp3", DX_PLAYTYPE_NORMAL);
	//}
	
	CSoundManager::Update();
	CEffectManager::Update();

	CSceneManager::Update();
}

void CGameApp::Render(void)
{
	//CTextureManager::GetTexture("bomc.png")->Render(0, 0);
	CSceneManager::Render();
}

void CGameApp::Release(void)
{
	CTextureManager::Release();
	CSoundManager::Release();
	CAnimationManager::Release();
	CEffectManager::Release();
	CSceneManager::Release();
}
