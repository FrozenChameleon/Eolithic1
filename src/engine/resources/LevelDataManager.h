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
#include "../leveldata/LevelData.h"

Resource* LevelDataManager_GetResource(const char* filenameWithoutExtension);
LevelData* LevelDataManager_GetResourceData(const char* filenameWithoutExtension);
Resource* LevelDataManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path);
const char* LevelDataManager_GetDatFileName();
void LevelDataManager_LoadAllFromDat();
void LevelDataManager_Dispose(const char* filenameWithoutExtension);
void LevelDataManager_DisposeAll();
int LevelDataManager_Length();
Resource* LevelDataManager_GetResourceByIndex(int index);
LevelData* LevelDataManager_GetResourceDataByIndex(int index);