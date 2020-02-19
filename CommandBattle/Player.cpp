#include "Player.h"

std::string gCommandList[] = {
	"たたかう",
	"とくぎ",
	"どうぐ",
};

namespace DxLibPlus
{
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <returns>None</returns>
	/// <created>いのうえ,2020/02/17</created>
	/// <changed>いのうえ,2020/02/17</changed>
	// ********************************************************************************
	CPlayer::CPlayer(void) :
		CChara(),
		m_Cursor(0),
		m_State(COMMAND_WAIT)
	{
	}

	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <returns>None</returns>
	/// <created>いのうえ,2020/02/17</created>
	/// <changed>いのうえ,2020/02/17</changed>
	// ********************************************************************************
	CPlayer::~CPlayer(void)
	{
	}

	// ********************************************************************************
	/// <summary>
	/// 読み込み
	/// </summary>
	/// <returns>true  成功</param>
	/// 			 false 失敗</returns>
	/// <created>いのうえ,2020/02/17</created>
	/// <changed>いのうえ,2020/02/17</changed>
	// ********************************************************************************
	bool CPlayer::Load(void)
	{
		//ファイルを開く
		std::wifstream ifs("PlayerStatus.txt", std::ios::in);
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
		while (length > indentCnt)
		{
			int strlen = buff.find_first_of("\n", indentCnt) - indentCnt;
			std::string str = buff.substr(indentCnt, strlen);
			indentCnt += strlen + 1;
			//ステータスコマンドの場合
			if (str == "status")
			{

			}
			//スキルコマンドの場合
			else if (str == "skill")
			{
				Skill addData;
				addData.effect = (str == "FIRE") ? SKILL_FIRE : (str == "ICE") ? SKILL_ICE : SKILL_THUNDER;
				//スキルの登録
				m_SkillList.push_back(addData);
			}
		}
		return true;
	}

	// ********************************************************************************
	/// <summary>
	/// 初期化
	/// </summary>
	/// <created>いのうえ,2020/02/17</created>
	/// <changed>いのうえ,2020/02/17</changed>
	// ********************************************************************************
	void CPlayer::Initialize(void)
	{
		m_Cursor = 0;
		m_State = COMMAND_WAIT;
	}

	// ********************************************************************************
	/// <summary>
	/// 更新
	/// </summary>
	/// <created>いのうえ,2020/02/19</created>
	/// <changed>いのうえ,2020/02/19</changed>
	// ********************************************************************************
	void CPlayer::Update(void)
	{
		//上キーを押したら選択を上にする
		if (DxLib::CheckHitKey(KEY_INPUT_UP))
		{
			m_Cursor--;
		}
		//下キーを押したら選択を下にする
		else if (DxLib::CheckHitKey(KEY_INPUT_DOWN))
		{
			m_Cursor++;
		}
		//選択できる最大
		int listmax = 0;
		//状態ごとに操作を変える
		switch (m_State)
		{
		case COMMAND_ATTACK:
		case COMMAND_WAIT:
			listmax = 2;
			break;
		case COMMAND_SKILL:
			listmax = static_cast<int>(m_SkillList.size());
			break;
		default:
			break;
		}
		//選択が枠外に行かないようにする
		if (m_Cursor < 0)
		{
			m_Cursor = listmax;
		}
		else if (m_Cursor > listmax)
		{
			m_Cursor = 0;
		}
		//状態ごとにエンターキーを押したときの操作を分ける
		//if (DxLib::CheckHitKey(KEY_INPUT_RETURN))
		if (theInput.IsKeyPush(KEY_INPUT_RETURN))
		{
			switch (m_State)
			{
			case COMMAND_WAIT:
				m_State = static_cast<CommandState>(m_Cursor + 1);
				if (m_State == COMMAND_ATTACK)
				{
					m_AttackRate = 1.0f;
					theTurnManager.SetTurn(TURN_ENEMY);
				}
				break;
			case COMMAND_SKILL:
				m_State = COMMAND_ATTACK;
				m_AttackRate = m_SkillList[m_Cursor].rate;
				break;
			default:
				break;
			}
		}
	}

	// ********************************************************************************
	/// <summary>
	/// 描画
	/// </summary>
	/// <created>いのうえ,2020/02/19</created>
	/// <changed>いのうえ,2020/02/19</changed>
	// ********************************************************************************
	void CPlayer::Render(void)
	{
		switch (m_State)
		{
		case COMMAND_WAIT:
			for (int i = 0; i < 3; i++)
			{
				DxLib::DrawFormatString(CommandRectX + 24, CommandRectY + i * 24 + 4 + i * 4, GetColor(255, 255, 255), "%s", gCommandList[i].c_str());
			}
			break;
		case COMMAND_ATTACK:
			for (int i = 0; i < 3; i++)
			{
				DxLib::DrawFormatString(CommandRectX + 24, CommandRectY + i * 24 + 4 + i * 4, GetColor(128, 128, 128), "%s", gCommandList[i].c_str());
			}
			break;
		case COMMAND_SKILL:
			for (int i = 0; i < m_SkillList.size(); i++)
			{
				DxLib::DrawFormatString(CommandRectX + 24, CommandRectY + i * 24 + 4 + i * 4, GetColor(255, 255, 255), "%s", m_SkillList[i].name.c_str());
			}
			break;
		case COMMAND_ITEM:
			break;
		default:
			break;
		}
	}

	// ********************************************************************************
	/// <summary>
	/// 解放
	/// </summary>
	/// <created>いのうえ,2020/02/19</created>
	/// <changed>いのうえ,2020/02/19</changed>
	// ********************************************************************************
	void CPlayer::Release(void)
	{
		m_SkillList.clear();
	}
}

