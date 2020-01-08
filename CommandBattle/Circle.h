#pragma once
#include	"Base.h"


/*****************************************************************************************************************************
 *
 *												円クラス
 *
 ****************************************************************************************************************************/
class CCircle {
private:
	SCircle			circle;		//円の構造体情報
public:
	CCircle() : circle(SCircleSet(0,0,0)){}
	CCircle(float r, Vector2<float> pos) : circle(SCircleSet(r,pos.x,pos.y)) {}
	CCircle(float r, float x, float y) : circle(SCircleSet(r,x,y)) {}

	bool			CollisionCircle(CCircle cir);			//円との衝突判定
	bool			CollisionRect(SRectangle rect);			//四角との衝突判定
	bool			CollisionPoint(Vector2<int> pos);		//点との衝突判定
	void			Draw(unsigned int Color, bool Fill);	//描画
	void			Draw(Vector2<float> pos, unsigned int Color, bool Fill);		//描画
	void			Draw(float posX, float posY, unsigned int Color, bool Fill);	//描画
	void			SetCircle(SCircle cir);					//円情報セット
	void			SetCircle(float r, Vector2<float> pos);	//円情報セット
	void			SetCircle(float r, float x, float y);	//円情報セット
	SCircle			GetSCircle() { return circle; }			//円情報取得
};
