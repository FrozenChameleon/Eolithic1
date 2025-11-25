#pragma once

#include "BmFontData.h"
#include "../utils/MString.h"
/*#include "../resources/ResourceData.h"
#include "../io/OeStream.h"
#include "../font/OeFontMapData.h"*/

typedef struct SpriteBatch SpriteBatch;
typedef struct Texture Texture;
typedef struct TTFont TTFont;
typedef struct BufferReader BufferReader;

typedef struct BmFont
{
//#if !DISABLE_TT_FONT
	//TODO C99 OeTTFont* GetTTFont(const std::string& font);
//#endif
	MString* _mFontName;
	BmFontData _mFontData;
	Texture* _mFontTexture;
	struct { int key; BmFontDataChar value; }*hm_font_char_map;
} BmFont;

void BmFont_Init(BmFont* bmf, BufferReader* br, const char* fontName);
BmFont* BmFont_GetBmFont(BmFont* bmf, const char* font);
//TODO C99 const OeFontMapData* BmFont_GetReplacement(BmFont* bmf);
const char* BmFont_GetFontName(BmFont* bmf);
Texture* BmFont_GetFontTexture(BmFont* bmf);
bool BmFont_UpdateFontTexture(BmFont* bmf);
int BmFont_GetBaseHeight(BmFont* bmf);
int BmFont_GetLineHeight(BmFont* bmf);
Rectangle BmFont_GetBounds(BmFont* bmf, const char* text, bool doNotReplaceFont);
// const std::string& GetFontExtension();
// const std::vector<std::string>& GetFontDirectories();
BmFont* BmFont_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br);
void BmFont_Dispose(BmFont* bmf);