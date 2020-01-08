#pragma once
#include	"DxLibPlus.h"

class CGameApp
{
public:
	CGameApp(void);
	~CGameApp(void);
	int Initialize(void);
	void Update(void);
	void Render(void);
	void Release(void);
};

