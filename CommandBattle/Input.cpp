#include	"Input.h"

void CInput::RefreshKey() {
	for (int i = 0; i < 256; i++) {
		m_OldKey[i] = m_Key[i];
	}
	GetHitKeyStateAll(KeyStateAll); // 全てのキーの入力状態を得る
	for (int i = 0; i < 256; i++) {
		if (KeyStateAll[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			m_Key[i]++;     // 加算
		}
		else {              // 押されていなければ
			m_Key[i] = 0;   // 0にする
		}
	}
	for (int i = 0; i < 2; i++) {
		m_OldMouse[i] = m_Mouse[i];
	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		// 押されている
		m_Mouse[0]++;
	}
	else
	{
		// 押されていない
		m_Mouse[0] = 0;
	}
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
	{
		// 押されている
		m_Mouse[1]++;
	}
	else
	{
		// 押されていない
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