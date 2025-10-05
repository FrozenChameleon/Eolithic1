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
#include "../math/Math.h"
#include "Cvars.h"
#include "../render/Renderer.h"

static uint64_t _mStringRefs;
static uint64_t _mMallocRefs;
static SharedFixedChar260** _mDynamicSharedStringBuffers;

#define LARGE_CHAR_BUFFER_LEN 8192
static char _mLargeCharBuffer[LARGE_CHAR_BUFFER_LEN];

SharedFixedChar260* Utils_CreateSharedFixedChar260()
{
	int32_t len = arrlen(_mDynamicSharedStringBuffers);
	for (int i = 0; i < len; i += 1)
	{
		SharedFixedChar260* sharedStringBuffer = _mDynamicSharedStringBuffers[i];
		if (!sharedStringBuffer->mIsInUse)
		{
			Utils_memset(&sharedStringBuffer->mBuffer, 0, FIXED_CHAR_260_LENGTH);
			sharedStringBuffer->mIsInUse = true;
			return sharedStringBuffer;
		}
	}

	SharedFixedChar260* bufferToAdd = Utils_malloc(sizeof(SharedFixedChar260));
	Utils_memset(bufferToAdd, 0, sizeof(SharedFixedChar260));
	arrput(_mDynamicSharedStringBuffers, bufferToAdd);
	bufferToAdd->mIsInUse = true;
	return bufferToAdd;
}
void Utils_DisposeSharedFixedChar260(SharedFixedChar260* sfc)
{
	sfc->mIsInUse = false;
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
void Utils_FreeAllSharedFixedChar260()
{
	int32_t len = arrlen(_mDynamicSharedStringBuffers);
	for (int i = 0; i < len; i += 1)
	{
		Utils_free(_mDynamicSharedStringBuffers[i]);
	}
	arrfree(_mDynamicSharedStringBuffers);
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
void* Utils_calloc(size_t nmemb, size_t size)
{
	_mMallocRefs += 1;
	return SDL_calloc(nmemb, size);
}
void Utils_free(void* mem)
{
	_mMallocRefs -= 1;
	SDL_free(mem);
}
size_t Utils_strlen(const char* str)
{
	return SDL_strlen(str);
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
	if ((str1 == NULL) && (str2 == NULL))
	{
		return true;
	}
	else if ((str1 != NULL) && (str2 == NULL))
	{
		return false;
	}
	else if ((str1 == NULL) && (str2 != NULL))
	{
		return false;
	}
	else
	{
		return (SDL_strcmp(str1, str2) == 0);
	}
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
double Utils_GetNormalStepLength()
{
	return MATH_TICK_60HZ;
}
double Utils_GetInterpolated(double delta, float current, float last)
{
	float diff = current - last;
	double mul = delta / Utils_GetNormalStepLength();
	return last + (diff * mul);
}
Rectangle Utils_GetInternalRectangle()
{
	Rectangle rect = { 0, 0, Utils_GetInternalWidth(), Utils_GetInternalHeight() };
	return rect;
}
Rectangle Utils_GetInternalRenderRectangle()
{
	Rectangle rect = { 0, 0, Utils_GetInternalRenderWidth(), Utils_GetInternalRenderHeight() };
	return rect;
}
int Utils_GetInternalWidth()
{
	return Cvars_GetAsInt(CVARS_ENGINE_INTERNAL_WIDTH);
}
int Utils_GetInternalHeight()
{
	return Cvars_GetAsInt(CVARS_ENGINE_INTERNAL_HEIGHT);
}
int Utils_GetInternalRenderWidth()
{
	return Cvars_GetAsInt(CVARS_ENGINE_INTERNAL_RENDER_WIDTH);
}
int Utils_GetInternalRenderHeight()
{
	return Cvars_GetAsInt(CVARS_ENGINE_INTERNAL_RENDER_HEIGHT);
}
float Utils_GetCurrentHardwareRatio()
{
	Rectangle rect = Renderer_GetDrawableSize();
	return (float)(rect.Width) / (float)(rect.Height);
}
float Utils_GetCurrentInternalRatio()
{
	return (float)(Cvars_GetAsInt(CVARS_ENGINE_INTERNAL_RENDER_WIDTH)) / (float)(Cvars_GetAsInt(CVARS_ENGINE_INTERNAL_RENDER_HEIGHT));
}
IStringArray* Utils_SplitString(const char* str, size_t maxlen, char delim)
{
	IStringArray* sa = IStringArray_Create();

	size_t len = Utils_strnlen(str, maxlen);
	int counter = 0;
	for (int i = 0; i < (len + 1); i += 1) //Add +1 to len because...
	{
		if ((str[i] == delim) || (i == len)) //We need to make sure we get the stuff at the end...
		{
			_mLargeCharBuffer[counter] = '\0';
			IStringArray_Add(sa, _mLargeCharBuffer);
			Utils_memset(_mLargeCharBuffer, 0, FIXED_CHAR_260_LENGTH);
			counter = 0;
		}
		else
		{
			_mLargeCharBuffer[counter] = str[i];
			counter += 1;
		}
	}

	return sa;
}
