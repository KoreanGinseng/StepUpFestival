#pragma once

#include	"DxLibPlus.h"

enum TextureKey {
	TEXKEY_DRAGON_BLUE,
	TEXKEY_DRAGON_RED,
	TEXKEY_DRAGON_GREEN,
	TEXKEY_DRAGON_KOMODO,

	TEXKEY_EFFECT_FIRE,
	TEXKEY_EFFECT_ICE,
	TEXKEY_EFFECT_THUNDER,
	TEXKEY_EFFECT_SLASH,

	TEXKEY_CURSOR,

	TEXKEY_COUNT,
};

enum GameState {
	STATE_GAME			= 0x00000000,
	STATE_GAMEOVER		= 0x00000001,
	STATE_GAMECLEAR		= 0x00000002,

	STATE_CHECK			= 0xFFFFFFFF,
};

extern TexMngInfo TexFile[TEXKEY_COUNT];
extern std::string gMessage;

struct Status {
	int		hp;
	int		attack;
};

struct Skill {
	std::string name;
	float		rate;
	EffectType  effect;
};

constexpr	int		FontMargin = 4;
constexpr	int		FontSize   = 24;

constexpr	int		PlayerRectX = 0;
constexpr	int		PlayerRectY = 0;
constexpr	int		PlayerRectW = 150;
constexpr	int		PlayerRectH = 150;

constexpr	int		CommandRectX = 0;
constexpr	int		CommandRectY = 568;
constexpr	int		CommandRectW = 290;
constexpr	int		CommandRectH = 768 - CommandRectY;

constexpr	int		MessageRectX = CommandRectX + CommandRectW;
constexpr	int		MessageRectY = CommandRectY;
constexpr	int		MessageRectW = 1024 - CommandRectW;
constexpr	int		MessageRectH = CommandRectH;