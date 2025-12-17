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
#include "../leveldata/Particle.h"

bool ParticleManager_HasResource(const char* filenameWithoutExtension);
Resource* ParticleManager_GetResource(const char* filenameWithoutExtension);
Particle* ParticleManager_GetResourceData(const char* filenameWithoutExtension);
Resource* ParticleManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path);
const char* ParticleManager_GetDatFileName();
void ParticleManager_LoadAllFromDat();
void ParticleManager_Dispose(const char* filenameWithoutExtension);
void ParticleManager_DisposeAll();
int64_t ParticleManager_Length();
Resource* ParticleManager_GetResourceByIndex(int index);
Particle* ParticleManager_GetResourceDataByIndex(int index);