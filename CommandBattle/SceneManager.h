#pragma once
#include	"Mof.h"
#include	"SceneBase.h"
#include	"SceneEffectBase.h"
#include	"GameDefine.h"

//シーン管理クラス
class CSceneManager
{
private:
	CSceneBase* m_pScenes[SCENE_COUNT];									//! 全シーン
	CSceneBase* m_pCurrentScene;										//! 現在のシーン
	int			m_CurrentSceneNo;										//! 現在のシーン番号
	CSceneEffectBase* m_pEffectScenes[SCENE_EFFECT_COUNT];				//! シーン切り替え用全エフェクト
	CSceneEffectBase* m_pEffectSceneIn;									//! シーンINエフェクト
	CSceneEffectBase* m_pEffectSceneOut;								//! シーンOUTエフェクト
	bool		m_bEffectIn;											//! INエフェクトフラグ
	bool		m_bEffectOut;											//! OUTエフェクトフラグ
	bool		m_bSceneChange;											//! シーン切り替え中フラグ
	CSceneManager(void);												//! コンストラクタ
	~CSceneManager(void);												//! デストラクタ
	static CSceneBase* GetScene(const int& no);							//! 指定番号のシーン取得
	static CSceneEffectBase* GetEffectScene(const int& type);			//! 指定番号のシーンエフェクト取得
	static bool Load(void);												//! 読込
public:
	static CSceneManager* GetManager(void);								//! マネージャー呼び出し
	static CSceneBase* GetScene(void);									//! 現在のシーン取得
	static bool IsEffectIn(void);										//! INエフェクトフラグ取得
	static void ChangeScene(const int& no);								//! シーン切り替え
	static void SceneEffectIn(const int& type, const float& spd);		//! シーンINエフェクト指定
	static void SceneEffectOut(const int& type, const float& spd);		//! シーンOUTエフェクト指定
	static bool Create(const int& no);									//! シーン生成と初期シーン設定
	static void Update(void);											//! 更新
	static void Render(void);											//! 描画
	static void RenderEffect(void);										//! シーンエフェクト描画
	static void Release(void);											//! 解放
};

