/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */
 
//THIS CODE IS AUTOMATICALLY GENERATED, DO NOT EDIT!

#include "AnimTileManager.h"

#include "../../third_party/stb_ds.h"
#include "../utils/Utils.h"
#include "../utils/Logger.h"
#include "../io/File.h"
#include "../io/DatReader.h"
#include "../utils/IStrings.h"

static int32_t _mResourceCounter;
static struct { char* key; Resource* value; } *_mStringHashMap;
static bool _mHasInit;

static void Init()
{
	if (_mHasInit)
	{
		return;
	}

	sh_new_arena(_mStringHashMap);

	_mHasInit = true;
}

Resource* AnimTileManager_GetResource(const char* filenameWithoutExtension)
{
	//
	Init();
	//
	
	Resource* resource = shget(_mStringHashMap, filenameWithoutExtension);
	if (resource == NULL)
	{
		Logger_printf("Unable to get resource: %s", filenameWithoutExtension);
		return NULL;
	}
	
	return resource;
}
AnimTile* AnimTileManager_GetResourceData(const char* filenameWithoutExtension)
{
	//
	Init();
	//
	
	Resource* resource = AnimTileManager_GetResource(filenameWithoutExtension);
	if (resource == NULL)
	{
		Logger_printf("Unable to get resource data: %s", filenameWithoutExtension);
		return NULL;
	}

	return (AnimTile*)resource->mData;
}
Resource* AnimTileManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path)
{
	//
	Init();
	//

	Resource* resource = Utils_malloc(sizeof(Resource));
	Utils_memset(resource, 0, sizeof(Resource));
	resource->mPath = IStrings_GlobalGet(path);
	resource->mFileNameWithoutExtension = IStrings_GlobalGet(filenameWithoutExtension);
	resource->mID = _mResourceCounter;
	_mResourceCounter += 1;
	resource->mData = AnimTile_FromStream(resource->mPath, resource->mFileNameWithoutExtension, br);
	shput(_mStringHashMap, resource->mFileNameWithoutExtension, resource);
}
const char* AnimTileManager_GetDatFileName()
{
	return "animtile.dat";
}
void AnimTileManager_LoadAllFromDat()
{
	//
	Init();
	//

	SharedFixedChar260* sharedStringBufferForPath = Utils_CreateSharedFixedChar260();
	SharedFixedChar260* sharedStringBufferForFileName = Utils_CreateSharedFixedChar260();
	SharedFixedChar260* sharedStringBufferForFileNameWithoutExtension = Utils_CreateSharedFixedChar260();
	File_Combine2(sharedStringBufferForPath, "data", AnimTileManager_GetDatFileName());
	if (!File_Exists(sharedStringBufferForPath))
	{
		Logger_printf("Unable to load from dat: %s", sharedStringBufferForPath);
		return;
	}
	
	DatReader* dr = DatReader_Create(sharedStringBufferForPath);
	while (DatReader_HasNext(dr))
	{
		DatReader_NextFilePath(dr, sharedStringBufferForPath);
		File_GetFileName(sharedStringBufferForFileName, sharedStringBufferForPath);
		File_GetFileNameWithoutExtension(sharedStringBufferForFileNameWithoutExtension, sharedStringBufferForPath);
		BufferReader* br = DatReader_NextStream(dr, false);
		AnimTileManager_LoadAssetFromStreamAndCreateResource(br, sharedStringBufferForFileNameWithoutExtension, sharedStringBufferForPath);
		BufferReader_Dispose(br, false);
	}
	DatReader_Dispose(dr);
	Utils_DisposeSharedFixedChar260(sharedStringBufferForPath);
	Utils_DisposeSharedFixedChar260(sharedStringBufferForFileName);
	Utils_DisposeSharedFixedChar260(sharedStringBufferForFileNameWithoutExtension);
}
void AnimTileManager_Dispose(const char* filenameWithoutExtension)
{
	//
	Init();
	//
	
	int32_t len = shlen(_mStringHashMap);
	Resource* resource = shget(_mStringHashMap, filenameWithoutExtension);
	if (resource->mData != NULL)
	{
		AnimTile_Dispose(resource->mData);
	}
	Utils_free(resource);
	shdel(_mStringHashMap, filenameWithoutExtension);
}
void AnimTileManager_DisposeAll()
{
	//
	Init();
	//
	
	int32_t len = shlen(_mStringHashMap);
	for (int i = 0; i < len; i += 1)
	{
		AnimTileManager_Dispose(_mStringHashMap[i].key);
	}

	shfree(_mStringHashMap);
	_mStringHashMap = NULL;
	_mResourceCounter = 0;
	_mHasInit = false;
}
int AnimTileManager_Length()
{
	return shlen(_mStringHashMap);
}
Resource* AnimTileManager_GetResourceByIndex(int index)
{
	return _mStringHashMap[index].value;
}
AnimTile* AnimTileManager_GetResourceDataByIndex(int index)
{
	return (AnimTile*)_mStringHashMap[index].value->mData;
}