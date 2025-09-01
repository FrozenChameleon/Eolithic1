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
#include "../leveldata/AnimTile.h"

Resource* AnimTileManager_GetResource(const char* filenameWithoutExtension);
AnimTile* AnimTileManager_GetResourceData(const char* filenameWithoutExtension);
Resource* AnimTileManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path);
const char* AnimTileManager_GetDatFileName();
void AnimTileManager_LoadAllFromDat();
void AnimTileManager_Dispose(const char* filenameWithoutExtension);
void AnimTileManager_DisposeAll();