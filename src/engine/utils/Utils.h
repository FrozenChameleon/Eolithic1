/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "../math/Rectangle.h"

typedef struct IStringArray IStringArray;

uint64_t Utils_GetMallocRefs();
uint64_t Utils_GetStringRefs();
int32_t Utils_memcmp(const void* s1, const void* s2, size_t len);
void Utils_memcpy(void* _Dst, const void* _Src, size_t _Size);
void Utils_memset(void* _Dst, int _Val, size_t _Size);
void* Utils_malloc(size_t size);
void* Utils_calloc(size_t nmemb, size_t size);
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
char Utils_GetCharFromNumber(int val);
int Utils_Get1DArrayPosFor2DArray(int i, int j, int width);
bool Utils_CharIsDigit(char c);
bool Utils_ArrContainsInt(int* arr_values, int containsThis);
bool Utils_StringContains(const char* str, const char* containsThis);