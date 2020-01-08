#include "SceneManager.h"

CSceneManager::CSceneManager(void) :
m_pScenes(),
m_pCurrentScene(nullptr),
m_CurrentSceneNo(0),
m_pEffectScenes(),
m_pEffectSceneIn(nullptr),
m_pEffectSceneOut(nullptr),
m_bEffectIn(false),
m_bEffectOut(false),
m_bSceneChange(false)
{
	for (int i = 0; i < SCENE_COUNT; i++)
	{
		m_pScenes[i] = nullptr;
	}
	for (int i = 0; i < SCENE_EFFECT_COUNT; i++)
	{
		m_pEffectScenes[i] = nullptr;
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

bool CSceneManager::IsEffectIn(void)
{
	return CSceneManager::GetManager()->m_bEffectIn;
}

CSceneBase * CSceneManager::GetScene(const int & no)
{
	return CSceneManager::GetManager()->m_pScenes[no];
}

CSceneEffectBase * CSceneManager::GetEffectScene(const int & type)
{
	return CSceneManager::GetManager()->m_pEffectScenes[type];
}

void CSceneManager::ChangeScene(const int & no)
{
	//現在のシーンを変更
	CSceneManager::GetManager()->m_CurrentSceneNo = no;
	//OUTエフェクトフラグが立っていれば終わるまで切り替えない
	if (CSceneManager::GetManager()->m_bEffectOut)
	{
		CSceneManager::GetManager()->m_bSceneChange = true;
		return;
	}
	//次のシーンに変更
	CSceneManager::GetManager()->m_pCurrentScene = CSceneManager::GetScene(no);
	CSceneManager::GetManager()->m_pCurrentScene->Initialize();
	CSceneManager::GetManager()->m_bSceneChange = false;
	//INエフェクトフラグが立っていればエフェクトを開始
	if (CSceneManager::GetManager()->m_bEffectIn)
	{
		int type = CSceneManager::GetManager()->m_pEffectSceneIn->GetType();
		float spd = CSceneManager::GetManager()->m_pEffectSceneIn->GetSpd();
		CSceneManager::GetManager()->m_bEffectIn = false;
		CSceneManager::GetManager()->SceneEffectIn(type, spd);
	}
}

void CSceneManager::SceneEffectIn(const int & type, const float& spd)
{
	if (CSceneManager::GetManager()->m_bEffectIn)
	{
		return;
	}
	CSceneManager::GetManager()->m_bEffectIn = true;
	CSceneManager::GetManager()->m_pEffectSceneIn = CSceneManager::GetEffectScene(type);
	CSceneManager::GetManager()->m_pEffectSceneIn->SetType(EFFECTTYPE_IN);
	CSceneManager::GetManager()->m_pEffectSceneIn->SetSpd(spd);
	CSceneManager::GetManager()->m_pEffectSceneIn->Initialize();
}

void CSceneManager::SceneEffectOut(const int & type, const float& spd)
{
	if (CSceneManager::GetManager()->m_bEffectOut)
	{
		return;
	}
	CSceneManager::GetManager()->m_bEffectOut = true;
	CSceneManager::GetManager()->m_pEffectSceneOut = CSceneManager::GetEffectScene(type);
	CSceneManager::GetManager()->m_pEffectSceneOut->SetType(EFFECTTYPE_OUT);
	CSceneManager::GetManager()->m_pEffectSceneOut->SetSpd(spd);
	CSceneManager::GetManager()->m_pEffectSceneOut->Initialize();
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
	//シーン切り替えフラグが立っているならOUTエフェクトをかける
	if (CSceneManager::GetManager()->m_bSceneChange)
	{
		if (CSceneManager::GetManager()->m_bEffectOut)
		{
			CSceneManager::GetManager()->m_pEffectSceneOut->Update();
			bool end = CSceneManager::GetManager()->m_pEffectSceneOut->IsEnd();
			CSceneManager::GetManager()->m_bEffectOut = !end;
		}
		//OUTエフェクトが終わればシーンを切り替える
		int no = CSceneManager::GetManager()->m_CurrentSceneNo;
		CSceneManager::GetManager()->ChangeScene(no);
	}
	//INエフェクトフラグが立っていればINエフェクトをかける
	else if (CSceneManager::GetManager()->m_bEffectIn)
	{
		CSceneManager::GetManager()->m_pEffectSceneIn->Update();
		bool end = CSceneManager::GetManager()->m_pEffectSceneIn->IsEnd();
		CSceneManager::GetManager()->m_bEffectIn = !end;
	}
	CSceneManager::GetManager()->m_pCurrentScene->Update();
}

void CSceneManager::Render(void)
{
	CSceneManager::GetManager()->m_pCurrentScene->Render();
}

void CSceneManager::RenderEffect(void)
{
	if (CSceneManager::GetManager()->m_bEffectOut)
	{
		CSceneManager::GetManager()->m_pEffectSceneOut->Render();
	}
	else if (CSceneManager::GetManager()->m_bEffectIn)
	{
		CSceneManager::GetManager()->m_pEffectSceneIn->Render();
	}
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
		MOF_SAFE_DELETE(CSceneManager::GetManager()->m_pScenes[i]);
	}
	for (int i = 0; i < SCENE_EFFECT_COUNT; i++)
	{
		if (CSceneManager::GetManager()->m_pEffectScenes[i] == nullptr)
		{
			continue;
		}
		CSceneManager::GetManager()->m_pEffectScenes[i]->Release();
		MOF_SAFE_DELETE(CSceneManager::GetManager()->m_pEffectScenes[i]);
	}
}
