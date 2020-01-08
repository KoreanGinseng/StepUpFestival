/*****************************************************************************************************************************
 *
 *													テクスチャヘッダー
 *
 ****************************************************************************************************************************/
#pragma once

#include "Base.h"

 /*****************************************************************************************************************************
  *
  *													テクスチャクラス
  *
  ****************************************************************************************************************************/
class CTexture {
private:
	int			m_SizeX;		//画像の横幅
	int			m_SizeY;		//画像の縦幅
	int			m_Handle;		//画像ソース
public:
	CTexture() : m_SizeX(0), m_SizeY(0), m_Handle(0) {}
	~CTexture() {}
	void Load(const TCHAR* FileName) { m_Handle = LoadGraph(FileName); GetGraphSize(m_Handle, &m_SizeX, &m_SizeY); }	//読み込み
	int GetWidth() { GetGraphSize(m_Handle, &m_SizeX, &m_SizeY); return m_SizeX; }		//画像横幅取得
	int GetHeight() { GetGraphSize(m_Handle, &m_SizeX, &m_SizeY); return m_SizeY; }		//画像縦幅取得
	int GetHandle() { GetGraphSize(m_Handle, &m_SizeX, &m_SizeY); return m_Handle; }	//画像ソース取得

	void Render(int x, int y) { DrawGraph(x, y, m_Handle, true); }
	void Render(int x, int y, SRectangle rect) { DrawRectGraph(x, y, (int)(rect.Left), (int)(rect.Top), (int)(rect.Right), (int)(rect.Bottom), m_Handle, true, true); }
	void Render(float x, float y) { DrawGraphF(x, y, m_Handle, true); }
	void Render(float x, float y, SRectangle rect) { DrawRectGraphF(x, y, (int)(rect.Left), (int)(rect.Top), (int)(rect.Right), (int)(rect.Bottom), m_Handle, true); }
	void Render(int x, int y, bool transflag) { DrawGraph(x, y, m_Handle, transflag); }
	void Render(int x, int y, SRectangle rect, bool transflag) { DrawRectGraph(x, y, (int)(rect.Left), (int)(rect.Top), (int)(rect.Right), (int)(rect.Bottom), m_Handle, transflag); }
	void Render(int x, int y, SRectangle rect, bool transflag, bool turnflag) { DrawRectGraph(x, y, (int)(rect.Left), (int)(rect.Top), (int)(rect.Right), (int)(rect.Bottom), m_Handle, transflag, turnflag); }
	void Render(float x, float y, bool transflag) { DrawGraphF(x, y, m_Handle, transflag); }
	void Render(float x, float y, SRectangle rect, bool transflag) { DrawRectGraphF(x, y, (int)(rect.Left), (int)(rect.Top), (int)(rect.Right), (int)(rect.Bottom), m_Handle, transflag); }
	void Render(float x, float y, SRectangle rect, bool transflag, bool turnflag) { DrawRectGraphF(x, y, (int)(rect.Left), (int)(rect.Top), (int)(rect.Right), (int)(rect.Bottom), m_Handle, transflag, turnflag); }

	void Release() { DeleteGraph(m_Handle); }
};