/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "ImageData.h"
#include "../render/Sheet.h"
#include "../render/Animation.h"

typedef struct ImageDataInstance
{
	ImageData* mData;
	Sheet* mSheet;
	Animation mAnimation;
	bool mIsOriginSet;
} ImageDataInstance;

void ImageDataInstance_Init(ImageDataInstance* idi, ImageData* data);