#pragma once

#include "../utils/Macros.h"

typedef struct BmFontDataInfo
{
	char Face[EE_FILENAME_MAX];
	int Size;
	int Bold;
	int Italic;
	char Charset[EE_FILENAME_MAX];
	int Unicode;
	int StretchH;
	int Smooth;
	int AA;
	int PaddingUp;
	int PaddingRight;
	int PaddingDown;
	int PaddingLeft;
	int SpacingHoriz;
	int SpacingVert;
	int Outline;
} BmFontDataInfo;