#pragma once

#include "BmFontDataChar.h"
#include "BmFontData.h"
#include "../render/Texture.h"

typedef struct BmFont
{
	const char* _mFontName;
	BmFontData* _mFontData;
	Texture* _mFontTexture;
	struct { int key; BmFontDataChar value; }  _mFontCharHashMap;
} BmFont;

void BmFont_Dispose(BmFont* bf);
BmFont* BmFont_FromStream();