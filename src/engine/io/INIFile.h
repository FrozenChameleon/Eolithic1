/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"

typedef struct INIFile INIFile;
typedef struct BufferReader BufferReader;

INIFile* INIFile_Create_From_Binary(BufferReader* br);
void INIFile_Dispose(INIFile* ini);
uint64_t INIFile_GetRefs();
int64_t INIFile_GetLength(INIFile* ini);
const char* INIFile_GetKey(INIFile* ini, int32_t index);
const char* INIFile_GetValue(INIFile* ini, int32_t index);