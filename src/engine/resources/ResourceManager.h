/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */
 
//THIS CODE IS AUTOMATICALLY GENERATED, DO NOT EDIT!

#pragma once

#include "Resource.h"
#include "../utils/Macros.h"
#include "../io/BufferReader.h"

typedef void* (*ResourceManager_FromStreamFunc)(const char* path, const char* filenameWithoutExtension, BufferReader* br);
typedef void (*ResourceManager_DisposeFunc)(void* resourceData);

typedef struct ResourceManager
{
	int32_t _mResourceCounter;
	struct { char* key; Resource* value; } *sh_resources;
	bool _mHasInit;
	ResourceManager_FromStreamFunc _mFromStream;
	ResourceManager_DisposeFunc _mDispose;
	char _mDatFileName[EE_FILENAME_MAX];
	char _mResourceType[EE_FILENAME_MAX];
} ResourceManager;

void ResourceManager_Init(ResourceManager* rm);
bool ResourceManager_HasResource(ResourceManager* rm, const char* filenameWithoutExtension);
Resource* ResourceManager_GetResource(ResourceManager* rm, const char* filenameWithoutExtension);
void* ResourceManager_GetResourceData(ResourceManager* rm, const char* filenameWithoutExtension);
Resource* ResourceManager_LoadAssetFromStreamAndCreateResource(ResourceManager* rm, BufferReader* br, const char* filenameWithoutExtension, const char* path);
const char* ResourceManager_GetDatFileName(ResourceManager* rm);
void ResourceManager_LoadAllFromDat(ResourceManager* rm);
void ResourceManager_Dispose(ResourceManager* rm, const char* filenameWithoutExtension);
void ResourceManager_DisposeAll(ResourceManager* rm);
int64_t ResourceManager_Length(ResourceManager* rm);
Resource* ResourceManager_GetResourceByIndex(ResourceManager* rm, int index);
void* ResourceManager_GetResourceDataByIndex(ResourceManager* rm, int index);
const char* ResourceManager_GetKey(ResourceManager* rm, const char* filenameWithoutExtension);