#pragma once
//INCLUDE
#include "SceneBase.h"
#include "GameDefine.h"
#include "Player.h"
#include "Enemy.h"

namespace DxLibPlus
{
	//�Q�[���V�[���N���X
	class CGameScene : public CSceneBase
	{
	protected:

		CPlayer		m_Player;					//!<�v���C���[
		CEnemy		m_Enemy;					//!<�G
		bool		m_bChangeTurn = false;		//!<�^�[���ύX�t���O
		int			m_GameState = STATE_GAME;	//!<�Q�[���̏��

		std::string m_Message = "";				//!<���b�Z�[�W

	public:
		//�R���X�g���N�^
		CGameScene(void);
		//�f�X�g���N�^
		virtual ~CGameScene(void) override;
		//������
		virtual void Initialize(void) override;
		//�X�V
		virtual void Update(void) override;
		//�`��
		virtual void Render(void) override;
		//���
		virtual void Release(void) override;

	private:
		// ********************************************************************************
		/// <summary>
		/// �Q�[���N���A��Ԃ̏���
		/// </summary>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		void GameStateClear(void);
		// ********************************************************************************
		/// <summary>
		/// �Q�[���I�[�o�[��Ԃ̏���
		/// </summary>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		void GameStateOver(void);
		// ********************************************************************************
		/// <summary>
		/// ���X�^�[�g���̏�����
		/// </summary>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		void ReStart(void);
		// ********************************************************************************
		/// <summary>
		/// �v���C���[�ւ̃_���[�W����
		/// </summary>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		void DmgPlayer(void);
		// ********************************************************************************
		/// <summary>
		/// �G�ւ̃_���[�W����
		/// </summary>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		void DmgEnemy(void);
		// ********************************************************************************
		/// <summary>
		/// �v���C���[�̃^�[���ɂȂ��܂ł̏���
		/// </summary>
		/// <created>���̂���,2020/02/21</created>
		/// <changed>���̂���,2020/02/21</changed>
		// ********************************************************************************
		void RefreshPlayer(void);
		// ********************************************************************************
		/// <summary>
		/// �^�[�����ς�������̎��̃^�[���܂łȂ�����
		/// </summary>
		/// <param name="turn">���݂̃^�[��</param>
		/// <created>���̂���,2020/02/23</created>
		/// <changed>���̂���,2020/02/23</changed>
		// ********************************************************************************
		void RefreshChangeTurn(const Turn& turn);
		// ********************************************************************************
		/// <summary>
		/// �Q�[���I�[�o�[�̊Ď�
		/// </summary>
		/// <created>���̂���,2020/02/23</created>
		/// <changed>���̂���,2020/02/23</changed>
		// ********************************************************************************
		void CheckGameOver(void);
	};
}

