#pragma once

#include "../utils/Macros.h"
#include "../math/Rectangle.h"

typedef struct TextureOffsetInfo
{
	Rectangle mRect;
	IString mPath;
	IString mVirtualName;
	IString mFilenameWithoutExtension;
} TextureOffsetInfo;
