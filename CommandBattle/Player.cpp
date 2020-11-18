/*************************************************************************//*!

					@file	Player.cpp
					@brief	プレイヤークラス

															@author	いのうえ
															@date	2020.02.21
*//**************************************************************************/

//INCLUDE
#include "Player.h"
#include "GameScene.h"

//コマンドリスト
std::string gCommandList[] = {
	"たたかう",
	"とくぎ",
	"にげる",
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
		std::string buff = CDxLibUtilities::WStringToString(wstr);
		int length = (int)buff.length();
		int indentCnt = 0;
		int strlen = 0;
		std::string str = "";
		while (length > indentCnt && strlen >= 0)
		{
			//改行区切りで文字列取得
			str = CDxLibUtilities::GetSpalateString(buff, "\n", strlen, indentCnt);
			//ステータスコマンドの場合
			if (str == "status")
			{
				//HPの取得
				str = CDxLibUtilities::GetSpalateString(buff, "\n", strlen, indentCnt);
				m_Status.hp = std::atoi(str.c_str());
				m_OffsetHp = m_Status.hp;
				//ATTACKの取得
				str = CDxLibUtilities::GetSpalateString(buff, "\n", strlen, indentCnt);
				m_Status.attack = std::atoi(str.c_str());
			}
			//スキルコマンドの場合
			else if (str == "skill")
			{
				Skill addData;
				//スキル名取得
				str = CDxLibUtilities::GetSpalateString(buff, "\n", strlen, indentCnt);
				addData.name = str;
				//スキル攻撃倍率取得
				str = CDxLibUtilities::GetSpalateString(buff, "\n", strlen, indentCnt);
				addData.rate = static_cast<float>(std::atof(str.c_str()));
				//エフェクトの種類取得
				str = CDxLibUtilities::GetSpalateString(buff, "\n", strlen, indentCnt);
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
		CGameScene::SetMessage("どうする？");
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
		//カーソルを動かす
		CursorMove();

		//選択が枠外に行かないようにする
		CursorOver();

		//状態ごとにエンターキーを押したときの操作を分ける
		if (theInput.IsKeyPush(KEY_INPUT_RETURN))
		{
			//決定音を鳴らす
			theSoundManager.Play(SoundFile[SOUNDKEY_SE_ENTER].key);
			switch (m_State)
			{
			case COMMAND_WAIT:
				EnterWait();
				break;
			case COMMAND_SKILL:
				EnterSkill();
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
		//状態によって表示色を変える
		switch (m_State)
		{
		case COMMAND_ATTACK:
			Color = DxLib::GetColor(128, 128, 128);
		case COMMAND_WAIT:
			if (m_bDead)
			{
				Color = DxLib::GetColor(192, 64, 64);
			}
			for (int i = 0; i < 3; i++)
			{
				DxLib::DrawFormatString(CommandRectX + FontSize, CommandRectY + i * (FontSize + FontMargin) + FontMargin, Color, "%s", gCommandList[i].c_str());
			}
			break;
			//スキルページの表示
		case COMMAND_SKILL:
			for (int i = 0; i < static_cast<int>(m_SkillList.size()); i++)
			{
				//スキルリストが表示数を超えている場合ページ切り替えできるようにする
				int scrlCnt = (m_Cursor / LineMax);
				if (scrlCnt)
				{
					scroll = 0;
					scroll = ((FontSize + FontMargin) * LineMax) * scrlCnt;
					if (i < LineMax * scrlCnt)
					{
						continue;
					}
				}
				DxLib::DrawFormatString(CommandRectX + FontSize, CommandRectY + i * (FontSize + FontMargin) + FontMargin - scroll, Color, "%s", m_SkillList[i].name.c_str());
			}
			break;
		default:
			break;
		}
		//カーソルの表示
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
		DxLib::DrawFormatString(PlayerRectX + static_cast<int>((PlayerRectW - FontSize * 5) * 0.5f), PlayerRectY + (FontSize + FontMargin) * 1, Color, "HP  : %4d", (m_Status.hp <= 9999) ? m_Status.hp : 9999);
		DxLib::DrawFormatString(PlayerRectX + static_cast<int>((PlayerRectW - FontSize * 5) * 0.5f), PlayerRectY + (FontSize + FontMargin) * 2, Color, "ATK : %4d", (m_Status.attack <= 9999) ? m_Status.attack : 9999);
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
	// ********************************************************************************
	/// <summary>
	/// 切り替え処理
	/// </summary>
	/// <created>いのうえ,2020/02/21</created>
	/// <changed>いのうえ,2020/02/21</changed>
	// ********************************************************************************
	void CPlayer::TurnStart(void)
	{
		//カーソルを一番上にセットする
		m_Cursor = 0;
		//待機状態
		m_State = COMMAND_WAIT;
		//メッセージ変更
		CGameScene::SetMessage("どうする？");

	}
	// ********************************************************************************
	/// <summary>
	/// カーソル移動処理
	/// </summary>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	void CPlayer::CursorMove(void)
	{
		//上キーを押したら選択を上にする
		if (theInput.IsKeyPush(KEY_INPUT_UP))
		{
			m_Cursor--;
			theSoundManager.Play(SoundFile[SOUNDKEY_SE_SELECT].key);
		}
		//下キーを押したら選択を下にする
		else if (theInput.IsKeyPush(KEY_INPUT_DOWN))
		{
			m_Cursor++;
			theSoundManager.Play(SoundFile[SOUNDKEY_SE_SELECT].key);
		}
		//左キーを押したら選択を1ページ分上にする
		else if (theInput.IsKeyPush(KEY_INPUT_LEFT))
		{
			m_Cursor -= LineMax;
			theSoundManager.Play(SoundFile[SOUNDKEY_SE_SELECT].key);
		}
		//右キーを押したら選択を1ページ分下にする
		else if (theInput.IsKeyPush(KEY_INPUT_RIGHT))
		{
			m_Cursor += LineMax;
			theSoundManager.Play(SoundFile[SOUNDKEY_SE_SELECT].key);
		}
	}
	// ********************************************************************************
	/// <summary>
	/// カーソルをリスト数以上超えないようにする処理
	/// </summary>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	void CPlayer::CursorOver(void)
	{
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
	}
	// ********************************************************************************
	/// <summary>
	/// 決定ボタンを押したとき選んだコマンドによって状態を変化させる処理
	/// </summary>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	void CPlayer::EnterWait(void)
	{
		//状態取得
		m_State = static_cast<CommandState>(m_Cursor + 1);
		//通常攻撃の場合
		if (m_State == COMMAND_ATTACK)
		{
			//攻撃倍率1倍
			m_AttackRate = 1.0f;
			//斬撃エフェクト開始
			theEffectManager.Start(SKILL_SLASH);
			//斬撃音を鳴らす
			theSoundManager.Play(SoundFile[SOUNDKEY_SE_SLASH].key);
			//行動終了なので敵のターンへ移行する
			theTurnManager.SetTurn(TURN_ENEMY);
			//メッセージを変更
			CGameScene::SetMessage("プレイヤーの攻撃！");
		}
		//終了を押された場合
		else if (m_State == COMMAND_EXIT)
		{
			//アプリ終了
			m_bEnd = true;
			//PostQuitMessage(0);
		}
		//上記以外はカーソルを戻すだけ
		else
		{
			m_Cursor = 0;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// スキルを決めたときの処理
	/// </summary>
	/// <created>いのうえ,2020/02/23</created>
	/// <changed>いのうえ,2020/02/23</changed>
	// ********************************************************************************
	void CPlayer::EnterSkill(void)
	{
		//スキルの一番最後(戻るコマンド)なら一つ戻る
		if (m_Cursor == m_SkillList.size() - 1)
		{
			m_State = COMMAND_WAIT;
			return;
		}
		//状態を攻撃に変更
		m_State = COMMAND_ATTACK;
		//攻撃倍率を選んだスキルの倍率にセットする
		m_AttackRate = m_SkillList[m_Cursor].rate;
		//選んだスキルのエフェクトを発生させる
		theEffectManager.Start(m_SkillList[m_Cursor].effect);
		//音の番号を取得
		int sound = SOUNDKEY_BGM_COUNT + m_SkillList[m_Cursor].effect;
		//スキルにあった音を鳴らす
		theSoundManager.Play(SoundFile[sound].key);
		//行動終了なので敵のターンへ移行する
		theTurnManager.SetTurn(TURN_ENEMY);
		//メッセージにスキル名を表示させる
		CGameScene::SetMessage("プレイヤーの" + m_SkillList[m_Cursor].name + "！");
		//カーソルのリセット
		m_Cursor = 0;
	}
}

