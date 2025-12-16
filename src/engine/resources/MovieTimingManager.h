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
#include "../movie/MovieTiming.h"

Resource* MovieTimingManager_GetResource(const char* filenameWithoutExtension);
MovieTiming* MovieTimingManager_GetResourceData(const char* filenameWithoutExtension);
Resource* MovieTimingManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path);
const char* MovieTimingManager_GetDatFileName();
void MovieTimingManager_LoadAllFromDat();
void MovieTimingManager_Dispose(const char* filenameWithoutExtension);
void MovieTimingManager_DisposeAll();
int64_t MovieTimingManager_Length();
Resource* MovieTimingManager_GetResourceByIndex(int index);
MovieTiming* MovieTimingManager_GetResourceDataByIndex(int index);