#pragma once
#include	"DxLibPlus.h"
#include	"AnimationManager.h"

typedef CAnimation CSpriteMotionController;

class CEffect
{
private:
	CTexture* m_pTexture;					//! エフェクト画像
	CSpriteMotionController m_Motion;		//! エフェクトモーション
	bool m_bShow;							//! 表示フラグ
	Vector2<float> m_Pos;					//! 表示座標
public:
	CEffect(void);							//! コンストラクタ
	~CEffect(void);							//! デストラクタ
	bool IsShow(void) const;				//! 表示フラグ取得
	void Start(const Vector2<float>& pos);	//! エフェクトの発生
	bool Load(const std::string& str);		//! ファイルからデータ読み込み
	void Update(void);						//! エフェクト制御
	void Render(void);						//! エフェクト表示
	void Release(void);						//! 解放
};

