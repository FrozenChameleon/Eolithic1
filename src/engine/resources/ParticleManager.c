/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */
 
//THIS CODE IS AUTOMATICALLY GENERATED, DO NOT EDIT!

#include "ParticleManager.h"

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

Resource* ParticleManager_GetResource(const char* filenameWithoutExtension)
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
Particle* ParticleManager_GetResourceData(const char* filenameWithoutExtension)
{
	//
	Init();
	//
	
	Resource* resource = ParticleManager_GetResource(filenameWithoutExtension);
	if (resource == NULL)
	{
		Logger_printf("Unable to get resource data: %s", filenameWithoutExtension);
		return NULL;
	}

	return (Particle*)resource->mData;
}
Resource* ParticleManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path)
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
	resource->mData = Particle_FromStream(resource->mPath, resource->mFileNameWithoutExtension, br);
	shput(sh_resources, resource->mFileNameWithoutExtension, resource);
	return resource;
}
const char* ParticleManager_GetDatFileName()
{
	return "particle.dat";
}
void ParticleManager_LoadAllFromDat()
{
	//
	Init();
	//

	SharedFixedChar260* sharedStringBufferForPath = Utils_CreateSharedFixedChar260();
	SharedFixedChar260* sharedStringBufferForFileName = Utils_CreateSharedFixedChar260();
	SharedFixedChar260* sharedStringBufferForFileNameWithoutExtension = Utils_CreateSharedFixedChar260();
	File_Combine2(sharedStringBufferForPath, "data", ParticleManager_GetDatFileName());
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
		ParticleManager_LoadAssetFromStreamAndCreateResource(br, sharedStringBufferForFileNameWithoutExtension, sharedStringBufferForPath);
		BufferReader_Dispose(br, false);
	}
	DatReader_Dispose(dr);
	Utils_DisposeSharedFixedChar260(sharedStringBufferForPath);
	Utils_DisposeSharedFixedChar260(sharedStringBufferForFileName);
	Utils_DisposeSharedFixedChar260(sharedStringBufferForFileNameWithoutExtension);
}
void ParticleManager_Dispose(const char* filenameWithoutExtension)
{
	//
	Init();
	//
	
	int32_t len = shlen(sh_resources);
	Resource* resource = shget(sh_resources, filenameWithoutExtension);
	if (resource->mData != NULL)
	{
		Particle_Dispose(resource->mData);
	}
	Utils_free(resource);
	shdel(sh_resources, filenameWithoutExtension);
}
void ParticleManager_DisposeAll()
{
	//
	Init();
	//
	
	int32_t len = shlen(sh_resources);
	for (int i = 0; i < len; i += 1)
	{
		ParticleManager_Dispose(sh_resources[i].key);
	}

	shfree(sh_resources);
	sh_resources = NULL;
	_mResourceCounter = 0;
	_mHasInit = false;
}
int ParticleManager_Length()
{
	return shlen(sh_resources);
}
Resource* ParticleManager_GetResourceByIndex(int index)
{
	return sh_resources[index].value;
}
Particle* ParticleManager_GetResourceDataByIndex(int index)
{
	return (Particle*)sh_resources[index].value->mData;
}