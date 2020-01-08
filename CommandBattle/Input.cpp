#include	"Input.h"

void CInput::RefreshKey() {
	for (int i = 0; i < 256; i++) {
		m_OldKey[i] = m_Key[i];
	}
	GetHitKeyStateAll(KeyStateAll); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i < 256; i++) {
		if (KeyStateAll[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			m_Key[i]++;     // ���Z
		}
		else {              // ������Ă��Ȃ����
			m_Key[i] = 0;   // 0�ɂ���
		}
	}
	for (int i = 0; i < 2; i++) {
		m_OldMouse[i] = m_Mouse[i];
	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		// ������Ă���
		m_Mouse[0]++;
	}
	else
	{
		// ������Ă��Ȃ�
		m_Mouse[0] = 0;
	}
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
	{
		// ������Ă���
		m_Mouse[1]++;
	}
	else
	{
		// ������Ă��Ȃ�
		m_Mouse[1] = 0;
	}
}

bool CInput::IsKeyPush(int KeyCode) {
	return (m_Key[KeyCode] == 1) ? true : false;
}

bool CInput::IsKeyHold(int KeyCode) {
	return (m_Key[KeyCode] != 0) ? true : false;
}

bool CInput::IsKeyPull(int KeyCode) {
	return (m_OldKey[KeyCode] != 0) ? ((m_Key[KeyCode] == 0) ? true : false) : false;
}

bool CInput::IsMousePush(int MouseCode) {
	int m = (MouseCode == MOUSE_INPUT_LEFT) ? 0	: ((MouseCode == MOUSE_INPUT_RIGHT) ? 1 : -1);
	return (m == -1) ? false : ((m_Mouse[m] == 1) ? true : false);
}

bool CInput::IsMouseHold(int MouseCode) {
	int m = (MouseCode == MOUSE_INPUT_LEFT) ? 0 : ((MouseCode == MOUSE_INPUT_RIGHT) ? 1 : -1);
	return (m == -1) ? false : ((m_Mouse[m] != 0) ? true : false);
}

bool CInput::IsMousePull(int MouseCode) {
	int m = (MouseCode == MOUSE_INPUT_LEFT) ? 0 : ((MouseCode == MOUSE_INPUT_RIGHT) ? 1 : -1);
	return (m == -1) ? false : (m_OldMouse[m] != 0) ? ((m_Mouse[m] == 0) ? true : false) : false;
}

int CInput::GetMousePos(int *XBuf, int *YBuf) {
	return GetMousePoint(XBuf, YBuf);
}

int CInput::GetMousePos(Vector2<int> *pos) {
	return GetMousePoint(&pos->x, &pos->y);
}