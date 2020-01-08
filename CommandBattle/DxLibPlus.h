#pragma once
#include	"Fps.h"
#include	"Circle.h"
#include	"Texture.h"
#include	"Rectangle.h"
#include	"Animation.h"
#include	"Input.h"

#include	<crtdbg.h>
#ifdef _DEBUG
#define		NEW		new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define		NEW		new
#endif