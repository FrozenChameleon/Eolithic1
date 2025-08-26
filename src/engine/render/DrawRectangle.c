/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "DrawRectangle.h"

void DrawRectangle_Init(DrawRectangle* drect, Color color, Rectangle rectangle)
{
	drect->mColor = color;
	drect->mRectangle = rectangle;
}
