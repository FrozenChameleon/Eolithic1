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
#include "../render/ShaderProgram.h"

bool ShaderProgramManager_HasResource(const char* filenameWithoutExtension);
Resource* ShaderProgramManager_GetResource(const char* filenameWithoutExtension);
ShaderProgram* ShaderProgramManager_GetResourceData(const char* filenameWithoutExtension);
Resource* ShaderProgramManager_LoadAssetFromStreamAndCreateResource(BufferReader* br, const char* filenameWithoutExtension, const char* path);
const char* ShaderProgramManager_GetDatFileName();
void ShaderProgramManager_LoadAllFromDat();
void ShaderProgramManager_Dispose(const char* filenameWithoutExtension);
void ShaderProgramManager_DisposeAll();
int64_t ShaderProgramManager_Length();
Resource* ShaderProgramManager_GetResourceByIndex(int index);
ShaderProgram* ShaderProgramManager_GetResourceDataByIndex(int index);