/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "File.h"

#include "SDL3/SDL.h"
#include "../utils/Utils.h"
#include "../utils/Macros.h"

#ifdef _WIN32
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif

static const char* _mBasePath;
static const char* _mPrefPath;

FixedByteBuffer* File_ReadAll(const char* path)
{
	SharedFixedChar260* sharedStringBuffer = Utils_CreateSharedFixedChar260();
	File_Combine2(sharedStringBuffer, File_GetBasePath(), path);
	SDL_IOStream* rwops = SDL_IOFromFile(sharedStringBuffer, "rb");
	Utils_DisposeSharedFixedChar260(sharedStringBuffer);
	if (rwops == NULL)
	{
		return NULL;
	}
	int64_t dataSize = SDL_GetIOSize(rwops);
	if (dataSize < 0)
	{
		return NULL;
	}
	FixedByteBuffer* fbb = FixedByteBuffer_Create(dataSize);
	SDL_ReadIO(rwops, FixedByteBuffer_GetBuffer(fbb), dataSize);
	SDL_CloseIO(rwops);
	return fbb;
}
bool File_Exists(const char* path)
{
	SharedFixedChar260* sharedStringBuffer = Utils_CreateSharedFixedChar260();
	File_Combine2(sharedStringBuffer, File_GetBasePath(), path);
	SDL_IOStream* file = SDL_IOFromFile(sharedStringBuffer, "r");
	Utils_DisposeSharedFixedChar260(sharedStringBuffer);
	if (file != NULL)
	{
		SDL_CloseIO(file);
		return true;
	}
	else
	{
		return false;
	}
}
const char* File_GetBasePath()
{
	if (_mBasePath == NULL)
	{
		_mBasePath = SDL_GetBasePath();
	}

	return _mBasePath;
}
const char* File_GetPrefPath()
{
	if (_mPrefPath == NULL)
	{
		_mPrefPath = SDL_GetPrefPath("IcedLizardGames", "TestApp");
	}

	return _mPrefPath;
}
void File_AppendPathSeparator(FixedChar260* dst)
{
	size_t dstLen = Utils_strnlen(dst, FIXED_CHAR_260_LENGTH);
	if (dst->mValue[dstLen - 1] != PATH_SEPARATOR)
	{
		if ((dstLen + 1) > FIXED_CHAR_260_LENGTH)
		{
			return;
		}
		dst->mValue[dstLen] = PATH_SEPARATOR;
		dst->mValue[dstLen + 1] = '\0';
	}
}

static void INTERNAL_File_Combine2(FixedChar260* dst, const char* path1, const char* path2)
{
	File_AppendPathSeparator(dst);
	Utils_strlcat(dst, path2, FIXED_CHAR_260_LENGTH);
}
static void INTERNAL_File_Combine3(FixedChar260* dst, const char* path1, const char* path2, const char* path3)
{
	INTERNAL_File_Combine2(dst, path1, path2);
	INTERNAL_File_Combine2(dst, dst, path3);
}
static void INTERNAL_File_Combine4(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4)
{
	INTERNAL_File_Combine3(dst, path1, path2, path3);
	INTERNAL_File_Combine2(dst, dst, path4);
}
static void INTERNAL_File_Combine5(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5)
{
	INTERNAL_File_Combine4(dst, path1, path2, path3, path4);
	INTERNAL_File_Combine2(dst, dst, path5);
}
static void INTERNAL_File_Combine6(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6)
{
	INTERNAL_File_Combine5(dst, path1, path2, path3, path4, path5);
	INTERNAL_File_Combine2(dst, dst, path6);
}
static void INTERNAL_File_Combine7(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7)
{
	INTERNAL_File_Combine6(dst, path1, path2, path3, path4, path5, path6);
	INTERNAL_File_Combine2(dst, dst, path7);
}
static void INTERNAL_File_Combine8(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8)
{
	INTERNAL_File_Combine7(dst, path1, path2, path3, path4, path5, path6, path7);
	INTERNAL_File_Combine2(dst, dst, path8);
}
static void INTERNAL_File_Combine9(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8, const char* path9)
{
	INTERNAL_File_Combine8(dst, path1, path2, path3, path4, path5, path6, path7, path8);
	INTERNAL_File_Combine2(dst, dst, path9);
}
static void INTERNAL_File_Combine10(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8, const char* path9, const char* path10)
{
	INTERNAL_File_Combine9(dst, path1, path2, path3, path4, path5, path6, path7, path8, path9);
	INTERNAL_File_Combine2(dst, dst, path10);
}

static void File_CombineHelper(FixedChar260* dst, const char* path1)
{
	Utils_memset(dst, 0, FIXED_CHAR_260_LENGTH);
	Utils_strlcpy(dst, path1, FIXED_CHAR_260_LENGTH);
}
void File_Combine2(FixedChar260* dst, const char* path1, const char* path2)
{
	File_CombineHelper(dst, path1);
	INTERNAL_File_Combine2(dst, path1, path2);
}
void File_Combine3(FixedChar260* dst, const char* path1, const char* path2, const char* path3)
{
	File_CombineHelper(dst, path1);
	INTERNAL_File_Combine3(dst, path1, path2, path3);
}
void File_Combine4(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4)
{
	File_CombineHelper(dst, path1);
	INTERNAL_File_Combine4(dst, path1, path2, path3, path4);
}
void File_Combine5(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5)
{
	File_CombineHelper(dst, path1);
	INTERNAL_File_Combine5(dst, path1, path2, path3, path4, path5);
}
void File_Combine6(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6)
{
	File_CombineHelper(dst, path1);
	INTERNAL_File_Combine6(dst, path1, path2, path3, path4, path5, path6);
}
void File_Combine7(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7)
{
	File_CombineHelper(dst, path1);
	INTERNAL_File_Combine7(dst, path1, path2, path3, path4, path5, path6, path7);
}
void File_Combine8(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8)
{
	File_CombineHelper(dst, path1);
	INTERNAL_File_Combine8(dst, path1, path2, path3, path4, path5, path6, path7, path8);
}
void File_Combine9(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8, const char* path9)
{
	File_CombineHelper(dst, path1);
	INTERNAL_File_Combine9(dst, path1, path2, path3, path4, path5, path6, path7, path8, path9);
}
void File_Combine10(FixedChar260* dst, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8, const char* path9, const char* path10)
{
	File_CombineHelper(dst, path1);
	INTERNAL_File_Combine10(dst, path1, path2, path3, path4, path5, path6, path7, path8, path9, path10);
}

static void File_GetFileNameHelper(FixedChar260* dst, const FixedChar260* path, bool removeTheExtension)
{
	int32_t loc = Utils_StringIndexOf(PATH_SEPARATOR, path, FIXED_CHAR_260_LENGTH, true);
	if (loc == -1)
	{
		return;
	}

	Utils_memset(dst, 0, FIXED_CHAR_260_LENGTH);

	int32_t counter = 0;
	int32_t len = Utils_strnlen(path, FIXED_CHAR_260_LENGTH);
	for (int i = (loc + 1); i < len; i += 1)
	{
		if (removeTheExtension)
		{
			if (path->mValue[i] == '.')
			{
				break;
			}
		}
		dst->mValue[counter] = path->mValue[i];
		counter += 1;
	}

	dst->mValue[counter + 1] = '\0';
}
void File_GetFileName(FixedChar260* dst, const FixedChar260* path)
{
	File_GetFileNameHelper(dst, path, false);
}
void File_GetFileNameWithoutExtension(FixedChar260* dst, const FixedChar260* path)
{
	File_GetFileNameHelper(dst, path, true);
}
