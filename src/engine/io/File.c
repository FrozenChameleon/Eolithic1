/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "File.h"

#include "SDL3/SDL.h"
#include "../utils/Utils.h"
#include "../utils/Macros.h"
#include "../utils/Exception.h"

#ifdef _WIN32
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif

static const char* _mBasePath;
static const char* _mPrefPath;

#define LARGE_CHAR_BUFFER_LEN 8192
static char _mLargeCharBuffer[LARGE_CHAR_BUFFER_LEN];

FixedByteBuffer* File_ReadAll(const char* path)
{
	MString* sharedStringBuffer = File_Combine2(File_GetBasePath(), path);
	SDL_IOStream* rwops = SDL_IOFromFile(MString_GetText(sharedStringBuffer), "rb");
	MString_Dispose(&sharedStringBuffer);
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
	MString* sharedStringBuffer = File_Combine2(File_GetBasePath(), path);
	SDL_IOStream* file = SDL_IOFromFile(MString_GetText(sharedStringBuffer), "r");
	MString_Dispose(&sharedStringBuffer);
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
void File_AppendPathSeparator(MString** str)
{
	MString_AddAssignChar(str, PATH_SEPARATOR);
}

static MString* File_GetFileNameHelper(const char* path, bool removeTheExtension)
{
	int32_t len = Utils_strlen(path);
	int32_t loc = Utils_StringIndexOf(PATH_SEPARATOR, path, len + 1, true);
	if (loc == -1)
	{
		return NULL;
	}

	MString* returnStr = NULL;
	MString_AssignEmpty(&returnStr, len + 1);
	char* returnStrText = MString_GetText(returnStr);

	int32_t counter = 0;
	for (int i = (loc + 1); i < len; i += 1)
	{
		if (removeTheExtension)
		{
			if (path[i] == '.')
			{
				break;
			}
		}
		returnStrText[counter] = path[i];
		counter += 1;
	}

	returnStrText[counter + 1] = '\0';
	return returnStr;
}
MString* File_GetFileName(const char* path)
{
	return File_GetFileNameHelper(path, false);
}
MString* File_GetFileNameWithoutExtension(const char* path)
{
	return 	File_GetFileNameHelper(path, true);
}
IStringArray* File_ReadAllToStrings(BufferReader* br)
{
	uint64_t len = BufferReader_GetSize(br);
	uint8_t* bufferData = BufferReader_GetBufferData(br);
	IStringArray* sa = IStringArray_Create();
	int counter = 0;
	for (int i = 0; i < (len + 1); i += 1) //Add +1 to len because...
	{
		if (counter >= LARGE_CHAR_BUFFER_LEN)
		{
			Exception_Run("Buffer overflow in read all strings...", false);
			return sa;
		}

		bool isAtEndOfString = false;
		if (i == len) //We need to make sure we get the stuff at the end...
		{
			isAtEndOfString = true;
		}
		else
		{
			char c = bufferData[i];
			if (c == '\r')
			{
				continue;
			}
			if (c == '\n')
			{
				isAtEndOfString = true;
			}
			else
			{
				_mLargeCharBuffer[counter] = c;
				counter += 1;
			}
		}

		if (isAtEndOfString)
		{
			_mLargeCharBuffer[counter] = '\0';
			IStringArray_Add(sa, _mLargeCharBuffer);
			Utils_memset(_mLargeCharBuffer, 0, LARGE_CHAR_BUFFER_LEN);
			counter = 0;
		}
	}
	return sa;
}

static void CombineHelper(MString** str, const char* addedPath)
{
	MString* newStr = *str;
	MString_AddAssignChar(&newStr, PATH_SEPARATOR);
	MString_AddAssignString(&newStr, addedPath);
	*str = newStr;
}
MString* File_Combine2(const char* path1, const char* path2)
{
	MString* str = NULL;
	MString_Assign(&str, path1);
	CombineHelper(&str, path2);
	return str;
}
MString* File_Combine3(const char* path1, const char* path2, const char* path3)
{
	MString* str = File_Combine2(path1, path2);
	CombineHelper(&str, path3);
	return str;
}
MString* File_Combine4(const char* path1, const char* path2, const char* path3, const char* path4)
{
	MString* str = File_Combine3(path1, path2, path3);
	CombineHelper(&str, path4);
	return str;
}
MString* File_Combine5(const char* path1, const char* path2, const char* path3, const char* path4, const char* path5)
{
	MString* str = File_Combine4(path1, path2, path3, path4);
	CombineHelper(&str, path5);
	return str;
}
MString* File_Combine6(const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6)
{
	MString* str = File_Combine5(path1, path2, path3, path4, path5);
	CombineHelper(&str, path6);
	return str;
}
MString* File_Combine7(const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7)
{
	MString* str = File_Combine6(path1, path2, path3, path4, path5, path6);
	CombineHelper(&str, path7);
	return str;
}
MString* File_Combine8(const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8)
{
	MString* str = File_Combine7(path1, path2, path3, path4, path5, path6, path7);
	CombineHelper(&str, path8);
	return str;
}
MString* File_Combine9(const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8, const char* path9)
{
	MString* str = File_Combine8(path1, path2, path3, path4, path5, path6, path7, path8);
	CombineHelper(&str, path9);
	return str;
}
MString* File_Combine10(const char* path1, const char* path2, const char* path3, const char* path4, const char* path5, const char* path6, const char* path7,
	const char* path8, const char* path9, const char* path10)
{
	MString* str = File_Combine9(path1, path2, path3, path4, path5, path6, path7, path8, path9);
	CombineHelper(&str, path10);
	return str;
}