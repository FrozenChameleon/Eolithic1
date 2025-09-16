/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "FixedChar260.h"
#include "../math/Rectangle.h"
#include "IStringArray.h"

typedef struct SharedFixedChar260
{
	FixedChar260 mBuffer;
	bool mIsInUse;
} SharedFixedChar260;

#define UTILS_SHARED_STRING_BUFFER_LENGTH FIXED_CHAR_260_LENGTH

SharedFixedChar260* Utils_CreateSharedFixedChar260();
void Utils_DisposeSharedFixedChar260(SharedFixedChar260* sfc);
int32_t Utils_GetAmountOfSharedFixedChar260InUse();
void Utils_FreeAllSharedFixedChar260();
uint64_t Utils_GetMallocRefs();
uint64_t Utils_GetStringRefs();
int32_t Utils_memcmp(const void* s1, const void* s2, size_t len);
void Utils_memcpy(void* _Dst, const void* _Src, size_t _Size);
void Utils_memset(void* _Dst, int _Val, size_t _Size);
void* Utils_malloc(size_t size);
void Utils_free(void* mem);
size_t Utils_strlen(const char* str);
size_t Utils_strnlen(const char* str, size_t maxlen);
size_t Utils_strlcpy(char* dst, const char* src, size_t maxlen);
size_t Utils_strlcat(char* dst, const char* src, size_t maxlen);
float Utils_ParseFloat(const char* str);
int32_t Utils_ParseInt(const char* str);
bool Utils_StringEqualTo(const char* str1, const char* str2);
int32_t Utils_IntToString(int32_t value, char* buffer, size_t maxlen);
int32_t Utils_FloatToString(float value, char* buffer, size_t maxlen);
int32_t Utils_DoubleToString(double value, char* buffer, size_t maxlen);
char* Utils_CreateStringBuffer(size_t length);
char* Utils_CreateStringCopy(const char* str);
void Utils_FreeString(char* str);
void Utils_ResetArrayAsBool(bool* values, size_t len, bool valueToSet);
void Utils_ResetArrayAsInt32(int32_t* values, size_t len, int32_t valueToSet);
void Utils_ResetArrayAsSingle(float* values, size_t len, float valueToSet);
void Utils_ToggleFullscreenButton();
int32_t Utils_StringIndexOf(char findThis, const char* strInThis, size_t maxlen, bool findLastIndex);
double Utils_GetNormalStepLength();
double Utils_GetInterpolated(double delta, float current, float last);
Rectangle Utils_GetInternalRectangle();
Rectangle Utils_GetInternalRenderRectangle();
int Utils_GetInternalWidth();
int Utils_GetInternalHeight();
int Utils_GetInternalRenderWidth();
int Utils_GetInternalRenderHeight();
float Utils_GetCurrentHardwareRatio();
float Utils_GetCurrentInternalRatio();
IStringArray* Utils_SplitString(const char* str, size_t maxlen, char delim);