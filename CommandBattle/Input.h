#pragma once
#include	"Base.h"
#include	"Singleton.h"

class CInput {
	friend	SingletonHolder<CInput>;
private:
	char	KeyStateAll[256];
	int		m_Key[256];
	int		m_OldKey[256];
	int     m_Mouse[2];
	int     m_OldMouse[2];
	CInput() : KeyStateAll(), m_Key(), m_OldKey(), m_Mouse(), m_OldMouse(){}
public:
	void	RefreshKey();
	bool	IsKeyPush(int KeyCode);
	bool	IsKeyHold(int KeyCode);
	bool	IsKeyPull(int KeyCode);
	bool	IsMousePush(int MouseCode);
	bool	IsMouseHold(int MouseCode);
	bool	IsMousePull(int MouseCode);
	int		GetMousePos(int *XBuf, int *YBuf);
	int		GetMousePos(Vector2<int> *pos);
};

// SingletonHolderを使う際のお決まりtypedef
typedef SingletonHolder<CInput>    CInputHolder;
// 海外のコードでよくみかけるdefineやexternで使うthe...形式(ちょっとオシャレ?)
#define theCInput CInputHolder::getInstance()
#define g_pInput CInputHolder::getInstancePtr()