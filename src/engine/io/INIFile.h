/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"

typedef struct INIFile INIFile;

INIFile* INIFile_Create_From_Binary(const char* path);
void INIFile_Dispose(INIFile* ini);
uint64_t INIFile_GetRefs();
int64_t INIFile_GetLength(INIFile* ini);
const char* INIFile_GetKey(INIFile* ini, int index);
const char* INIFile_GetValue(INIFile* ini, int index);