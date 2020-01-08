#pragma once
#include "SceneBase.h"

//シーンエフェクトベースクラス
class CSceneEffectBase : public CSceneBase
{
protected:
	int			m_Type;							//! 0 = IN, 1 = OUT
	float		m_Alpha;						//! アルファ値
	float		m_Spd;							//! 切り替え速度
	bool		m_bEnd;							//! 切り替え終了フラグ
public:
	CSceneEffectBase(void);						//! コンストラクタ
	virtual ~CSceneEffectBase(void);			//! デストラクタ
	virtual bool Load(void) override;			//! 読込
	virtual void Initialize(void) override;		//! 初期化
	virtual void Release(void) override {}		//! 解放
	void	SetType(const int& type);			//! フェードタイプの設定
	void	SetSpd(const float& spd);			//! 切り替え速度の設定
	int		GetType(void) const;				//! フェードタイプ取得
	float	GetSpd(void) const;					//! 切り替え速度取得
	bool	IsEnd(void) const;					//! 切り替え終了フラグ取得
};

