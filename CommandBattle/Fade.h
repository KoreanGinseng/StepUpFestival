#pragma once
#include "SceneEffectBase.h"

//フェードクラス
class CFade : public CSceneEffectBase
{
public:
	CFade(void);							//! コンストラクタ
	virtual ~CFade(void);					//! デストラクタ
	virtual void Update(void) override;		//! 更新
	virtual void Render(void) override;		//! 描画
};

