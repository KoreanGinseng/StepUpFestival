#pragma once
#include "SceneBase.h"
#include "Enemy.h"

namespace DxLibPlus
{
	class CTitleScene : public CSceneBase
	{
	private:

		CEnemy m_Enemy;

	public:
		//コンストラクタ
		CTitleScene(void);
		//デストラクタ
		virtual ~CTitleScene(void) override;
		//初期化
		virtual void Initialize(void) override;
		//更新
		virtual void Update(void) override;
		//描画
		virtual void Render(void) override;
		//解放
		virtual void Release(void) override;
	};
}

