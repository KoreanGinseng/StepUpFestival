#include	"Rectangle.h"

/*****************************************************************************************************************************
  *
  *												四角の描画
  *
  *		Color		:	色
  *		Fill		:	塗りつぶしフラグ
  *
  ****************************************************************************************************************************/
void CRectangle::Draw(unsigned int Color, bool Fill) {
	DrawBox((int)rect.Left, (int)rect.Top, (int)rect.Right, (int)rect.Bottom, Color, Fill);
}


/*****************************************************************************************************************************
  *
  *												円との衝突判定
  *
  *		cir		:	衝突判定を調べる円
  *
  ****************************************************************************************************************************/
bool CRectangle::CollisionCircle(SCircle cir) {
	bool A, B, C, D, E, F;
	A = B = C = D = E = F = false;

	if ((cir.x > rect.Left) &&
		(cir.x < rect.Right) &&
		(cir.y > rect.Top - cir.r) &&
		(cir.y < rect.Bottom + cir.r)) {
		A = true;
	}
	if ((cir.x > rect.Left - cir.r) &&
		(cir.x < rect.Right + cir.r) &&
		(cir.y > rect.Top) &&
		(cir.y < rect.Bottom)) {
		B = true;
	}
	float a = rect.Left - cir.x;
	float b = rect.Top - cir.y;
	float c = sqrtf(a * a + b * b);
	if (c < cir.r) {
		C = true;
	}
	float d = rect.Right - cir.x;
	float e = rect.Top - cir.y;
	float f = sqrtf(d * d + e * e);
	if (f < cir.r) {
		D = true;
	}
	float g = rect.Left - cir.x;
	float h = rect.Bottom - cir.y;
	float i = sqrtf(g * g + h * h);
	if (i < cir.r) {
		E = true;
	}
	float j = rect.Right - cir.x;
	float k = rect.Bottom - cir.y;
	float l = sqrtf(j * j + k * k);
	if (l < cir.r) {
		F = true;
	}
	if (A || B || C || D || E || F) {
		return true;
	}
	return false;
}

/*****************************************************************************************************************************
  *
  *												点との衝突判定
  *
  *		pos		:	衝突判定を調べる点
  *
  ****************************************************************************************************************************/
bool CRectangle::CollisionPoint(Vector2<int> pos) {
	if (rect.Top < pos.y && rect.Bottom > pos.y &&
		rect.Left < pos.x && rect.Right > pos.x) {
		return true;
	}
	return false;
}

/*****************************************************************************************************************************
  *
  *												四角との衝突判定
  *
  *		crect		:	衝突判定を調べる四角
  *
  ****************************************************************************************************************************/
bool CRectangle::CollisionRect(CRectangle crect) {
	if (rect.Top > crect.GetSRect().Top && rect.Top < crect.GetSRect().Bottom &&
		rect.Left > crect.GetSRect().Left && rect.Left < crect.GetSRect().Right) {
		return true;
	}
	if (rect.Bottom > crect.GetSRect().Top && rect.Bottom < crect.GetSRect().Bottom &&
		rect.Left > crect.GetSRect().Left && rect.Left < crect.GetSRect().Right) {
		return true;
	}
	if (rect.Top > crect.GetSRect().Top && rect.Top < crect.GetSRect().Bottom &&
		rect.Right > crect.GetSRect().Left && rect.Right < crect.GetSRect().Right) {
		return true;
	}
	if (rect.Bottom > crect.GetSRect().Top && rect.Bottom < crect.GetSRect().Bottom &&
		rect.Right > crect.GetSRect().Left && rect.Right < crect.GetSRect().Right) {
		return true;
	}
	return false;
}

/*****************************************************************************************************************************
  *
  *												四角情報セット
  *
  *		srect		:	セットする四角情報
  *
  ****************************************************************************************************************************/
void CRectangle::SetRect(SRectangle srect) {
	rect = srect;
}

/*****************************************************************************************************************************
  *
  *												四角情報セット
  *
  *		left		:	セットする左
  *		top			:	セットする上
  *		right		:	セットする右
  *		bottom		:	セットする下
  *
  ****************************************************************************************************************************/
void CRectangle::SetRect(float left, float top, float right, float bottom) {
	rect.Left = left;
	rect.Top = top;
	rect.Right = right;
	rect.Bottom = bottom;
}

void CRectangle::SetRect(Vector2<float> start, Vector2<float> end) {
	rect.Left = start.x;
	rect.Top = start.y;
	rect.Right = end.x;
	rect.Bottom = end.y;
}

/*****************************************************************************************************************************
  *
  *												四角情報に加算
  *
  *		srect		:	加算する四角情報
  *
  ****************************************************************************************************************************/
void CRectangle::AddRect(SRectangle rectA) {
	rect.Left += rectA.Left;
	rect.Top += rectA.Top;
	rect.Right += rectA.Right;
	rect.Bottom += rectA.Bottom;
}

/*****************************************************************************************************************************
  *
  *												四角情報に加算
  *
  *		left		:	加算する左
  *		top			:	加算する上
  *		right		:	加算する右
  *		bottom		:	加算する下
  *
  ****************************************************************************************************************************/
void CRectangle::AddRect(float left, float top, float right, float bottom) {
	rect.Left += left;
	rect.Top += top;
	rect.Right += right;
	rect.Bottom += bottom;
}

void CRectangle::AddRect(Vector2<float> start, Vector2<float> end) {
	rect.Left += start.x;
	rect.Top += start.y;
	rect.Right += end.x;
	rect.Bottom += end.y;
}