#include "Player.h"

std::string gCommandList[] = {
	"たたかう",
	"とくぎ",
	"どうぐ",
	"ゲーム終了",
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
			//スキルコマンドの場合
			else if (str == "skill")
			{
				Skill addData;
				//スキル名取得
				strlen = buff.find_first_of("\n", indentCnt) - indentCnt;
				str = buff.substr(indentCnt, strlen);
				indentCnt += strlen + 1;
				addData.name = str;
				//スキル攻撃倍率取得
				strlen = buff.find_first_of("\n", indentCnt) - indentCnt;
				str = buff.substr(indentCnt, strlen);
				indentCnt += strlen + 1;
				addData.rate = static_cast<float>(std::atof(str.c_str()));
				//エフェクトの種類取得
				strlen = buff.find_first_of("\n", indentCnt) - indentCnt;
				str = buff.substr(indentCnt, strlen);
				indentCnt += strlen + 1;
				addData.effect = (str == "FIRE") ? SKILL_FIRE : (str == "ICE") ? SKILL_ICE : (str == "THUNDER") ? SKILL_THUNDER : SKILL_SLASH;
				//スキルの登録
				m_SkillList.push_back(addData);
			}
		}
		//スキル列最後に戻るコマンドを追加する
		Skill backCommand;
		backCommand.name = "戻る";
		backCommand.rate = 0.0f;
		backCommand.effect = SKILL_SLASH;
		m_SkillList.push_back(backCommand);
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
		m_bDead = false;
		m_Status.hp = m_OffsetHp;
		m_Cursor = 0;
		m_State = COMMAND_WAIT;
		gMessage = "どうする？";
		m_DamageWait = 0;
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
		if (theInput.IsKeyPush(KEY_INPUT_UP))
		{
			m_Cursor--;
		}
		//下キーを押したら選択を下にする
		else if (theInput.IsKeyPush(KEY_INPUT_DOWN))
		{
			m_Cursor++;
		}
		//左キーを押したら選択を1ページ分上にする
		else if (theInput.IsKeyPush(KEY_INPUT_LEFT))
		{
			m_Cursor -= LineMax;
		}
		//右キーを押したら選択を1ページ分下にする
		else if (theInput.IsKeyPush(KEY_INPUT_RIGHT))
		{
			m_Cursor += LineMax;
		}
		//選択できる最大
		int listmax = 0;
		//状態ごとに操作を変える
		switch (m_State)
		{
		case COMMAND_ATTACK:
		case COMMAND_WAIT:
			listmax = 3;
			break;
		case COMMAND_SKILL:
			listmax = static_cast<int>(m_SkillList.size()) - 1;
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
		if (theInput.IsKeyPush(KEY_INPUT_RETURN))
		{
			switch (m_State)
			{
			case COMMAND_WAIT:
				m_State = static_cast<CommandState>(m_Cursor + 1);
				if (m_State == COMMAND_ATTACK)
				{
					m_AttackRate = 1.0f;
					theEffectManager.Start(SKILL_SLASH);
					theTurnManager.SetTurn(TURN_ENEMY);
					gMessage = "プレイヤーの攻撃！";
				}
				else if (m_State == COMMAND_EXIT)
				{
					PostQuitMessage(0);
				}
				else
				{
					m_Cursor = 0;
				}
				break;
			case COMMAND_SKILL:
				//スキルの一番最後(戻るコマンド)なら一つ戻る
				if (m_Cursor == m_SkillList.size() - 1)
				{
					m_State = COMMAND_WAIT;
					break;
				}
				m_State = COMMAND_ATTACK;
				m_AttackRate = m_SkillList[m_Cursor].rate;
				theEffectManager.Start(m_SkillList[m_Cursor].effect);
				theTurnManager.SetTurn(TURN_ENEMY);
				gMessage = "プレイヤーの" + m_SkillList[m_Cursor].name + "！";
				m_Cursor = 0;
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
		//コマンド部分の表示
		unsigned int Color = DxLib::GetColor(255, 255, 255);
		int scroll = 0;
		switch (m_State)
		{
		case COMMAND_ATTACK:
			Color = DxLib::GetColor(128, 128, 128);
		case COMMAND_WAIT:
			if (m_bDead)
			{
				Color = DxLib::GetColor(192, 64, 64);
			}
			for (int i = 0; i < 4; i++)
			{
				DxLib::DrawFormatString(CommandRectX + FontSize, CommandRectY + i * (FontSize + FontMargin) + FontMargin, Color, "%s", gCommandList[i].c_str());
			}
			break;
		case COMMAND_SKILL:
			for (int i = 0; i < static_cast<int>(m_SkillList.size()); i++)
			{
				//スキルリストが表示数を超えている場合ページ切り替えできるようにする
				int scrlCnt = (m_Cursor / LineMax);
				if (scrlCnt)
				{
					scroll = 0;
					scroll = ((FontSize + FontMargin) * LineMax) * scrlCnt;
					if (i < LineMax)
					{
						continue;
					}
				}
				DxLib::DrawFormatString(CommandRectX + FontSize, CommandRectY + i * (FontSize + FontMargin) + FontMargin - scroll, Color, "%s", m_SkillList[i].name.c_str());
			}
			break;
		case COMMAND_ITEM:
			break;
		default:
			break;
		}
		int cursorGraph = theTextureManager.GetGraphHandle(TexFile[TEXKEY_CURSOR].key);
		DxLib::DrawGraph(CommandRectX, CommandRectY + m_Cursor * (FontSize + FontMargin) + FontMargin - scroll, cursorGraph, true);
	}

	// ********************************************************************************
	/// <summary>
	/// ステータス描画
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CPlayer::RenderStatus(void)
	{
		unsigned int Color = DxLib::GetColor(255, 255, 255);
		if (m_bDead)
		{
			Color = DxLib::GetColor(192, 64, 64);
		}
		DxLib::DrawFormatString(PlayerRectX + static_cast<int>((PlayerRectW - FontSize * 5) * 0.5f), PlayerRectY, Color, "ステータス");
		DxLib::DrawFormatString(PlayerRectX + FontSize, PlayerRectY + (FontSize + FontMargin) * 1, Color, "HP  : %d", m_Status.hp);
		DxLib::DrawFormatString(PlayerRectX + FontSize, PlayerRectY + (FontSize + FontMargin) * 2, Color, "ATK : %d", m_Status.attack);
		DxLib::DrawFormatString(PlayerRectX + static_cast<int>((PlayerRectW - FontSize * 3.5f) * 0.5f), PlayerRectY + 28 * 4, Color, "PLAYER1");
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

	void CPlayer::TurnStart(void)
	{
		m_Cursor = 0;
		m_State = COMMAND_WAIT;
		gMessage = "どうする？";

	}
}

