#include	"SceneManager.h"
#include	"GameDefine.h"
#include	"Game.h"
#include	"Title.h"

bool CSceneManager::Load(void)
{
	CSceneManager::GetManager()->m_pScenes[SCENE_TITLE] = NEW CTitle();
	CSceneManager::GetManager()->m_pScenes[SCENE_GAME] = NEW CGame();



	for (int i = 0; i < SCENE_COUNT; i++)
	{
		if (CSceneManager::GetManager()->m_pScenes[i] == nullptr)
		{
			return false;
		}
		if (!CSceneManager::GetManager()->m_pScenes[i]->Load())
		{
			return false;
		}
	}
	//for (int i = 0; i < SCENE_EFFECT_COUNT; i++)
	//{
	//	if (CSceneManager::GetManager()->m_pEffectScenes[i] == nullptr)
	//	{
	//		return false;
	//	}
	//	if (!CSceneManager::GetManager()->m_pEffectScenes[i]->Load())
	//	{
	//		return false;
	//	}
	//}
	return true;
}