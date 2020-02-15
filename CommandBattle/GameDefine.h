#pragma once

#include	"DxLibPlus.h"

enum TextureKey {
	TEXKEY_DRAGON_BLUE,
	TEXKEY_DRAGON_RED,
	TEXKEY_DRAGON_GREEN,
	TEXKEY_DRAGON_KOMODO,

	TEXKEY_COUNT,
};

constexpr	int		PlayerRectX = 0;
constexpr	int		PlayerRectY = 0;
constexpr	int		PlayerRectW = 150;
constexpr	int		PlayerRectH = 150;

constexpr	int		CommandRectX = 0;
constexpr	int		CommandRectY = 568;
constexpr	int		CommandRectW = 150;
constexpr	int		CommandRectH = 768 - CommandRectY;

constexpr	int		MessageRectX = CommandRectX + CommandRectW;
constexpr	int		MessageRectY = CommandRectY;
constexpr	int		MessageRectW = 1024 - CommandRectW;
constexpr	int		MessageRectH = CommandRectH;