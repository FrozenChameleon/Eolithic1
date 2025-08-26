/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "Color.h"
#include "../math/Rectangle.h"

typedef struct DrawRectangle
{
	Color mColor;
	Rectangle mRectangle;
} DrawRectangle;

void DrawRectangle_Init(DrawRectangle* drect, Color color, Rectangle rectangle);