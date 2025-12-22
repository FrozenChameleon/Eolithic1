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
#include "../font/TtFont.h"

bool TTFontManager_HasResource(const char* filenameWithoutExtension);
Resource* TTFontManager_GetResource(const char* filenameWithoutExtension);
TTFont* TTFontManager_GetResourceData(const char* filenameWithoutExtension);
Resource* TTFontManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path);
const char* TTFontManager_GetDatFileName();
void TTFontManager_LoadAllFromDat();
void TTFontManager_Dispose(const char* filenameWithoutExtension);
void TTFontManager_DisposeAll();
int64_t TTFontManager_Length();
Resource* TTFontManager_GetResourceByIndex(int index);
TTFont* TTFontManager_GetResourceDataByIndex(int index);