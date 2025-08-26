/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "IniFile.h"

#include "../../third_party/stb_ds.h"
#include "../utils/Utils.h"
#include "BufferReader.h"
#include "../io/File.h"

static uint64_t _mRefs;

typedef struct INIFile
{
	struct { char* key; char* value; } *mData;
} IniFile;

INIFile* INIFile_Create_From_Binary(const char* path)
{
	_mRefs += 1;

	INIFile* ini = Utils_malloc(sizeof(INIFile));
	ini->mData = NULL;
	BufferReader* br = BufferReader_CreateFromPath(path);
	while (BufferReader_HasNext(br))
	{
		char* key = Utils_CreateStringBuffer(EE_PATH_MAX);
		char* value = Utils_CreateStringBuffer(EE_PATH_MAX);
		BufferReader_ReadString(br, key, EE_PATH_MAX);
		BufferReader_ReadString(br, value, EE_PATH_MAX);
		shput(ini->mData, key, value);
	}
	BufferReader_Dispose(br, false);
	return ini;
}
void INIFile_Dispose(INIFile* ini)
{
	_mRefs -= 1;

	if (ini->mData != NULL)
	{
		int64_t len = INIFile_GetLength(ini);
		for (int i = 0; i < len; i += 1)
		{
			Utils_FreeString(ini->mData[i].key);
			Utils_FreeString(ini->mData[i].value);
		}
		shfree(ini->mData);
	}

	Utils_free(ini);
}
uint64_t INIFile_GetRefs()
{
	return _mRefs;
}
int64_t INIFile_GetLength(INIFile* ini)
{
	return shlen(ini->mData);
}
const char* INIFile_GetKey(INIFile* ini, int index)
{
	return ini->mData[index].key;
}
const char* INIFile_GetValue(INIFile* ini, int index)
{
	return ini->mData[index].value;
}
