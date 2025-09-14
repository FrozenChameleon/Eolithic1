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
#include "../audio/SoundEffect.h"

Resource* SoundEffectManager_GetResource(const char* filenameWithoutExtension);
SoundEffect* SoundEffectManager_GetResourceData(const char* filenameWithoutExtension);
Resource* SoundEffectManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path);
const char* SoundEffectManager_GetDatFileName();
void SoundEffectManager_LoadAllFromDat();
void SoundEffectManager_Dispose(const char* filenameWithoutExtension);
void SoundEffectManager_DisposeAll();
int SoundEffectManager_Length();
Resource* SoundEffectManager_GetResourceByIndex(int index);
SoundEffect* SoundEffectManager_GetResourceDataByIndex(int index);