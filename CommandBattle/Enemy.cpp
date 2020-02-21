#include "Enemy.h"

namespace DxLibPlus
{
	CEnemy::CEnemy(void) :
		CChara(),
		m_Type(ENE_RED)
	{
	}

	CEnemy::~CEnemy(void)
	{
	}

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

	void CEnemy::Initialize(void)
	{
		//敵の種類をランダムで決める
		m_Type = static_cast<EnemyType>(CDxLibUtillities::Random(ENE_COUNT) - 1);
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
		m_bDead = false;
		m_Status.hp = m_OffsetHp;
		m_DamageWait = 0;
	}

	void CEnemy::Update(void)
	{
	}

	void CEnemy::Render(void)
	{
		if ((m_DamageWait % 3 == 1) || (m_bDead && m_DamageWait <= 0))
		{
			return;
		}
		//表示位置計算(中央寄せ)
		float x = (CGraphicsUtillities::GetTargetWidth() - theTextureManager.GetWidth(TexFile[m_TexKey].key)) * 0.5f;
		//ドラゴンの描画
		DxLib::DrawGraph(static_cast<int>(x), PlayerRectW, m_GraphHandle, true);
	}
}

