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

Resource* TextureFontManager_GetResource(const char* filenameWithoutExtension);
Texture* TextureFontManager_GetResourceData(const char* filenameWithoutExtension);
Resource* TextureFontManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path);
const char* TextureFontManager_GetDatFileName();
void TextureFontManager_LoadAllFromDat();
void TextureFontManager_Dispose(const char* filenameWithoutExtension);
void TextureFontManager_DisposeAll();
int64_t TextureFontManager_Length();
Resource* TextureFontManager_GetResourceByIndex(int index);
Texture* TextureFontManager_GetResourceDataByIndex(int index);