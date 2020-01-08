#pragma once
#include	"DxLibPlus.h"
#include	"SceneBase.h"
#include	"GameDefine.h"

//シーン管理クラス
class CSceneManager
{
private:
	CSceneBase* m_pScenes[SCENE_COUNT];									//! 全シーン
	CSceneBase* m_pCurrentScene;										//! 現在のシーン
	int			m_CurrentSceneNo;										//! 現在のシーン番号
	CSceneManager(void);												//! コンストラクタ
	~CSceneManager(void);												//! デストラクタ
	static CSceneBase* GetScene(const int& no);							//! 指定番号のシーン取得
	static bool Load(void);												//! 読込
public:
	static CSceneManager* GetManager(void);								//! マネージャー呼び出し
	static CSceneBase* GetScene(void);									//! 現在のシーン取得
	static void ChangeScene(const int& no);								//! シーン切り替え
	static bool Create(const int& no);									//! シーン生成と初期シーン設定
	static void Update(void);											//! 更新
	static void Render(void);											//! 描画
	static void Release(void);											//! 解放
};

