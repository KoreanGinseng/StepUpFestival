#include "TitleScene.h"
#include "DxLibPlus.h"
#include "GameDefine.h"

namespace DxLibPlus
{
	CTitleScene::CTitleScene(void)
		: CSceneBase()
	{
		//�T�E���h�S�X�g�b�v
		theSoundManager.Stop();
	}

	CTitleScene::~CTitleScene(void)
	{
	}
	
	void CTitleScene::Initialize(void)
	{
		//�o�g��BGM�̍Đ�
		theSoundManager.Play(SoundFile[SOUNDKEY_BGM_BATTLE].key);
		m_Enemy.Initialize();
	}
	
	void CTitleScene::Update(void)
	{
		if (theInput.IsKeyPush(KEY_INPUT_RETURN))
		{
			//���艹��炷
			theSoundManager.Play(SoundFile[SOUNDKEY_SE_ENTER].key);
			m_bEnd = true;
			m_NextScene =SCENE_GAME;
		}
	}
	
	void CTitleScene::Render(void)
	{
		m_Enemy.Render();

		std::string title = "�R�}���h�o�g��";
		std::string next = "Enter�L�[�ŃQ�[����\n   Esc�L�[�ŏI��";
		SetFontSize(72);
		int tw = DxLib::GetDrawFormatStringWidth(title.c_str());
		DxLib::DrawFormatString((CGraphicsUtillities::GetTargetWidth() - tw) / 2, 100, DxLib::GetColor(255, 255, 255), title.c_str());
		SetFontSize(24);
		tw = DxLib::GetDrawFormatStringWidth(next.c_str());
		DxLib::DrawFormatString((CGraphicsUtillities::GetTargetWidth() - tw) / 2, 600, DxLib::GetColor(255, 255, 0), next.c_str());
	}
	
	void CTitleScene::Release(void)
	{
	}
}