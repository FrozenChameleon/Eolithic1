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

void File_AppendPathSeparator(char* dst, size_t maxlen);
FixedByteBuffer* File_ReadAll(const char* path);
bool File_Exists(const char* path);
const char* File_GetBasePath();
const char* File_GetPrefPath();
void File_Combine2(char* dst, size_t maxlen, const char* path1, const char* path2);
void File_Combine3(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3);
void File_Combine4(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4);
void File_Combine5(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5);
void File_Combine6(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6);
void File_Combine7(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7);
void File_Combine8(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8);
void File_Combine9(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8, const char* path9);
void File_Combine10(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8, const char* path9, const char* path10);