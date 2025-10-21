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
#include "../render/Texture.h"

Resource* TextureManager_GetResource(const char* filenameWithoutExtension);
Texture* TextureManager_GetResourceData(const char* filenameWithoutExtension);
Resource* TextureManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path);
const char* TextureManager_GetDatFileName();
void TextureManager_LoadAllFromDat();
void TextureManager_Dispose(const char* filenameWithoutExtension);
void TextureManager_DisposeAll();
int64_t TextureManager_Length();
Resource* TextureManager_GetResourceByIndex(int index);
Texture* TextureManager_GetResourceDataByIndex(int index);