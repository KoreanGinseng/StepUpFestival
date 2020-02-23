/*************************************************************************//*!

					@file	Enemy.cpp
					@brief	敵クラス

															@author	いのうえ
															@date	2020.02.21
*//**************************************************************************/

//INCLUDE
#include "Enemy.h"

namespace DxLibPlus
{
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <returns>None</returns>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	CEnemy::CEnemy(void) :
		CChara(),
		m_Type(ENE_RED)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <returns>None</returns>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	CEnemy::~CEnemy(void)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// 読み込み
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	bool CEnemy::Load(void)
	{
		//ファイルを開く
		std::wifstream ifs("EnemyStatus.txt", std::ios::in);
		//開けない場合error
		if (!ifs)
		{
			return false;
		}
		//ファイルの終端まで読み込む
		ifs.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
		std::wstring wstr((std::istreambuf_iterator<wchar_t>(ifs)), std::istreambuf_iterator<wchar_t>());
		std::string buff = CDxLibUtillities::WStringToString(wstr);
		int length = buff.length();
		int indentCnt = 0;
		int strlen = 0;
		std::string str = "";
		while (length > indentCnt && strlen >= 0)
		{
			//改行区切りで文字列取得
			strlen = buff.find_first_of("\n", indentCnt) - indentCnt;
			str = buff.substr(indentCnt, strlen);
			indentCnt += strlen + 1;
			//ステータスコマンドの場合
			if (str == "status")
			{
				//HPの取得
				strlen = buff.find_first_of("\n", indentCnt) - indentCnt;
				str = buff.substr(indentCnt, strlen);
				indentCnt += strlen + 1;
				m_Status.hp = std::atoi(str.c_str());
				m_OffsetHp = m_Status.hp;
				//ATTACKの取得
				strlen = buff.find_first_of("\n", indentCnt) - indentCnt;
				str = buff.substr(indentCnt, strlen);
				indentCnt += strlen + 1;
				m_Status.attack = std::atoi(str.c_str());
			}
		}
		return true;
	}
	// ********************************************************************************
	/// <summary>
	/// 初期化
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CEnemy::Initialize(void)
	{
		//敵の種類をランダムで決める
		m_Type = static_cast<EnemyType>(CDxLibUtillities::Random(ENE_COUNT) - 1);
		//画像のキーを取得しておく
		m_TexKey;
		switch (m_Type)
		{
		case ENE_RED:
			m_TexKey = TEXKEY_DRAGON_RED;
			break;
		case ENE_GREEN:
			m_TexKey = TEXKEY_DRAGON_GREEN;
			break;
		case ENE_BLUE:
			m_TexKey = TEXKEY_DRAGON_BLUE;
			break;
		case ENE_KOMODO:
			m_TexKey = TEXKEY_DRAGON_KOMODO;
			break;
		}
		//画像ハンドルを取得する
		m_GraphHandle = theTextureManager.GetGraphHandle(TexFile[m_TexKey].key);
		//死亡フラグの初期化
		m_bDead = false;
		//体力のセット
		m_Status.hp = m_OffsetHp;
		//ダメージ待機時間の初期化
		m_DamageWait = 0;
	}
	// ********************************************************************************
	/// <summary>
	/// 更新
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CEnemy::Update(void)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// 描画
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CEnemy::Render(void)
	{
		//ダメージをくらっている間もしくは、死んでいれば表示しない
		if ((m_DamageWait % 3 == 1) || (m_bDead && m_DamageWait <= 0))
		{
			return;
		}
		//表示位置計算(中央寄せ)
		float x = (CGraphicsUtillities::GetTargetWidth() - theTextureManager.GetWidth(TexFile[m_TexKey].key)) * 0.5f;
		//ドラゴンの描画
		DxLib::DrawGraph(static_cast<int>(x), PlayerRectH, m_GraphHandle, true);
	}
}

