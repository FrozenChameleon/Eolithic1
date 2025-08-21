/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Utils.h"

#include "SDL3/SDL.h"
#include "stdlib.h"
#include "float.h"

static uint64_t _mStringRefs;
static uint64_t _mMallocRefs;
static FixedChar260 _mSharedPathStringBuffer;

FixedChar260* Utils_GetSharedStringBuffer()
{
	return &_mSharedPathStringBuffer;
}
uint64_t Utils_GetMallocRefs()
{
	return _mMallocRefs;
}
uint64_t Utils_GetStringRefs()
{
	return _mStringRefs;
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
