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
	char pathBuffer[EE_PATH_MAX];
	File_Combine2(pathBuffer, EE_PATH_MAX, File_GetBasePath(), path);
	SDL_IOStream* rwops = SDL_IOFromFile(pathBuffer, "rb");
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
	char combinedPath[EE_PATH_MAX];
	File_Combine2(combinedPath, EE_PATH_MAX, File_GetBasePath(), path);
	SDL_IOStream* file = SDL_IOFromFile(combinedPath, "r");
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
void File_AppendPathSeparator(char* dst, size_t maxlen)
{
	size_t dstLen = Utils_strnlen(dst, maxlen);
	if (dst[dstLen - 1] != PATH_SEPARATOR)
	{
		if ((dstLen + 1) > maxlen)
		{
			return;
		}
		dst[dstLen] = PATH_SEPARATOR;
		dst[dstLen + 1] = '\0';
	}
}

static void INTERNAL_File_Combine2(char* dst, size_t maxlen, const char* path1, const char* path2)
{
	File_AppendPathSeparator(dst, maxlen);
	Utils_strlcat(dst, path2, maxlen);
}
static void INTERNAL_File_Combine3(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3)
{
	INTERNAL_File_Combine2(dst, maxlen, path1, path2);
	INTERNAL_File_Combine2(dst, maxlen, dst, path3);
}
static void INTERNAL_File_Combine4(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4)
{
	INTERNAL_File_Combine3(dst, maxlen, path1, path2, path3);
	INTERNAL_File_Combine2(dst, maxlen, dst, path4);
}
static void INTERNAL_File_Combine5(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5)
{
	INTERNAL_File_Combine4(dst, maxlen, path1, path2, path3, path4);
	INTERNAL_File_Combine2(dst, maxlen, dst, path5);
}
static void INTERNAL_File_Combine6(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6)
{
	INTERNAL_File_Combine5(dst, maxlen, path1, path2, path3, path4, path5);
	INTERNAL_File_Combine2(dst, maxlen, dst, path6);
}
static void INTERNAL_File_Combine7(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7)
{
	INTERNAL_File_Combine6(dst, maxlen, path1, path2, path3, path4, path5, path6);
	INTERNAL_File_Combine2(dst, maxlen, dst, path7);
}
static void INTERNAL_File_Combine8(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8)
{
	INTERNAL_File_Combine7(dst, maxlen, path1, path2, path3, path4, path5, path6, path7);
	INTERNAL_File_Combine2(dst, maxlen, dst, path8);
}
static void INTERNAL_File_Combine9(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8, const char* path9)
{
	INTERNAL_File_Combine8(dst, maxlen, path1, path2, path3, path4, path5, path6, path7, path8);
	INTERNAL_File_Combine2(dst, maxlen, dst, path9);
}
static void INTERNAL_File_Combine10(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8, const char* path9, const char* path10)
{
	INTERNAL_File_Combine9(dst, maxlen, path1, path2, path3, path4, path5, path6, path7, path8, path9);
	INTERNAL_File_Combine2(dst, maxlen, dst, path10);
}

static void File_CombineHelper(char* dst, size_t maxlen, const char* path1)
{
	memset(dst, 0, maxlen);
	Utils_strlcpy(dst, path1, maxlen);
}
void File_Combine2(char* dst, size_t maxlen, const char* path1, const char* path2)
{
	File_CombineHelper(dst, maxlen, path1);
	INTERNAL_File_Combine2(dst, maxlen, path1, path2);
}
void File_Combine3(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3)
{
	File_CombineHelper(dst, maxlen, path1);
	INTERNAL_File_Combine3(dst, maxlen, path1, path2, path3);
}
void File_Combine4(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4)
{
	File_CombineHelper(dst, maxlen, path1);
	INTERNAL_File_Combine4(dst, maxlen, path1, path2, path3, path4);
}
void File_Combine5(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5)
{
	File_CombineHelper(dst, maxlen, path1);
	INTERNAL_File_Combine5(dst, maxlen, path1, path2, path3, path4, path5);
}
void File_Combine6(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6)
{
	File_CombineHelper(dst, maxlen, path1);
	INTERNAL_File_Combine6(dst, maxlen, path1, path2, path3, path4, path5, path6);
}
void File_Combine7(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7)
{
	File_CombineHelper(dst, maxlen, path1);
	INTERNAL_File_Combine7(dst, maxlen, path1, path2, path3, path4, path5, path6, path7);
}
void File_Combine8(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8)
{
	File_CombineHelper(dst, maxlen, path1);
	INTERNAL_File_Combine8(dst, maxlen, path1, path2, path3, path4, path5, path6, path7, path8);
}
void File_Combine9(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8, const char* path9)
{
	File_CombineHelper(dst, maxlen, path1);
	INTERNAL_File_Combine9(dst, maxlen, path1, path2, path3, path4, path5, path6, path7, path8, path9);
}
void File_Combine10(char* dst, size_t maxlen, const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8, const char* path9, const char* path10)
{
	File_CombineHelper(dst, maxlen, path1);
	INTERNAL_File_Combine10(dst, maxlen, path1, path2, path3, path4, path5, path6, path7, path8, path9, path10);
}