/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */
 
//THIS CODE IS AUTOMATICALLY GENERATED, DO NOT EDIT!

#include "ResourceManager.h"

#include "../../third_party/stb_ds.h"
#include "../utils/Utils.h"
#include "../utils/Logger.h"
#include "../io/File.h"
#include "../io/DatReader.h"
#include "../utils/IStrings.h"

static void PrintResourceType(ResourceManager* rm)
{
	Logger_printf("Resource type: %s\n", rm->_mResourceType);
}

void ResourceManager_Init(ResourceManager* rm)
{
	if (rm->_mHasInit)
	{
		return;
	}

	sh_new_arena(rm->sh_resources);

	rm->_mHasInit = true;
}
bool ResourceManager_HasResource(ResourceManager* rm, const char* filenameWithoutExtension)
{
	int64_t index = shgeti(rm->sh_resources, filenameWithoutExtension);
	if (index < 0)
	{
		return false;
	}
	return true;
}
Resource* ResourceManager_GetResource(ResourceManager* rm, const char* filenameWithoutExtension)
{
	Resource* resource = shget(rm->sh_resources, filenameWithoutExtension);
	if (resource == NULL)
	{
		Logger_printf("Unable to get resource: %s", filenameWithoutExtension);
		return NULL;
	}
	
	return resource;
}
void* ResourceManager_GetResourceData(ResourceManager* rm, const char* filenameWithoutExtension)
{
	Resource* resource = ResourceManager_GetResource(rm, filenameWithoutExtension);
	if (resource == NULL)
	{
		Logger_printf("Unable to get resource data: %s", filenameWithoutExtension);
		return NULL;
	}

	return resource->mData;
}
Resource* ResourceManager_LoadAssetFromStreamAndCreateResource(ResourceManager* rm, BufferReader* br, const char* filenameWithoutExtension, const char* path)
{
	Resource* resource = Utils_malloc(sizeof(Resource));
	Utils_memset(resource, 0, sizeof(Resource));
	MString_Assign(&resource->mPath, path);
	MString_Assign(&resource->mFileNameWithoutExtension, filenameWithoutExtension);
	resource->mID = rm->_mResourceCounter;
	rm->_mResourceCounter += 1;
	if (rm->_mFromStream != NULL)
	{
		resource->mData = rm->_mFromStream(MString_GetText(resource->mPath), MString_GetText(resource->mFileNameWithoutExtension), br);
	}
	shput(rm->sh_resources, MString_GetText(resource->mFileNameWithoutExtension), resource);
	return resource;
}
const char* ResourceManager_GetDatFileName(ResourceManager* rm)
{
	return rm->_mDatFileName;
}
void ResourceManager_LoadAllFromDat(ResourceManager* rm)
{
	MString* path = File_Combine2("data", ResourceManager_GetDatFileName(rm));
	if (!File_Exists(MString_GetText(path)))
	{
		Logger_printf("Unable to load from dat: %s\n", MString_GetText(path));
		PrintResourceType(rm);
		return;
	}
	
	DatReader* dr = DatReader_Create(MString_GetText(path));
	while (DatReader_HasNext(dr))
	{
		MString* nextPath = DatReader_NextFilePath(dr);
		MString* fileName = File_GetFileName(MString_GetText(nextPath));
		MString* fileNameWithoutExtension = File_GetFileNameWithoutExtension(MString_GetText(nextPath));
		BufferReader* br = DatReader_NextStream(dr, false);
		ResourceManager_LoadAssetFromStreamAndCreateResource(rm, br, MString_GetText(fileNameWithoutExtension), MString_GetText(path));
		BufferReader_Dispose(br);
		MString_Dispose(&nextPath);
		MString_Dispose(&fileName);
		MString_Dispose(&fileNameWithoutExtension);
	}

	DatReader_Dispose(dr);
	MString_Dispose(&path);
}
void ResourceManager_Dispose(ResourceManager* rm, const char* filenameWithoutExtension)
{
	Resource* resource = shget(rm->sh_resources, filenameWithoutExtension);
	if ((resource->mData != NULL) && (rm->_mDispose != NULL))
	{
		rm->_mDispose(resource->mData);
		resource->mData = NULL;
	}
	Utils_free(resource);
	shdel(rm->sh_resources, filenameWithoutExtension);
}
void ResourceManager_DisposeAll(ResourceManager* rm)
{
	int64_t len = shlen(rm->sh_resources);
	for (int i = 0; i < len; i += 1)
	{
		ResourceManager_Dispose(rm, rm->sh_resources[i].key);
	}

	shfree(rm->sh_resources);
	rm->sh_resources = NULL;
	rm->_mResourceCounter = 0;
	rm->_mHasInit = false;
}
int64_t ResourceManager_Length(ResourceManager* rm)
{
	return shlen(rm->sh_resources);
}
Resource* ResourceManager_GetResourceByIndex(ResourceManager* rm, int index)
{
	return rm->sh_resources[index].value;
}
void* ResourceManager_GetResourceDataByIndex(ResourceManager* rm, int index)
{
	return rm->sh_resources[index].value->mData;
}

const char* ResourceManager_GetKey(ResourceManager* rm, const char* filenameWithoutExtension)
{
	int64_t index = shgeti(rm->sh_resources, filenameWithoutExtension);
	if (index < 0)
	{
		Logger_printf("Unable to get key: %s", filenameWithoutExtension);
		return NULL;
	}

	return rm->sh_resources[index].key;
}
