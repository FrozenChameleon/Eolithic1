#pragma once

#include "Resource.h"
#include "../utils/Macros.h"
#include "../io/BufferReader.h"
#include "../leveldata/AnimTile.h"

Resource* AnimTileManager_GetResource(const char* filenameWithoutExtension);
AnimTile* AnimTileManager_GetResourceData(const char* filenameWithoutExtension);
Resource* AnimTileManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path);