/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdbool.h"
#include "stdint.h"
#include "FixedByteBuffer.h"
#include "../utils/Macros.h"
#include "../utils/FixedChar260.h"

void File_AppendPathSeparator(FixedChar260* dst);
FixedByteBuffer* File_ReadAll(const char* path);
bool File_Exists(const char* path);
const char* File_GetBasePath();
const char* File_GetPrefPath();

void File_Combine2(FixedChar260* dst, const char* path1, const char* path2);
void File_Combine3(FixedChar260* dst, const char* path1, const char* path2, const char* path3);
void File_Combine4(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4);
void File_Combine5(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5);
void File_Combine6(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6);
void File_Combine7(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7);
void File_Combine8(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8);
void File_Combine9(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8, const char* path9);
void File_Combine10(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8, const char* path9, const char* path10);

void File_GetFileName(FixedChar260* dst, const FixedChar260* path);
void File_GetFileNameWithoutExtension(FixedChar260* dst, const FixedChar260* path);