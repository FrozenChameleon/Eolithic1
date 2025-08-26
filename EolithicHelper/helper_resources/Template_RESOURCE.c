/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */
 
//THIS CODE IS AUTOMATICALLY GENERATED, DO NOT EDIT!

#include "%strResourceManager%.h"

#include "../../third_party/stb_ds.h"
#include "../utils/Utils.h"

static int32_t _mResourceCounter;
static struct { char* key; Resource* value; } *_mHashMap;

Resource* %strResourceManager%_GetResource(const char* filenameWithoutExtension)
{
	return hmget(_mHashMap, filenameWithoutExtension);
}
%strResource%* %strResourceManager%_GetResourceData(const char* filenameWithoutExtension)
{
	Resource* resource = AnimTileManager_GetResource(filenameWithoutExtension);
	if (resource == NULL)
	{
		return NULL;
	}

	return (%strResource%*)resource->mData;
}
Resource* %strResourceManager%_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path)
{
	Resource* resource = Utils_malloc(sizeof(Resource));
	Utils_strlcpy(&resource->mPath, path, FIXED_CHAR_260_LENGTH);
	Utils_strlcpy(&resource->mFileNameWithoutExtension, filenameWithoutExtension, FIXED_CHAR_260_LENGTH);
	resource->mID = _mResourceCounter;
	_mResourceCounter += 1;
	resource->mData = %strResource%_FromStream(br);
	hmput(_mHashMap, filenameWithoutExtension, resource);
}
