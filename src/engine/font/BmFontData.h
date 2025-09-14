#pragma once

#include "BmFontDataInfo.h"
#include "BmFontDataCommon.h"
#include "BmFontDataPage.h"
#include "BmFontDataChar.h"
#include "BmFontDataKerning.h"
#include "../io/File.h"
#include "../utils/Utils.h"

typedef struct BmFontData
{
	BmFontDataInfo mInfo;
	BmFontDataCommon mCommon;
	BmFontDataPage* mDynamicPages;
	BmFontDataChar* mDynamicChars;
	BmFontDataKerning* mDynamicKernings;
} BmFontData;

