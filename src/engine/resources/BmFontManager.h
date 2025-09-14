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
#include "../font/BmFont.h"

Resource* BmFontManager_GetResource(const char* filenameWithoutExtension);
BmFont* BmFontManager_GetResourceData(const char* filenameWithoutExtension);
Resource* BmFontManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path);
const char* BmFontManager_GetDatFileName();
void BmFontManager_LoadAllFromDat();
void BmFontManager_Dispose(const char* filenameWithoutExtension);
void BmFontManager_DisposeAll();
int BmFontManager_Length();
Resource* BmFontManager_GetResourceByIndex(int index);
BmFont* BmFontManager_GetResourceDataByIndex(int index);