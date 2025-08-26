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
#include "../io/BufferReader.h"

typedef struct Prop
{
	bool _mIsSetup;
	Animation _mAnimation;
	Sheet* _mSheet;
	bool mIsAdditive;
	int mScaler;
	int mFlipSpeed;
	bool mIsAnimation;
	FixedChar260 mTextureName;
	FixedChar260 mTilesetFilter;
} Prop;

Prop* Prop_FromStream(BufferReader* br);