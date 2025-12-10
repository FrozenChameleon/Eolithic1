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
	struct { char* key; char* value; } *sh_values;
} IniFile;

INIFile* INIFile_Create_From_Binary(const char* path)
{
	_mRefs += 1;

	INIFile* ini = Utils_malloc(sizeof(INIFile));
	Utils_memset(ini, 0, sizeof(INIFile));
	sh_new_arena(ini->sh_values);
	BufferReader* br = BufferReader_CreateFromPath(path);
	while (BufferReader_HasNext(br))
	{
		char* key = Utils_CreateStringBuffer(EE_FILENAME_MAX);
		char* value = Utils_CreateStringBuffer(EE_FILENAME_MAX);
		BufferReader_ReadString(br, key, EE_FILENAME_MAX);
		BufferReader_ReadString(br, value, EE_FILENAME_MAX);
		shput(ini->sh_values, key, value);
	}
	BufferReader_Dispose(br, false);
	return ini;
}
void INIFile_Dispose(INIFile* ini)
{
	_mRefs -= 1;

	if (ini->sh_values != NULL)
	{
		shfree(ini->sh_values);
		//TODO MEMLEAK?
	}

	Utils_free(ini);
}
uint64_t INIFile_GetRefs()
{
	return _mRefs;
}
int64_t INIFile_GetLength(INIFile* ini)
{
	return shlen(ini->sh_values);
}
const char* INIFile_GetKey(INIFile* ini, int32_t index)
{
	return ini->sh_values[index].key;
}
const char* INIFile_GetValue(INIFile* ini, int32_t index)
{
	return ini->sh_values[index].value;
}
