#pragma once

#include "TextureOffsetInfo.h"

#include "../io/BufferReader.h"

typedef struct TextureOffset
{
	TextureOffsetInfo* _mDynamicOffsets;
} TextureOffset;

TextureOffset* TextureOffset_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br);
void TextureOffset_Dispose(TextureOffset* to);