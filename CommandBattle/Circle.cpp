#include	"Circle.h"



/*****************************************************************************************************************************
  *
  *												�~���Z�b�g
  *
  *		cir		:	�Z�b�g����~���
  *
  ****************************************************************************************************************************/
void CCircle::SetCircle(SCircle cir) {
	circle.r = cir.r;
	circle.x = cir.x;
	circle.y = cir.y;
}

/*****************************************************************************************************************************
  *
  *												�~���Z�b�g
  *
  *		r		:	�Z�b�g���锼�a
  *		pos		:	�Z�b�g������W
  *
  ****************************************************************************************************************************/
void CCircle::SetCircle(float r, Vector2<float> pos) {
	circle.r = r;
	circle.x = pos.x;
	circle.y = pos.y;
}

void CCircle::SetCircle(float r,float x, float y) {
	circle.r = r;
	circle.x = x;
	circle.y = y;
}

/*****************************************************************************************************************************
  *
  *												�~�`��
  *
  *		Color		:	�`�悷��F
  *		Fill		:	�h��Ԃ��t���O
  *
  ****************************************************************************************************************************/
void CCircle::Draw(unsigned int Color, bool Fill) {
	DrawCircle((int)circle.x, (int)circle.y, (int)circle.r, Color, Fill);
}

/*****************************************************************************************************************************
  *
  *												�~�`��
  *
  *		pos			:	�`�悷����W
  *		Color		:	�`�悷��F
  *		Fill		:	�h��Ԃ��t���O
  *
  ****************************************************************************************************************************/
void CCircle::Draw(Vector2<float> pos, unsigned int Color, bool Fill) {
	DrawCircle((int)pos.x, (int)pos.y, (int)circle.r, Color, Fill);
}

/*****************************************************************************************************************************
  *
  *												�~�`��
  *
  *		posX		:	�`�悷����WX
  *		posY		:	�`�悷����WY
  *		Color		:	�`�悷��F
  *		Fill		:	�h��Ԃ��t���O
  *
  ****************************************************************************************************************************/
void CCircle::Draw(float posX, float posY, unsigned int Color, bool Fill) {
	DrawCircle((int)posX, (int)posY, (int)circle.r, Color, Fill);
}

/*****************************************************************************************************************************
  *
  *												�~�Ƃ̏Փ˔���
  *
  *		cir		:	�Փ˔���𒲂ׂ�~
  *
  ****************************************************************************************************************************/
bool CCircle::CollisionCircle(CCircle cir) {
	float addR = circle.r + cir.GetSCircle().r;
	float a = circle.x - cir.GetSCircle().x;
	float b = circle.y - cir.GetSCircle().y;
	float c = sqrtf(a*a + b * b);
	if (addR >= c) {
		return true;
	}
	return false;
}

/*****************************************************************************************************************************
  *
  *												�_�Ƃ̏Փ˔���
  *
  *		pos		:	�Փ˔���𒲂ׂ�_
  *
  ****************************************************************************************************************************/
bool CCircle::CollisionPoint(Vector2<int> pos) {
	float a = circle.x - pos.x;
	float b = circle.y - pos.y;
	float c = sqrtf(a * a + b * b);
	if (circle.r >= c) {
		return true;
	}
	return false;
}

/*****************************************************************************************************************************
  *
  *												�l�p�Ƃ̏Փ˔���
  *
  *		rect		:	�Փ˔���𒲂ׂ�l�p
  *
  ****************************************************************************************************************************/
bool CCircle::CollisionRect(SRectangle rect) {
	bool A, B, C, D, E, F;
	A = B = C = D = E = F = false;

	if ((circle.x > rect.Left) &&
		(circle.x < rect.Right) &&
		(circle.y > rect.Top - circle.r) &&
		(circle.y < rect.Bottom + circle.r)) {
		A = true;
	}
	if ((circle.x > rect.Left - circle.r) &&
		(circle.x < rect.Right + circle.r) &&
		(circle.y > rect.Top) &&
		(circle.y < rect.Bottom)) {
		B = true;
	}
	float a = rect.Left - circle.x;
	float b = rect.Top - circle.y;
	float c = sqrtf(a * a + b * b);
	if (c < circle.r) {
		C = true;
	}
	float d = rect.Right - circle.x;
	float e = rect.Top - circle.y;
	float f = sqrtf(d * d + e * e);
	if (f < circle.r) {
		D = true;
	}
	float g = rect.Left - circle.x;
	float h = rect.Bottom - circle.y;
	float i = sqrtf(g * g + h * h);
	if (i < circle.r) {
		E = true;
	}
	float j = rect.Right - circle.x;
	float k = rect.Bottom - circle.y;
	float l = sqrtf(j * j + k * k);
	if (l < circle.r) {
		F = true;
	}
	if (A || B || C || D || E || F) {
		return true;
	}
	return false;
}