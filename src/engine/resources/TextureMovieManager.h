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

const char* TextureMovieManager_GetKey(const char* filenameWithoutExtension);
Resource* TextureMovieManager_GetResource(const char* filenameWithoutExtension);
Texture* TextureMovieManager_GetResourceData(const char* filenameWithoutExtension);
Resource* TextureMovieManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path);
const char* TextureMovieManager_GetDatFileName();
void TextureMovieManager_LoadAllFromDat();
void TextureMovieManager_Dispose(const char* filenameWithoutExtension);
void TextureMovieManager_DisposeAll();
int64_t TextureMovieManager_Length();
Resource* TextureMovieManager_GetResourceByIndex(int index);
Texture* TextureMovieManager_GetResourceDataByIndex(int index);