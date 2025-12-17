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
#include "../render/TilesetOffset.h"

bool TilesetOffsetManager_HasResource(const char* filenameWithoutExtension);
Resource* TilesetOffsetManager_GetResource(const char* filenameWithoutExtension);
TilesetOffset* TilesetOffsetManager_GetResourceData(const char* filenameWithoutExtension);
Resource* TilesetOffsetManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path);
const char* TilesetOffsetManager_GetDatFileName();
void TilesetOffsetManager_LoadAllFromDat();
void TilesetOffsetManager_Dispose(const char* filenameWithoutExtension);
void TilesetOffsetManager_DisposeAll();
int64_t TilesetOffsetManager_Length();
Resource* TilesetOffsetManager_GetResourceByIndex(int index);
TilesetOffset* TilesetOffsetManager_GetResourceDataByIndex(int index);