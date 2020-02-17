#include "Player.h"

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
		FILE* fp = fopen("PlayerStatus.txt", "rt");
		//開けなかった場合error
		if (fp == NULL)
		{
			return false;
		}
		//文字列を取り込む
		std::string buff;
		//ステータスから読み込み
		fscanf(fp, "%s,", buff);	//status,
		if (buff == "status")
		{
			//体力攻撃の順番で読む
			fscanf(fp, "%d,", &m_Status.hp);
			fscanf(fp, "%d,", &m_Status.attack);
		}
		//先頭にステータスが記述されていない場合error
		else
		{
			fclose(fp);
			return false;
		}
		//スキルを読み込む
		fscanf(fp, "%s,", buff);	//skill,
		if (buff == "skill")
		{
			//スキルの数を取得する
			int skillCnt;
			fscanf(fp, "%d,", &skillCnt);
			//スキルの数だけ読み込む
			for (int i = 0; i < skillCnt; i++)
			{
				Skill addData;
				fscanf(fp, "%s,", &addData.name);
				fscanf(fp, "%f,", &addData.rate);
				fscanf(fp, "%s,", buff);
				addData.effect = (buff == "FIRE") ? SKILL_FIRE : (buff == "ICE") ? SKILL_ICE : SKILL_THUNDER;
				m_SkillList.push_back(addData);
			}
		}
		fclose(fp);
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
			listmax = m_SkillList.size;
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
		if (DxLib::CheckHitKey(KEY_INPUT_RETURN))
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

	void CPlayer::Render(void)
	{
	}

	void CPlayer::Release(void)
	{
	}
}

