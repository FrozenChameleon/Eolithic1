/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../resources/Resource.h"
#include "../math/Rectangle.h"
#include "../utils/IStringArray.h"

typedef struct Sheet
{
	const char* mSheetName;
	const char* mUnderlyingTextureName;
	Rectangle mRectangle;
	Resource* mTextureResource;
} Sheet;

Sheet* Sheet_GetDefaultSheet();
Sheet* Sheet_GetSheet(const char* name);
void Sheet_BuildSheets();
bool Sheet_HasSheet(const char* name);
IStringArray* Sheet_CreateListOfSheetNames();