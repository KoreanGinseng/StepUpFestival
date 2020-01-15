#pragma once
#include "SceneBase.h"
#include "DxLibPlus.h"
#include "Menu.h"

//ゲームクラス
class CGame : public CSceneBase
{
private:
	CMenu	m_Battle;
public:
	CGame(void);								//! コンストラクタ
	virtual ~CGame(void);						//! デストラクタ
	virtual bool Load(void) override;			//! 読込
	virtual void Initialize(void) override;		//! 初期化
	virtual void Update(void) override;			//! 更新
	virtual void Render(void) override;			//! 描画
	virtual void Release(void) override;		//! 解放
};

