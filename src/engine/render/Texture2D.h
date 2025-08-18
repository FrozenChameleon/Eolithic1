/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../math/Rectangle.h"

typedef struct Texture2D
{
	const char* mPath;
	void* mTextureData;
	void* mSurfaceData;
	Rectangle mBounds;
} Texture2D;

