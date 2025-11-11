/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "DrawRectangle.h"

#include "../utils/Utils.h"

void DrawRectangle_Init(DrawRectangle* drect, Color color, Rectangle rectangle)
{
	Utils_memset(drect, 0, sizeof(DrawRectangle));

	drect->mColor = color;
	drect->mRectangle = rectangle;
}
