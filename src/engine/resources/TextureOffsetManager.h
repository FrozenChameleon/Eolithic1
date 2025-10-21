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
#include "../render/TextureOffset.h"

Resource* TextureOffsetManager_GetResource(const char* filenameWithoutExtension);
TextureOffset* TextureOffsetManager_GetResourceData(const char* filenameWithoutExtension);
Resource* TextureOffsetManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path);
const char* TextureOffsetManager_GetDatFileName();
void TextureOffsetManager_LoadAllFromDat();
void TextureOffsetManager_Dispose(const char* filenameWithoutExtension);
void TextureOffsetManager_DisposeAll();
int64_t TextureOffsetManager_Length();
Resource* TextureOffsetManager_GetResourceByIndex(int index);
TextureOffset* TextureOffsetManager_GetResourceDataByIndex(int index);