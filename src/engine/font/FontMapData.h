#pragma once

#include "../utils/IStringArray.h"
#include "../utils/Macros.h"
#include "../math/Vector2.h"

typedef struct FontMapData
{
	char mNote[EE_FILENAME_MAX];
	char mFontName[EE_FILENAME_MAX];
	int mFontSize;
	char mReplace[EE_FILENAME_MAX];
	Vector2 mOffset;
	bool mIsBitmap;
	int mLineSpacing;
	int mEffect;
	int mEffectAmount;
	int mCharacterSpacing;
	int mScaleFactor;
	IStringArray* mLanguages;
	int mOverrideBoundsHeight;
} FontMapData;

void FontMapData_Init(FontMapData* fmd);