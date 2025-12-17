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
#include "../movie/Movie.h"

bool MovieManager_HasResource(const char* filenameWithoutExtension);
Resource* MovieManager_GetResource(const char* filenameWithoutExtension);
Movie* MovieManager_GetResourceData(const char* filenameWithoutExtension);
Resource* MovieManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path);
const char* MovieManager_GetDatFileName();
void MovieManager_LoadAllFromDat();
void MovieManager_Dispose(const char* filenameWithoutExtension);
void MovieManager_DisposeAll();
int64_t MovieManager_Length();
Resource* MovieManager_GetResourceByIndex(int index);
Movie* MovieManager_GetResourceDataByIndex(int index);