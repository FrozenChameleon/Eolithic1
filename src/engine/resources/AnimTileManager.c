/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */
 
//THIS CODE IS AUTOMATICALLY GENERATED, DO NOT EDIT!

#include "AnimTileManager.h"

#include "../../third_party/stb_ds.h"
#include "../utils/Utils.h"

static int32_t _mResourceCounter;
static struct { char* key; Resource* value; } *_mHashMap;

Resource* AnimTileManager_GetResource(const char* filenameWithoutExtension)
{
	return hmget(_mHashMap, filenameWithoutExtension);
}
AnimTile* AnimTileManager_GetResourceData(const char* filenameWithoutExtension)
{
	Resource* resource = AnimTileManager_GetResource(filenameWithoutExtension);
	if (resource == NULL)
	{
		return NULL;
	}

	return (AnimTile*)resource->mData;
}
Resource* AnimTileManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path)
{
	Resource* resource = Utils_malloc(sizeof(Resource));
	Utils_strlcpy(&resource->mPath, path, FIXED_CHAR_260_LENGTH);
	Utils_strlcpy(&resource->mFileNameWithoutExtension, filenameWithoutExtension, FIXED_CHAR_260_LENGTH);
	resource->mID = _mResourceCounter;
	_mResourceCounter += 1;
	resource->mData = AnimTile_FromStream(br);
	hmput(_mHashMap, filenameWithoutExtension, resource);
}
