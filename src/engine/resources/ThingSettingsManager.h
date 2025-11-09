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
#include "../leveldata/ThingSettings.h"

Resource* ThingSettingsManager_GetResource(const char* filenameWithoutExtension);
ThingSettings* ThingSettingsManager_GetResourceData(const char* filenameWithoutExtension);
Resource* ThingSettingsManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path);
const char* ThingSettingsManager_GetDatFileName();
void ThingSettingsManager_LoadAllFromDat();
void ThingSettingsManager_Dispose(const char* filenameWithoutExtension);
void ThingSettingsManager_DisposeAll();
int64_t ThingSettingsManager_Length();
Resource* ThingSettingsManager_GetResourceByIndex(int index);
ThingSettings* ThingSettingsManager_GetResourceDataByIndex(int index);