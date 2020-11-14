#pragma once

namespace DxLibPlus
{
	//シーン基盤クラス
	class CSceneBase
	{
	public:
		//コンストラクタ
		CSceneBase(void) {}
		//デストラクタ
		virtual ~CSceneBase(void) {}
		//初期化
		virtual void Initialize(void) = 0;
		//更新
		virtual void Update(void) = 0;
		//描画
		virtual void Render(void) = 0;
		//解放
		virtual void Release(void) = 0;
	};
}

