/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */
 
//THIS CODE IS AUTOMATICALLY GENERATED, DO NOT EDIT!

#include "TextureManager.h"

#include "../../third_party/stb_ds.h"
#include "../utils/Utils.h"
#include "../utils/Logger.h"
#include "../io/File.h"
#include "../io/DatReader.h"

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

Resource* TextureManager_GetResource(const char* filenameWithoutExtension)
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
Texture* TextureManager_GetResourceData(const char* filenameWithoutExtension)
{
	//
	Init();
	//
	
	Resource* resource = TextureManager_GetResource(filenameWithoutExtension);
	if (resource == NULL)
	{
		Logger_printf("Unable to get resource data: %s", filenameWithoutExtension);
		return NULL;
	}

	return (Texture*)resource->mData;
}
Resource* TextureManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path)
{
	//
	Init();
	//

	Resource* resource = Utils_malloc(sizeof(Resource));
	Utils_strlcpy(&resource->mPath, path, FIXED_CHAR_260_LENGTH);
	Utils_strlcpy(&resource->mFileNameWithoutExtension, filenameWithoutExtension, FIXED_CHAR_260_LENGTH);
	resource->mID = _mResourceCounter;
	_mResourceCounter += 1;
	resource->mData = Texture_FromStream(path, filenameWithoutExtension, br);
	shput(_mStringHashMap, filenameWithoutExtension, resource);
}
const char* TextureManager_GetDatFileName()
{
	return "texture.dat";
}
void TextureManager_LoadAllFromDat()
{
	//
	Init();
	//

	SharedFixedChar260* sharedStringBufferForPath = Utils_CreateSharedFixedChar260();
	SharedFixedChar260* sharedStringBufferForFileName = Utils_CreateSharedFixedChar260();
	SharedFixedChar260* sharedStringBufferForFileNameWithoutExtension = Utils_CreateSharedFixedChar260();
	File_Combine2(sharedStringBufferForPath, "data", TextureManager_GetDatFileName());
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
		TextureManager_LoadAssetFromStreamAndCreateResource(br, sharedStringBufferForFileNameWithoutExtension, sharedStringBufferForPath);
		BufferReader_Dispose(br, false);
	}
	DatReader_Dispose(dr);
	Utils_DisposeSharedFixedChar260(sharedStringBufferForPath);
	Utils_DisposeSharedFixedChar260(sharedStringBufferForFileName);
	Utils_DisposeSharedFixedChar260(sharedStringBufferForFileNameWithoutExtension);
}
void TextureManager_Dispose(const char* filenameWithoutExtension)
{
	//
	Init();
	//
	
	int32_t len = shlen(_mStringHashMap);
	Resource* resource = shget(_mStringHashMap, filenameWithoutExtension);
	if (resource->mData != NULL)
	{
		Texture_Dispose(resource->mData);
	}
	Utils_free(resource);
	shdel(_mStringHashMap, filenameWithoutExtension);
}
void TextureManager_DisposeAll()
{
	//
	Init();
	//
	
	int32_t len = shlen(_mStringHashMap);
	for (int i = 0; i < len; i += 1)
	{
		TextureManager_Dispose(_mStringHashMap[i].key);
	}

	shfree(_mStringHashMap);
	_mStringHashMap = NULL;
	_mResourceCounter = 0;
	_mHasInit = false;
}
int TextureManager_Length()
{
	return shlen(_mStringHashMap);
}
Resource* TextureManager_GetResourceByIndex(int index)
{
	return _mStringHashMap[index].value;
}
Texture* TextureManager_GetResourceDataByIndex(int index)
{
	return (Texture*)_mStringHashMap[index].value->mData;
}