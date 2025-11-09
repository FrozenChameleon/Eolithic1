/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "AnimTile.h"
#include "../utils/Utils.h"

void AnimTile_Read(AnimTile* atile, BufferReader* br)
{
	atile->mIsAdditive = BufferReader_ReadBoolean(br);
	atile->mScaler = BufferReader_ReadI32(br);
	atile->mIsFlipX = BufferReader_ReadBoolean(br);
	atile->mIsFlipY = BufferReader_ReadBoolean(br);
	atile->mFlipSpeed = BufferReader_ReadI32(br);
	atile->mRotation = BufferReader_ReadFloat(br);
	atile->mTextureName = BufferReader_ReadMString(br);
	atile->mTilesetFilter = BufferReader_ReadMString(br);
	atile->mIsWrap = BufferReader_ReadBoolean(br);
	atile->mWrapTextureName = BufferReader_ReadMString(br);
	atile->mIsWrapX = BufferReader_ReadBoolean(br);
	atile->mWrapSpeedX = BufferReader_ReadI32(br);
	atile->mIsWrapY = BufferReader_ReadBoolean(br);
	atile->mWrapSpeedY = BufferReader_ReadI32(br);
	atile->mWrapSpeedDelay = BufferReader_ReadI32(br);
}

AnimTile* AnimTile_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br)
{
	AnimTile* animTile = Utils_calloc(1, sizeof(AnimTile));
	AnimTile_Read(animTile, br);
	return animTile;
}
void AnimTile_Dispose(AnimTile* atile)
{
	Utils_free(atile);
}
