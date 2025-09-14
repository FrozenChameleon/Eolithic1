#pragma once

typedef struct BmFontDataInfo
{
	const char* Face;
	int Size;
	int Bold;
	int Italic;
	const char* Charset;
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