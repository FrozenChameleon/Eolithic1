/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "AnimTile.h"
#include "../utils/Utils.h"

void AnimTile_Read(AnimTile* at, BufferReader* br)
{
	at->mIsAdditive = BufferReader_ReadBoolean(br);
	at->mScaler = BufferReader_ReadI32(br);
	at->mIsFlipX = BufferReader_ReadBoolean(br);
	at->mIsFlipY = BufferReader_ReadBoolean(br);
	at->mFlipSpeed = BufferReader_ReadI32(br);
	at->mRotation = BufferReader_ReadFloat(br);
	at->mTextureName = BufferReader_ReadMString(br);
	at->mTilesetFilter = BufferReader_ReadMString(br);
	at->mIsWrap = BufferReader_ReadBoolean(br);
	at->mWrapTextureName = BufferReader_ReadMString(br);
	at->mIsWrapX = BufferReader_ReadBoolean(br);
	at->mWrapSpeedX = BufferReader_ReadI32(br);
	at->mIsWrapY = BufferReader_ReadBoolean(br);
	at->mWrapSpeedY = BufferReader_ReadI32(br);
	at->mWrapSpeedDelay = BufferReader_ReadI32(br);
}

AnimTile* AnimTile_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br)
{
	AnimTile* at = Utils_calloc(1, sizeof(AnimTile));
	AnimTile_Read(at, br);
	return at;
}
void AnimTile_Dispose(AnimTile* at)
{
	Utils_free(at);
}
Animation* AnimTile_GetAnimation(AnimTile* at)
{
	return &at->_mAnimation;
}
