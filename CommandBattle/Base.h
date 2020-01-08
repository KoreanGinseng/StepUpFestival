/*****************************************************************************************************************************
 *
 *													ベースヘッダー
 *
 ****************************************************************************************************************************/
#pragma once
#pragma comment(lib,"winmm.lib")
#include "DxLib.h"

//! 追加インクルードファイル
#include <math.h>



//! マクロ定義
#define		PI					3.14159
#define		ToRadian(DEG)		(DEG > 180 ? PI/180*(DEG-360*(int)(DEG/360)) : PI/180*DEG)
#define		ToDegree(RAD)		(RAD/PI*180)

#define		COLOR_RED			GetColor(255,0,0)
#define		COLOR_GREEN			GetColor(0,255,0)
#define		COLOR_BLUE			GetColor(0,0,255)
#define		COLOR_WHITE			GetColor(255,255,255)
#define		COLOR_BLACK			GetColor(0,0,0)

#define		ENDFRAME			{999,999,999}


// グローバル変数


/*****************************************************************************************************************************
 *
 *													二次元情報
 *
 *	x		: x座標
 *	y		: y座標
 *
 ****************************************************************************************************************************/
template<typename T> struct Vector2 {
	T x, y;
};

/*****************************************************************************************************************************
 *
 *													二次元情報取得
 *
 *	x		: x座標
 *	y		: y座標
 *
 ****************************************************************************************************************************/
template<typename T>  __inline Vector2<T> Vector2Get(T x, T y) {
	Vector2<T> result;
	result.x = x;
	result.y = y;
	return result;
}

/*****************************************************************************************************************************
 *
 *												四角の構造体情報
 *
 *	Top		: 上座標
 *	Left	: 左座標
 *	Bottom  : 下座標
 *	Right	: 右座標
 *
 ****************************************************************************************************************************/
typedef struct tag_Rectangle {
	float		Top;
	float		Left;
	float		Bottom;
	float		Right;
} SRectangle;

__inline SRectangle SRectGet(float left, float top, float right, float bottom) {
	SRectangle result;
	result.Left = left;
	result.Top = top;
	result.Right = right;
	result.Bottom = bottom;
	return result;
}

/*****************************************************************************************************************************
 *
 *												円の構造体情報
 *
 *	r		: 半径
 *	x		: 円のx座標
 *	y		: 円のy座標
 *
 ****************************************************************************************************************************/
typedef struct tag_Circle {
	float	r;
	float	x;
	float	y;
} SCircle;

__inline SCircle SCircleSet(float r, float x, float y) {
	SCircle result;
	result.r = r;
	result.x = x;
	result.y = y;
}