#pragma once
#include	"Base.h"


/*****************************************************************************************************************************
 *
 *												�~�N���X
 *
 ****************************************************************************************************************************/
class CCircle {
private:
	SCircle			circle;		//�~�̍\���̏��
public:
	CCircle() : circle(SCircleSet(0,0,0)){}
	CCircle(float r, Vector2<float> pos) : circle(SCircleSet(r,pos.x,pos.y)) {}
	CCircle(float r, float x, float y) : circle(SCircleSet(r,x,y)) {}

	bool			CollisionCircle(CCircle cir);			//�~�Ƃ̏Փ˔���
	bool			CollisionRect(SRectangle rect);			//�l�p�Ƃ̏Փ˔���
	bool			CollisionPoint(Vector2<int> pos);		//�_�Ƃ̏Փ˔���
	void			Draw(unsigned int Color, bool Fill);	//�`��
	void			Draw(Vector2<float> pos, unsigned int Color, bool Fill);		//�`��
	void			Draw(float posX, float posY, unsigned int Color, bool Fill);	//�`��
	void			SetCircle(SCircle cir);					//�~���Z�b�g
	void			SetCircle(float r, Vector2<float> pos);	//�~���Z�b�g
	void			SetCircle(float r, float x, float y);	//�~���Z�b�g
	SCircle			GetSCircle() { return circle; }			//�~���擾
};
