#pragma once
#include "Base.h"



/*****************************************************************************************************************************
 *
 *												�l�p�N���X
 *
 ****************************************************************************************************************************/
class CRectangle {
private:
	SRectangle		rect;		//�l�p�̍\���̏��
public:
	CRectangle() : rect(SRectGet(0,0,0,0)) {}
	CRectangle(float left, float top, float right, float bottom) : rect(SRectGet(left,top,right,bottom)) {}
	CRectangle(Vector2<float> start, Vector2<float> end) : rect(SRectGet(start.x, start.y, end.x, end.y)) {}

	bool			CollisionCircle(SCircle cir);									//�~�Ƃ̏Փ˔���
	bool			CollisionRect(CRectangle rect);									//�l�p�Ƃ̏Փ˔���
	bool			CollisionPoint(Vector2<int> pos);								//�_�Ƃ̏Փ˔���
	void			Draw(unsigned int Color, bool Fill);							//�`��
	void			SetRect(SRectangle rect);										//�l�p���Z�b�g
	void			SetRect(float left, float top, float right, float bottom);		//�l�p���Z�b�g
	void			SetRect(Vector2<float> start, Vector2<float> end);				//�l�p���Z�b�g
	void			AddRect(SRectangle rectA);										//�l�p���ɉ��Z
	void			AddRect(float left, float top, float right, float bottom);		//�l�p���ɉ��Z
	void			AddRect(Vector2<float> start, Vector2<float> end);				//�l�p���ɉ��Z
	SRectangle		GetSRect() { return rect; }										//�l�p���擾
};