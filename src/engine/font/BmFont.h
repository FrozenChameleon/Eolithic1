#pragma once

#include "BmFontDataChar.h"
#include "../render/Texture2D.h"

typedef struct BmFontData BmFontData;

struct BmFont
{
	const char* _mFontName;
	BmFontData* _mFontData;
	Texture2D* _mFontTexture;
	struct { int key; BmFontDataChar value; }  _mFontCharHashMap;
};

