/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */
 
//THIS CODE IS AUTOMATICALLY GENERATED, DO NOT EDIT!

#include "BmFontManager.h"

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

Resource* BmFontManager_GetResource(const char* filenameWithoutExtension)
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
BmFont* BmFontManager_GetResourceData(const char* filenameWithoutExtension)
{
	//
	Init();
	//
	
	Resource* resource = BmFontManager_GetResource(filenameWithoutExtension);
	if (resource == NULL)
	{
		Logger_printf("Unable to get resource data: %s", filenameWithoutExtension);
		return NULL;
	}

	return (BmFont*)resource->mData;
}
Resource* BmFontManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path)
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
	resource->mData = BmFont_FromStream(resource->mPath, resource->mFileNameWithoutExtension, br);
	shput(_mStringHashMap, resource->mFileNameWithoutExtension, resource);
	return resource;
}
const char* BmFontManager_GetDatFileName()
{
	return "bmfont.dat";
}
void BmFontManager_LoadAllFromDat()
{
	//
	Init();
	//

	SharedFixedChar260* sharedStringBufferForPath = Utils_CreateSharedFixedChar260();
	SharedFixedChar260* sharedStringBufferForFileName = Utils_CreateSharedFixedChar260();
	SharedFixedChar260* sharedStringBufferForFileNameWithoutExtension = Utils_CreateSharedFixedChar260();
	File_Combine2(sharedStringBufferForPath, "data", BmFontManager_GetDatFileName());
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
		BmFontManager_LoadAssetFromStreamAndCreateResource(br, sharedStringBufferForFileNameWithoutExtension, sharedStringBufferForPath);
		BufferReader_Dispose(br, false);
	}
	DatReader_Dispose(dr);
	Utils_DisposeSharedFixedChar260(sharedStringBufferForPath);
	Utils_DisposeSharedFixedChar260(sharedStringBufferForFileName);
	Utils_DisposeSharedFixedChar260(sharedStringBufferForFileNameWithoutExtension);
}
void BmFontManager_Dispose(const char* filenameWithoutExtension)
{
	//
	Init();
	//
	
	int32_t len = shlen(_mStringHashMap);
	Resource* resource = shget(_mStringHashMap, filenameWithoutExtension);
	if (resource->mData != NULL)
	{
		BmFont_Dispose(resource->mData);
	}
	Utils_free(resource);
	shdel(_mStringHashMap, filenameWithoutExtension);
}
void BmFontManager_DisposeAll()
{
	//
	Init();
	//
	
	int32_t len = shlen(_mStringHashMap);
	for (int i = 0; i < len; i += 1)
	{
		BmFontManager_Dispose(_mStringHashMap[i].key);
	}

	shfree(_mStringHashMap);
	_mStringHashMap = NULL;
	_mResourceCounter = 0;
	_mHasInit = false;
}
int BmFontManager_Length()
{
	return shlen(_mStringHashMap);
}
Resource* BmFontManager_GetResourceByIndex(int index)
{
	return _mStringHashMap[index].value;
}
BmFont* BmFontManager_GetResourceDataByIndex(int index)
{
	return (BmFont*)_mStringHashMap[index].value->mData;
}