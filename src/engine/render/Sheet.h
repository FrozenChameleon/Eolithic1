/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../resources/Resource.h"
#include "../math/Rectangle.h"

typedef struct Sheet
{
	const char* mSheetName;
	const char* mUnderlyingTextureName;
	Rectangle mRectangle;
	Resource* mTextureResource;
} Sheet;

Sheet* Sheet_GetDefaultSheet();
Sheet* Sheet_GetSheet();