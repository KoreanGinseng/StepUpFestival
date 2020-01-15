#include	"Menu.h"

/**
 * �R���X�g���N�^
 *
 */
CMenu::CMenu() :
	m_cx(0.0f),
	m_cy(0.0f),
	m_HSpace(12),
	m_VSpace(8),
	m_Count(0),
	m_pTitle(NULL),
	m_pItem(NULL),
	m_Select(0),
	m_bShow(false),
	m_bEnter(false),
	m_Rect(),
	m_HeaderRect() {
}

/**
 * �f�X�g���N�^
 *
 */
CMenu::~CMenu() {
	Release();
}

/**
 * ����
 * ���j���[�̍��ڂ�ݒ肵�Ċ�{�̋�`�����߂�
 *
 * ����
 * [in]			pTitle			���j���[�^�C�g��
 * [in]			pItem			���j���[����
 * [in]			cnt				���j���[���ڂ̐�
 */
void CMenu::Create(const char* pTitle, const char** pItem, int cnt) {
	//�Â��f�[�^�̉��
	Release();
	//�����̕������ۑ�
	m_Count = cnt;
	m_pTitle = (char*)malloc(strlen(pTitle) + 1);
	strcpy(m_pTitle, pTitle);
	m_pItem = (char**)malloc(sizeof(char*) * cnt);
	for (int i = 0; i < m_Count; i++)
	{
		m_pItem[i] = (char*)malloc(strlen(pItem[i]) + 1);
		strcpy(m_pItem[i], pItem[i]);
	}
	//���j���[�̕�����̍ő�A�ŏ���`�����߂�
	CRectangle trec;
	//CGraphicsUtilities::CalculateStringRect(0, 0, m_pTitle, trec);
	trec.SetRect(0, 0, strlen(m_pTitle) * 24, 24);
	float r = max(m_Rect.GetSRect().Right, trec.GetSRect().Right + m_HSpace * 2);
	float b =  trec.GetSRect().Bottom + m_VSpace * 2;
	m_Rect.SetRect(0, 0, r, b);
	m_HeaderRect = m_Rect;
	for (int i = 0; i < m_Count; i++)
	{
		//CGraphicsUtilities::CalculateStringRect(0, 0, m_pItem[i], trec);
		float hr = max(m_Rect.GetSRect().Right, trec.GetSRect().Right + m_HSpace * 2);
		SRectangle hrect = m_HeaderRect.GetSRect();
		SRectangle rect = m_Rect.GetSRect();
		m_HeaderRect.SetRect(hrect.Left, hrect.Top, hr, hrect.Bottom);
		m_Rect.SetRect(rect.Left, rect.Top, hr, rect.Bottom + trec.GetSRect().Bottom + m_VSpace);
	}
	SRectangle rect = m_Rect.GetSRect();
	m_Rect.SetRect(rect.Left, rect.Top, rect.Right, rect.Bottom + m_VSpace);
}

/**
 * ���
 *
 */
void CMenu::Release(void) {
	if (m_pTitle)
	{
		free(m_pTitle);
		m_pTitle = NULL;
	}
	if (m_pItem)
	{
		for (int i = 0; i < m_Count; i++)
		{
			free(m_pItem[i]);
		}
		free(m_pItem);
		m_pItem = NULL;
		m_Count = 0;
	}
	m_Rect = CRectangle(0, 0, 0, 0);
}

/**
 * �\��
 * �����̈ʒu�𒆐S�Ƀ��j���[��\������
 *
 * ����
 * [in]			cx				X���W
 * [in]			cy				Y���W
 */
void CMenu::Show(float cx, float cy) {
	m_cx = cx;
	m_cy = cy;
	m_bShow = true;
	m_bEnter = false;
	m_Select = 0;
	float w = m_Rect.GetSRect().Right - m_Rect.GetSRect().Left;
	float h = m_Rect.GetSRect().Bottom - m_Rect.GetSRect().Top;
	m_Rect.SetRect(m_cx, m_cy, m_cx + w, m_cy + h);
	float hw = m_HeaderRect.GetSRect().Right - m_HeaderRect.GetSRect().Left;
	float hh = m_HeaderRect.GetSRect().Bottom - m_HeaderRect.GetSRect().Top;
	m_HeaderRect.SetRect(m_Rect.GetSRect().Left, m_Rect.GetSRect().Top, m_Rect.GetSRect().Left + hw, m_Rect.GetSRect().Top + hh);
}

/**
 * �X�V
 *
 */
void CMenu::Update(void) {
	if (!m_bShow)
	{
		return;
	}
	//�㉺�̃L�[�őI��
	if (g_pInput->IsKeyPush(KEY_INPUT_UP))
	{
		m_Select--;
		if (m_Select < 0)
		{
			m_Select = m_Count - 1;
		}
	}
	else if (g_pInput->IsKeyPush(KEY_INPUT_DOWN))
	{
		m_Select++;
		if (m_Select >= m_Count)
		{
			m_Select = 0;
		}
	}
	//Enter�Ō���
	if (g_pInput->IsKeyPush(KEY_INPUT_RETURN))
	{
		m_bEnter = true;
	}
}

/**
 * �`��
 *
 */
void CMenu::Render(void) {
	if (!m_bShow)
	{
		return;
	}
	//���j���[�̔w�i�`��
	m_Rect.Draw(COLOR_BLACK, TRUE);
	m_Rect.Draw(COLOR_WHITE, FALSE);
	m_HeaderRect.Draw(COLOR_BLACK, TRUE);
	m_HeaderRect.Draw(COLOR_WHITE, FALSE);
	//���ڂ̕�����`�悷��
	CRectangle trec;
	trec.SetRect(0, 0, strlen(m_pTitle) * 24, 24);
	float py = m_Rect.GetSRect().Top + m_VSpace;
	//CGraphicsUtilities::CalculateStringRect(0, 0, m_pTitle, trec);
	DrawFormatString(m_cx, py, COLOR_WHITE, m_pTitle);
	py += trec.GetSRect().Bottom + m_VSpace;
	for (int i = 0; i < m_Count; i++)
	{
		//CGraphicsUtilities::CalculateStringRect(0, 0, m_pItem[i], trec);
		DrawFormatString(m_cx, py + m_VSpace, ((m_Select == i) ? GetColor(255, 255, 255) : GetColor(128, 128, 128)), m_pItem[i]);
		py += trec.GetSRect().Bottom + m_VSpace;
	}
}