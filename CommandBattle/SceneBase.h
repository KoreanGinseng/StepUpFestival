#pragma once

//シーンベースクラス
class CSceneBase
{
protected:
public:
	CSceneBase(void);					//! コンストラクタ
	virtual ~CSceneBase(void);			//! デストラクタ
	virtual bool Load(void) = 0;		//! 読込
	virtual void Initialize(void) = 0;	//! 初期化
	virtual void Update(void) = 0;		//! 更新
	virtual void Render(void) = 0;		//! 描画
	virtual void RenderDebug(void) {}	//! デバッグ描画
	virtual void Release(void) = 0;		//! 解放
};

