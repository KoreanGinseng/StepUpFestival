#pragma once
#include "Base.h"



/*****************************************************************************************************************************
 *
 *												四角クラス
 *
 ****************************************************************************************************************************/
class CRectangle {
private:
	SRectangle		rect;		//四角の構造体情報
public:
	CRectangle() : rect(SRectGet(0,0,0,0)) {}
	CRectangle(float left, float top, float right, float bottom) : rect(SRectGet(left,top,right,bottom)) {}
	CRectangle(Vector2<float> start, Vector2<float> end) : rect(SRectGet(start.x, start.y, end.x, end.y)) {}

	bool			CollisionCircle(SCircle cir);									//円との衝突判定
	bool			CollisionRect(CRectangle rect);									//四角との衝突判定
	bool			CollisionPoint(Vector2<int> pos);								//点との衝突判定
	void			Draw(unsigned int Color, bool Fill);							//描画
	void			SetRect(SRectangle rect);										//四角情報セット
	void			SetRect(float left, float top, float right, float bottom);		//四角情報セット
	void			SetRect(Vector2<float> start, Vector2<float> end);				//四角情報セット
	void			AddRect(SRectangle rectA);										//四角情報に加算
	void			AddRect(float left, float top, float right, float bottom);		//四角情報に加算
	void			AddRect(Vector2<float> start, Vector2<float> end);				//四角情報に加算
	SRectangle		GetSRect() { return rect; }										//四角情報取得
};