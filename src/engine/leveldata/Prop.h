/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdbool.h"
#include "stdint.h"
#include "../render/Animation.h"
#include "../render/Sheet.h"

typedef struct Prop
{
	bool _mIsSetup;
	Animation _mAnimation;
	Sheet* _mSheet;
	bool mIsAdditive;
	int mScaler;
	int mFlipSpeed;
	bool mIsAnimation;
	char mTextureName[EE_FILENAME_MAX];
	char mTilesetFilter[EE_FILENAME_MAX];
} Prop;

