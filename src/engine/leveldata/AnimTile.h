/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../utils/Macros.h"
#include "../render/Animation.h"
#include "../render/Sheet.h"
#include "../io/BufferReader.h"
#include "../utils/FixedChar260.h"

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
	FixedChar260 mTextureName;
	FixedChar260 mTilesetFilter;
	bool mIsWrap;
	FixedChar260 mWrapTextureName;
	bool mIsWrapX;
	int mWrapSpeedX;
	bool mIsWrapY;
	int mWrapSpeedY;
	int mWrapSpeedDelay;
} AnimTile;

void AnimTile_Read(AnimTile* atile, BufferReader* br);
AnimTile* AnimTile_FromStream(BufferReader* br);