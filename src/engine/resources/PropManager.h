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
#include "../leveldata/Prop.h"

Resource* PropManager_GetResource(const char* filenameWithoutExtension);
Prop* PropManager_GetResourceData(const char* filenameWithoutExtension);
Resource* PropManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path);
const char* PropManager_GetDatFileName();
void PropManager_LoadAllFromDat();
void PropManager_Dispose(const char* filenameWithoutExtension);
void PropManager_DisposeAll();
int PropManager_Length();
Resource* PropManager_GetResourceByIndex(int index);
Prop* PropManager_GetResourceDataByIndex(int index);