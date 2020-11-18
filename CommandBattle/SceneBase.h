#pragma once

namespace DxLibPlus
{
	//シーン基盤クラス
	class CSceneBase
	{
	protected:

		int  m_NextScene{    -1 }; //!< 次のシーン番号
		bool m_bEnd     { false }; //!< シーン終了フラグ

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
		// 次のシーン取得
		virtual int GetNextScene(void) const { return m_NextScene; }
		// シーン終了フラグの取得
		virtual bool IsEnd(void) const { return m_bEnd; }
	};
}

