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
static struct { char* key; Resource* value; } *sh_resources;
static bool _mHasInit;

static void Init()
{
	if (_mHasInit)
	{
		return;
	}

	sh_new_arena(sh_resources);

	_mHasInit = true;
}

Resource* AnimTileManager_GetResource(const char* filenameWithoutExtension)
{
	//
	Init();
	//
	
	Resource* resource = shget(sh_resources, filenameWithoutExtension);
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
	shput(sh_resources, resource->mFileNameWithoutExtension, resource);
	return resource;
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

	MString* path = File_Combine2("data", AnimTileManager_GetDatFileName());
	if (!File_Exists(path->text))
	{
		Logger_printf("Unable to load from dat: %s\n", path->text);
		return;
	}
	
	DatReader* dr = DatReader_Create(path->text);
	while (DatReader_HasNext(dr))
	{
		MString* nextPath = DatReader_NextFilePath(dr);
		MString* fileName = File_GetFileName(nextPath->text);
		MString* fileNameWithoutExtension = File_GetFileNameWithoutExtension(nextPath->text);
		BufferReader* br = DatReader_NextStream(dr, false);
		AnimTileManager_LoadAssetFromStreamAndCreateResource(br, fileNameWithoutExtension->text, path->text);
		BufferReader_Dispose(br, false);
		MString_Dispose(nextPath);
		MString_Dispose(fileName);
		MString_Dispose(fileNameWithoutExtension);
	}

	DatReader_Dispose(dr);
	MString_Dispose(path);
}
void AnimTileManager_Dispose(const char* filenameWithoutExtension)
{
	//
	Init();
	//
	
	int32_t len = shlen(sh_resources);
	Resource* resource = shget(sh_resources, filenameWithoutExtension);
	if (resource->mData != NULL)
	{
		AnimTile_Dispose(resource->mData);
	}
	Utils_free(resource);
	shdel(sh_resources, filenameWithoutExtension);
}
void AnimTileManager_DisposeAll()
{
	//
	Init();
	//
	
	int32_t len = shlen(sh_resources);
	for (int i = 0; i < len; i += 1)
	{
		AnimTileManager_Dispose(sh_resources[i].key);
	}

	shfree(sh_resources);
	sh_resources = NULL;
	_mResourceCounter = 0;
	_mHasInit = false;
}
int64_t AnimTileManager_Length()
{
	return shlen(sh_resources);
}
Resource* AnimTileManager_GetResourceByIndex(int index)
{
	return sh_resources[index].value;
}
AnimTile* AnimTileManager_GetResourceDataByIndex(int index)
{
	return (AnimTile*)sh_resources[index].value->mData;
}