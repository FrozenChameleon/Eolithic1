#pragma once

#include "../math/Rectangle.h"

typedef struct TextureOffsetInfo
{
	Rectangle mRect;
	const char* mPath;
	const char* mVirtualName;
} TextureOffsetInfo;
