#pragma once

#include "../utils/MString.h"

typedef struct BmFontDataInfo
{
	MString* Face;
	int Size;
	int Bold;
	int Italic;
	MString* Charset;
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