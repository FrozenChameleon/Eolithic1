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
#include "../audio/Music.h"

Resource* MusicManager_GetResource(const char* filenameWithoutExtension);
Music* MusicManager_GetResourceData(const char* filenameWithoutExtension);
Resource* MusicManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path);
const char* MusicManager_GetDatFileName();
void MusicManager_LoadAllFromDat();
void MusicManager_Dispose(const char* filenameWithoutExtension);
void MusicManager_DisposeAll();
int64_t MusicManager_Length();
Resource* MusicManager_GetResourceByIndex(int index);
Music* MusicManager_GetResourceDataByIndex(int index);