/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Utils.h"

#include "stdlib.h"
#include "float.h"
#include "../../third_party/stb_ds.h"
#include "SDL3/SDL.h"
#include "../math/Math.h"
#include "Cvars.h"
#include "../render/Renderer.h"
#include "Logger.h"
#include "../input/Input.h"
#include "../service/Service.h"
#include "../input/ControllerState.h"
#include "../input/ControllerStates.h"
#include "../globals/Globals.h"

static uint64_t _mStringRefs;
static uint64_t _mMallocRefs;
static int64_t _mSaveFrames;

#define LARGE_CHAR_BUFFER_LEN 8192
static char _mLargeCharBuffer[LARGE_CHAR_BUFFER_LEN];

struct { int32_t key; void** value; }*hm_allocation_arenas;

static void ResetLargeCharBuffer()
{
	Utils_memset(_mLargeCharBuffer, 0, LARGE_CHAR_BUFFER_LEN);
}

bool Utils_IsCurrentLanguageEnglish()
{
	return true;
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
void Utils_memset(void* _Dst, int32_t _Val, size_t _Size)
{
	SDL_memset(_Dst, _Val, _Size);
}
static void AddToAllocationArenas(int32_t allocationArena, void* memoryAllocation)
{
	if (allocationArena == UTILS_ALLOCATION_ARENA_INVALID)
	{
		Logger_LogWarning("Attempted to allocate to invalid allocation arena!");
		return;
	}

	int64_t index = hmgeti(hm_allocation_arenas, allocationArena);
	if (index == -1)
	{
		hmput(hm_allocation_arenas, allocationArena, NULL);
	}

	index = hmgeti(hm_allocation_arenas, allocationArena);
	if (index == -1)
	{
		Logger_LogWarning("Attempted to allocate to get allocation arena!");
		return;
	}

	arrput(hm_allocation_arenas[index].value, memoryAllocation);
}
void* Utils_mallocArena(size_t size, int32_t allocationArena)
{
	void* mallocToReturn = Utils_malloc(size);

	AddToAllocationArenas(allocationArena, mallocToReturn);

	return mallocToReturn;
}
void* Utils_callocArena(size_t nmemb, size_t size, int32_t allocationArena)
{
	void* callocToReturn = Utils_calloc(nmemb, size);

	AddToAllocationArenas(allocationArena, callocToReturn);

	return callocToReturn;
}
static void FreeArenaHelper(int32_t allocationArena)
{
	int64_t index = hmgeti(hm_allocation_arenas, allocationArena);
	if (index == -1)
	{
		return;
	}

	int64_t len = arrlen(hm_allocation_arenas[index].value);
	if (len == 0)
	{
		return;
	}

	for (int i = 0; i < len; i += 1)
	{
		Utils_free(hm_allocation_arenas[index].value[i]);
	}
	arrsetlen(hm_allocation_arenas[index].value, 0);
}
void Utils_FreeJustThisFrameAllocationArena()
{
	FreeArenaHelper(UTILS_ALLOCATION_ARENA_JUST_THIS_FRAME);
}
void Utils_FreeJustThisLevelAllocationArena()
{
	FreeArenaHelper(UTILS_ALLOCATION_ARENA_JUST_THIS_LEVEL);
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
char* Utils_IntToStringStaticBuffer(int32_t value)
{
	ResetLargeCharBuffer();
	SDL_snprintf(_mLargeCharBuffer, LARGE_CHAR_BUFFER_LEN, "%d", value);
	return _mLargeCharBuffer;
}
char* Utils_FloatToStringStaticBuffer(float value)
{
	ResetLargeCharBuffer();
	SDL_snprintf(_mLargeCharBuffer, LARGE_CHAR_BUFFER_LEN, "%.9g", value); //9 FROM FROM FLT_DECIMAL_DIG in float.h
	return _mLargeCharBuffer;
}
char* Utils_DoubleToStringStaticBuffer(double value)
{
	ResetLargeCharBuffer();
	SDL_snprintf(_mLargeCharBuffer, LARGE_CHAR_BUFFER_LEN, "%.17g", value); //17 FROM DBL_DECIMAL_DIG in float.h
	return _mLargeCharBuffer;
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
		values[i] = valueToSet;
	}
}
void Utils_ResetArrayAsInt(int32_t* values, size_t len, int32_t valueToSet)
{
	for (int i = 0; i < len; i += 1)
	{
		values[i] = valueToSet;
	}
}
void Utils_ResetArrayAsFloat(float* values, size_t len, float valueToSet)
{
	for (int i = 0; i < len; i += 1)
	{
		values[i] = valueToSet;
	}
}
void Utils_ToggleFullscreenButton()
{
	//TODO
}
int32_t Utils_StringIndexOf(char findThis, const char* strInThis, size_t maxlen, bool findLastIndex)
{
	int32_t len = (int32_t)Utils_strnlen(strInThis, maxlen);
	int32_t loc = -1;
	for (int i = 0; i < len; i += 1)
	{
		if (strInThis[i] == findThis)
		{
			if (!findLastIndex)
			{
				return i;
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
	ResetLargeCharBuffer();

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
int Utils_Get1DArrayPosFor2DArray(int i, int32_t j, int32_t width)
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
bool Utils_ArrContainsInt(int* arr_values, int32_t containsThis)
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
	int32_t len = (int32_t)Utils_strlen(str);
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
	int32_t strLen = (int32_t)Utils_strlen(str);
	int32_t endsWithThisLen = (int32_t)Utils_strlen(endsWithThis);

	if (strLen < endsWithThisLen)
	{
		return false;
	}

	int32_t targetCounter = 0;
	for (int32_t i = (strLen - endsWithThisLen); i < strLen; i += 1)
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
bool Utils_StringStartsWith(const char* str, const char* startsWithThis)
{
	int32_t strLen = (int32_t)Utils_strlen(str);
	int32_t startsWithThisLen = (int32_t)Utils_strlen(startsWithThis);

	if (strLen < startsWithThisLen)
	{
		return false;
	}

	for (int32_t i = 0; i < startsWithThisLen; i += 1)
	{
		if (str[i] != startsWithThis[i])
		{
			return false;
		}
	}

	return true;
}
int32_t Utils_ParseDirection(const char* s)
{
	int32_t value;
	if (Utils_StringEqualTo(s, "0"))
	{
		value = 0;
	}
	else if (Utils_StringEqualTo(s, "1"))
	{
		value = 1;
	}
	else
	{
		value = -1;
	}
	return value;
}
const char* Utils_GetGlyphType()
{
	int controllerType = Cvars_GetAsInt(CVARS_USER_CONTROLLER_TYPE);
	if (Service_PlatformForcesSpecificGlyph())
	{
		const char* strForcedGlyph = ControllerState_PlatformGetForcedSpecificGlyphAsString();
		if (!Utils_StringEqualTo(strForcedGlyph, EE_STR_EMPTY))
		{
			return strForcedGlyph;
		}
		else
		{
			controllerType = Service_PlatformGetForcedSpecificGlyph();
		}
	}

	switch (controllerType)
	{
	case INPUT_CONTROLLER_GLYPH_X:
		return "XONE";
	case INPUT_CONTROLLER_GLYPH_P4:
		return "PS4";
	case INPUT_CONTROLLER_GLYPH_P5:
		return "PS5";
	case INPUT_CONTROLLER_GLYPH_N:
		return "SWITCH";
	}
	return "?";
}
float Utils_GetSubseconds(int32_t val)
{
	return (val % 60) * (100.0f / 60.0f);
}
int Utils_GetMinutes(int32_t val)
{
	int minutes = 0;

	int seconds = val / 60;
	if (seconds >= 60)
	{
		minutes = seconds / 60;
		if (minutes >= 60)
		{
			minutes = minutes % 60;
		}
	}

	return minutes;
}
int Utils_GetHours(int32_t val)
{
	int hours = 0;

	int seconds = val / 60;
	if (seconds >= 60)
	{
		int minutes = seconds / 60;
		if (minutes >= 60)
		{
			hours = minutes / 60;
		}
	}

	return hours;
}
int Utils_GetSeconds(int32_t val)
{
	int seconds = val / 60;

	if (seconds >= 60)
	{
		seconds = seconds % 60;
	}

	return seconds;
}
bool Utils_CheckSave(bool update)
{
	if (_mSaveFrames > 0)
	{
		if (update)
		{
			_mSaveFrames -= 1;
		}
		return true;
	}
	return false;
}
void Utils_JustSaved()
{
	if (Globals_IsSavingUserDataDisabled())
	{
		return;
	}

	_mSaveFrames = Cvars_GetAsInt(CVARS_ENGINE_SAVE_ICON_TIME);
}
static BuilderHelper(char* buffer, int index, int32_t val)
{
	if (val < 10)
	{
		buffer[index] = '0';
		buffer[index + 1] = Utils_GetCharFromNumber(val);
	}
	else
	{
		buffer[index] = Utils_GetCharFromNumber(val / 10);
		buffer[index + 1] = Utils_GetCharFromNumber(val % 10);
	}
}
void Utils_UpdateFramesToTimeDisplay(char* buffer, int32_t val)
{
	int subseconds = (int)Utils_GetSubseconds(val);
	int seconds = Utils_GetSeconds(val);
	int minutes = Utils_GetMinutes(val);
	int hours = Utils_GetHours(val);
	if (hours >= 24)
	{
		hours = 23;
		minutes = 59;
		seconds = 59;
		subseconds = 99;
	}

	BuilderHelper(buffer, 0, hours);
	buffer[2] = ':';
	BuilderHelper(buffer, 3, minutes);
	buffer[5] = ':';
	BuilderHelper(buffer, 6, seconds);
	buffer[8] = ':';
	BuilderHelper(buffer, 9, subseconds);
}
