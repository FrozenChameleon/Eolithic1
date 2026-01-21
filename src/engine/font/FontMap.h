#pragma once

#include "FontMapData.h"

void FontMap_Init(void);
const FontMapData* FontMap_GetReplacement(const char* fontName);