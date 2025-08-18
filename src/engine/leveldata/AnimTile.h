/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdbool.h"
#include "../render/Animation.h"
#include "../render/Sheet.h"
#include "../utils/Macros.h"

typedef struct AnimTile
{
	bool _mIsSetup;
	int _mWrapSpeedCounter;
	Point _mWrapOffset;
	Animation _mAnimation;
	Sheet* _mWrapSheet;

	bool mIsAdditive;
	int mScaler;
	bool mIsFlipX;
	bool mIsFlipY;
	int mFlipSpeed;
	float mRotation;
	char mTextureName[EE_FILENAME_MAX];
	char mTilesetFilter[EE_FILENAME_MAX];
	bool mIsWrap;
	char mWrapTextureName[EE_FILENAME_MAX];
	bool mIsWrapX;
	int mWrapSpeedX;
	bool mIsWrapY;
	int mWrapSpeedY;
	int mWrapSpeedDelay;
} AnimTile;

