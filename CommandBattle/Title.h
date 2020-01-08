#pragma once
#include "SceneBase.h"
#include "Mof.h"

//タイトルクラス
class CTitle : public CSceneBase
{
public:
	CTitle(void);								//! コンストラクタ
	virtual ~CTitle(void);						//! デストラクタ
	virtual bool Load(void) override;			//! 読込
	virtual void Initialize(void) override;		//! 初期化
	virtual void Update(void) override;			//! 更新
	virtual void Render(void) override;			//! 描画
	virtual void Release(void) override;		//! 解放
};

