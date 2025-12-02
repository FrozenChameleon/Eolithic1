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
#include "../utils/MString.h"

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
	MString* mTextureName;
	MString* mTilesetFilter;
	bool mIsWrap;
	MString* mWrapTextureName;
	bool mIsWrapX;
	int mWrapSpeedX;
	bool mIsWrapY;
	int mWrapSpeedY;
	int mWrapSpeedDelay;
} AnimTile;

void AnimTile_Read(AnimTile* at, BufferReader* br);
AnimTile* AnimTile_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br);
void AnimTile_Dispose(AnimTile* at);
Animation* AnimTile_GetAnimation(AnimTile* at);
void AnimTile_UpdateResource(AnimTile* at);
void AnimTile_Draw(AnimTile* at, SpriteBatch* spriteBatch, Color color, int32_t depth, int32_t x, int32_t y, float rotation, bool flipX, bool flipY);
Sheet* AnimTile_GetAnimationSheet(AnimTile* at);
void AnimTile_LoadAnimation(AnimTile* at);