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
#include "BufferReader.h"
#include "../utils/IStringArray.h"
#include "../utils/MString.h"

void File_AppendPathSeparator(MString** str);
FixedByteBuffer* File_ReadAll(const char* path);
bool File_Exists(const char* path);
const char* File_GetBasePath();
const char* File_GetPrefPath();

MString* File_GetFileName(const char* path);
MString* File_GetFileNameWithoutExtension(const char* path);
IStringArray* File_ReadAllToStrings(BufferReader* br);

MString* File_Combine2(const char* path1, const char* path2);
MString* File_Combine3(const char* path1, const char* path2, const char* path3);
MString* File_Combine4(const char* path1, const char* path2, const char* path3, const char* path4);
MString* File_Combine5(const char* path1, const char* path2, const char* path3, const char* path4, const char* path5);
MString* File_Combine6(const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6);
MString* File_Combine7(const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7);
MString* File_Combine8(const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8);
MString* File_Combine9(const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8, const char* path9);
MString* File_Combine10(const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8, const char* path9, const char* path10);