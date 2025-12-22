#pragma once

#include "FontMapData.h"

void FontMap_Init();
const FontMapData* FontMap_GetReplacement(const char* fontName);
/*#if EDITOR //C99 TODO? PROBABLY NOT.
void FontMap_Update();
#endif*/