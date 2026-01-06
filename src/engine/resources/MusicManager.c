/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */
 
//THIS CODE IS AUTOMATICALLY GENERATED, DO NOT EDIT!

#include "MusicManager.h"

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

bool MusicManager_HasResource(const char* filenameWithoutExtension)
{
	int64_t index = shgeti(sh_resources, filenameWithoutExtension);
	if (index < 0)
	{
		return false;
	}
	return true;
}
Resource* MusicManager_GetResource(const char* filenameWithoutExtension)
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
Music* MusicManager_GetResourceData(const char* filenameWithoutExtension)
{
	//
	Init();
	//
	
	Resource* resource = MusicManager_GetResource(filenameWithoutExtension);
	if (resource == NULL)
	{
		Logger_printf("Unable to get resource data: %s", filenameWithoutExtension);
		return NULL;
	}

	return (Music*)resource->mData;
}
Resource* MusicManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path)
{
	//
	Init();
	//

	Resource* resource = Utils_malloc(sizeof(Resource));
	Utils_memset(resource, 0, sizeof(Resource));
	MString_Assign(&resource->mPath, path);
	MString_Assign(&resource->mFileNameWithoutExtension, filenameWithoutExtension);
	resource->mID = _mResourceCounter;
	_mResourceCounter += 1;
	resource->mData = Music_FromStream(MString_GetText(resource->mPath), MString_GetText(resource->mFileNameWithoutExtension), br);
	shput(sh_resources, MString_GetText(resource->mFileNameWithoutExtension), resource);
	return resource;
}
const char* MusicManager_GetDatFileName()
{
	return "music.dat";
}
void MusicManager_LoadAllFromDat()
{
	//
	Init();
	//

	MString* path = File_Combine2("data", MusicManager_GetDatFileName());
	if (!File_Exists(MString_GetText(path)))
	{
		Logger_printf("Unable to load from dat: %s\n", MString_GetText(path));
		return;
	}
	
	DatReader* dr = DatReader_Create(MString_GetText(path));
	while (DatReader_HasNext(dr))
	{
		MString* nextPath = DatReader_NextFilePath(dr);
		MString* fileName = File_GetFileName(MString_GetText(nextPath));
		MString* fileNameWithoutExtension = File_GetFileNameWithoutExtension(MString_GetText(nextPath));
		BufferReader* br = DatReader_NextStream(dr, false);
		MusicManager_LoadAssetFromStreamAndCreateResource(br, MString_GetText(fileNameWithoutExtension), MString_GetText(path));
		BufferReader_Dispose(br);
		MString_Dispose(&nextPath);
		MString_Dispose(&fileName);
		MString_Dispose(&fileNameWithoutExtension);
	}

	DatReader_Dispose(dr);
	MString_Dispose(&path);
}
void MusicManager_Dispose(const char* filenameWithoutExtension)
{
	//
	Init();
	//
	
	Resource* resource = shget(sh_resources, filenameWithoutExtension);
	if (resource->mData != NULL)
	{
		Music_Dispose(resource->mData);
	}
	Utils_free(resource);
	shdel(sh_resources, filenameWithoutExtension);
}
void MusicManager_DisposeAll()
{
	//
	Init();
	//
	
	int64_t len = shlen(sh_resources);
	for (int i = 0; i < len; i += 1)
	{
		MusicManager_Dispose(sh_resources[i].key);
	}

	shfree(sh_resources);
	sh_resources = NULL;
	_mResourceCounter = 0;
	_mHasInit = false;
}
int64_t MusicManager_Length()
{
	return shlen(sh_resources);
}
Resource* MusicManager_GetResourceByIndex(int index)
{
	return sh_resources[index].value;
}
Music* MusicManager_GetResourceDataByIndex(int index)
{
	return (Music*)sh_resources[index].value->mData;
}