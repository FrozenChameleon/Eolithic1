#pragma once

#include "../io/FixedByteBuffer.h"
#include "../font/FontMapData.h"
#include "../render/Color.h"
#include "../math/Rectangle.h"

void RenderTtFont_Create(const char* name, FixedByteBuffer* data);
void RenderTtFont_Draw(const FontMapData* replacement, const char* text, Color color, Vector2 position);
Rectangle RenderTtFont_GetBounds(const FontMapData* replacement, const char* text);
