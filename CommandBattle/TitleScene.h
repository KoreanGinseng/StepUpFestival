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
		//�R���X�g���N�^
		CTitleScene(void);
		//�f�X�g���N�^
		virtual ~CTitleScene(void) override;
		//������
		virtual void Initialize(void) override;
		//�X�V
		virtual void Update(void) override;
		//�`��
		virtual void Render(void) override;
		//���
		virtual void Release(void) override;
	};
}

