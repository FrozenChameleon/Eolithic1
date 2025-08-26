/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Utils.h"

#include "../../third_party/stb_ds.h"
#include "SDL3/SDL.h"
#include "stdlib.h"
#include "float.h"

static uint64_t _mStringRefs;
static uint64_t _mMallocRefs;
static SharedFixedChar260** _mDynamicSharedStringBuffers;

SharedFixedChar260* Utils_GetSharedFixedChar260()
{
	int32_t len = arrlen(_mDynamicSharedStringBuffers);
	for (int i = 0; i < len; i += 1)
	{
		SharedFixedChar260* sharedStringBuffer = _mDynamicSharedStringBuffers[i];
		if (!sharedStringBuffer->mIsInUse)
		{
			memset(&sharedStringBuffer->mBuffer, 0, FIXED_CHAR_260_LENGTH);
			sharedStringBuffer->mIsInUse = true;
			return sharedStringBuffer;
		}
	}

	SharedFixedChar260* bufferToAdd = Utils_malloc(sizeof(SharedFixedChar260));
	memset(bufferToAdd, 0, sizeof(SharedFixedChar260));
	arrput(_mDynamicSharedStringBuffers, bufferToAdd);
	bufferToAdd->mIsInUse = true;
	return bufferToAdd;
}
int32_t Utils_GetAmountOfSharedFixedChar260InUse()
{
	int32_t counter = 0;
	int32_t len = arrlen(_mDynamicSharedStringBuffers);
	for (int i = 0; i < len; i += 1)
	{
		SharedFixedChar260* sharedStringBuffer = _mDynamicSharedStringBuffers[i];
		if (sharedStringBuffer->mIsInUse)
		{
			counter += 1;
		}
	}
	return counter;
}
uint64_t Utils_GetMallocRefs()
{
	return _mMallocRefs;
}
uint64_t Utils_GetStringRefs()
{
	return _mStringRefs;
}
int32_t Utils_memcmp(const void* s1, const void* s2, size_t len)
{
	return SDL_memcmp(s1, s2, len);
}
void Utils_memcpy(void* _Dst, const void* _Src, size_t _Size)
{
	SDL_memcpy(_Dst, _Src, _Size);
}
void Utils_memset(void* _Dst, int _Val, size_t _Size)
{
	SDL_memset(_Dst, _Val, _Size);
}
void* Utils_malloc(size_t size)
{
	_mMallocRefs += 1;
	return SDL_malloc(size);
}
void Utils_free(void* mem)
{
	_mMallocRefs -= 1;
	SDL_free(mem);
}
size_t Utils_strnlen(const char* str, size_t maxlen)
{
	return SDL_strnlen(str, maxlen);
}
size_t Utils_strlcpy(char* dst, const char* src, size_t maxlen)
{
	return SDL_strlcpy(dst, src, maxlen);
}
size_t Utils_strlcat(char* dst, const char* src, size_t maxlen)
{
	return SDL_strlcat(dst, src, maxlen);
}
float Utils_ParseFloat(const char* str)
{
	return (float)SDL_atof(str);
}
int32_t Utils_ParseInt(const char* str)
{
	return SDL_atoi(str);
}
bool Utils_StringEqualTo(const char* str1, const char* str2)
{
	return (SDL_strcmp(str1, str2) == 0);
}
int32_t Utils_IntToString(int32_t value, char* buffer, size_t maxlen)
{
	return SDL_snprintf(buffer, maxlen, "%d", value);
}
int32_t Utils_FloatToString(float value, char* buffer, size_t maxlen)
{
	return SDL_snprintf(buffer, maxlen, "%.9g", value); //9 FROM FROM FLT_DECIMAL_DIG in float.h
}
int32_t Utils_DoubleToString(double value, char* buffer, size_t maxlen)
{
	return SDL_snprintf(buffer, maxlen, "%.17g", value); //17 FROM DBL_DECIMAL_DIG in float.h
}
char* Utils_CreateStringBuffer(size_t length)
{
	_mStringRefs += 1;
	return Utils_malloc(sizeof(char) * length);
}
char* Utils_CreateStringCopy(const char* str)
{
	_mStringRefs += 1;
	return SDL_strdup(str);
}
void Utils_FreeString(char* str)
{
	_mStringRefs -= 1;
	Utils_free(str);
}
void Utils_ResetArrayAsBool(bool* values, size_t len, bool valueToSet)
{
	for (int i = 0; i < len; i += 1)
	{
		values[i] = false;
	}
}
void Utils_ResetArrayAsInt32(int32_t* values, size_t len, int32_t valueToSet)
{
	for (int i = 0; i < len; i += 1)
	{
		values[i] = 0;
	}
}
void Utils_ResetArrayAsSingle(float* values, size_t len, float valueToSet)
{
	for (int i = 0; i < len; i += 1)
	{
		values[i] = 0;
	}
}
void Utils_ToggleFullscreenButton()
{
	//TODO
}
int32_t Utils_StringIndexOf(char findThis, const char* strInThis, size_t maxlen, bool findLastIndex)
{
	int32_t len = Utils_strnlen(strInThis, maxlen);
	int32_t loc = -1;
	for (int i = 0; i < len; i += 1)
	{
		if (strInThis[i] == findThis)
		{
			if (!findLastIndex)
			{
				return loc;
			}
			else
			{
				loc = i;
			}
		}
	}
	return loc;
}
