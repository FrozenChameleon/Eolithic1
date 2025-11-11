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

#define LARGE_CHAR_BUFFER_LEN 8192
static char _mLargeCharBuffer[LARGE_CHAR_BUFFER_LEN];

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
bool Utils_ParseBooleanFromChar(const char* str)
{
	if ((str[0] == 'T') || (str[0] == 't'))
	{
		return true;
	}
	else
	{
		return false;
	}
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
	else if ((str1 == NULL) || (str2 == NULL))
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
void Utils_ResetArrayAsFloat(float* values, size_t len, float valueToSet)
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
			Utils_memset(_mLargeCharBuffer, 0, LARGE_CHAR_BUFFER_LEN);
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

char Utils_GetCharFromNumber(int val)
{
	if (val == -1)
	{
		return ' ';
	}

	switch (val)
	{
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	}
	return '0';
}
int Utils_Get1DArrayPosFor2DArray(int i, int j, int width)
{
	return i + (j * width);
}
bool Utils_CharIsDigit(char c)
{
	switch (c)
	{
	case '1':
		return true;
	case '2':
		return true;
	case '3':
		return true;
	case '4':
		return true;
	case '5':
		return true;
	case '6':
		return true;
	case '7':
		return true;
	case '8':
		return true;
	case '9':
		return true;
	case '0':
		return true;
	}
	return false;
}
bool Utils_ArrContainsInt(int* arr_values, int containsThis)
{
	int64_t len = arrlen(arr_values);
	for (int i = 0; i < len; i += 1)
	{
		if (arr_values[i] == containsThis)
		{
			return true;
		}
	}
	return false;
}
bool Utils_StringContains(const char* str, const char* containsThis)
{
	int len = Utils_strlen(str);
	char* result = SDL_strnstr(str, containsThis, len);
	if (result == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool Utils_StringEndsWith(const char* str, const char* endsWithThis)
{
	size_t strLen = Utils_strlen(str);
	size_t endsWithThisLen = Utils_strlen(endsWithThis);

	if (strLen < endsWithThisLen)
	{
		return false;
	}

	int targetCounter = 0;
	for (int i = (strLen - endsWithThisLen); i < strLen; i += 1)
	{
		if (str[i] != endsWithThis[targetCounter])
		{
			return false;
		}
		else
		{
			targetCounter += 1;
		}
	}

	return true;
}
