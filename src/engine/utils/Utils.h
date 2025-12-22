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
typedef struct MString MString;

#define UTILS_ENGLISH_LANGUAGE_CODE "en"
#define UTILS_FRENCH_LANGUAGE_CODE "fr"
#define UTILS_ITALIAN_LANGUAGE_CODE "it"
#define UTILS_GERMAN_LANGUAGE_CODE "de"
#define UTILS_SPANISH_LANGUAGE_CODE "es"

#define UTILS_EXTENSION_BIN ".bin"
#define UTILS_EXTENSION_INI ".ini"

enum
{
	UTILS_ALLOCATION_ARENA_INVALID = 0,
	UTILS_ALLOCATION_ARENA_JUST_THIS_FRAME = 1,
	UTILS_ALLOCATION_ARENA_JUST_THIS_LEVEL = 2,
	UTILS_ALLOCATION_ARENA_MOVIE_PLAYER = 3
};

const char* Utils_GetCurrentUserLanguageCode();
bool Utils_IsCurrentLanguageEnglish();
uint64_t Utils_GetMallocRefs();
uint64_t Utils_GetStringRefs();
int32_t Utils_memcmp(const void* s1, const void* s2, size_t len);
void Utils_memcpy(void* _Dst, const void* _Src, size_t _Size);
void Utils_memset(void* _Dst, int32_t _Val, size_t _Size);
void* Utils_mallocArena(size_t size, int32_t allocationArena);
void* Utils_callocArena(size_t nmemb, size_t size, int32_t allocationArena);
void Utils_FreeArena(int32_t allocationArena);
void* Utils_malloc(size_t size);
void* Utils_calloc(size_t nmemb, size_t size);
void Utils_free(void* mem);
size_t Utils_strlen(const char* str);
size_t Utils_strnlen(const char* str, size_t maxlen);
size_t Utils_strlcpy(char* dst, const char* src, size_t maxlen);
size_t Utils_strlcat(char* dst, const char* src, size_t maxlen);
bool Utils_ParseBooleanFromChar(const char* str);
float Utils_ParseFloat(const char* str);
int32_t Utils_ParseInt(const char* str);
bool Utils_ParseBoolean(const char* str);
bool Utils_StringEqualTo(const char* str1, const char* str2);
int32_t Utils_IntToString(int32_t value, char* buffer, size_t maxlen);
int32_t Utils_FloatToString(float value, char* buffer, size_t maxlen);
int32_t Utils_DoubleToString(double value, char* buffer, size_t maxlen);
char* Utils_IntToStringStaticBuffer(int32_t value);
char* Utils_FloatToStringStaticBuffer(float value);
char* Utils_DoubleToStringStaticBuffer(double value);
char* Utils_CreateStringBuffer(size_t length);
char* Utils_CreateStringCopy(const char* str);
void Utils_FreeString(char* str);
void Utils_ResetArrayAsBool(bool* values, size_t len, bool valueToSet);
void Utils_ResetArrayAsInt(int32_t* values, size_t len, int32_t valueToSet);
void Utils_ResetArrayAsFloat(float* values, size_t len, float valueToSet);
void Utils_ToggleFullscreenButton();
int32_t Utils_StringIndexOf(char findThis, const char* strInThis, size_t maxlen, bool findLastIndex);
int32_t Utils_StringFirstIndexOf(char findThis, const char* strInThis, size_t maxlen);
int32_t Utils_StringLastIndexOf(char findThis, const char* strInThis, size_t maxlen);
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
void Utils_SplitString(const char* str, size_t maxlen, char delim, IStringArray* addToThis);
char Utils_GetCharFromNumber(int val);
int Utils_Get1DArrayPosFor2DArray(int i, int32_t j, int32_t width);
bool Utils_CharIsDigit(char c);
bool Utils_ArrContainsInt(int* arr_values, int32_t containsThis);
bool Utils_StringContains(const char* str, const char* containsThis);
bool Utils_StringEndsWith(const char* str, const char* endsWithThis);
bool Utils_StringStartsWith(const char* str, const char* startsWithThis);
int32_t Utils_ParseDirection(const char* s);
const char* Utils_GetGlyphType();
void Utils_UpdateFramesToTimeDisplay(char* buffer, int32_t val);
float Utils_GetSubseconds(int32_t val);
int Utils_GetMinutes(int32_t val);
int Utils_GetHours(int32_t val);
int Utils_GetSeconds(int32_t val);
bool Utils_CheckSave(bool update);
void Utils_JustSaved();
int32_t Utils_GetAmountOfDigits(int32_t n);
void Utils_GetSplitCSV(const char* str, IStringArray* addToHere);
bool Utils_IsStringUnderWidth(const char* str, const char* font, int32_t start, int32_t currentIndex, int32_t width);
int32_t Utils_GetSpotForNewLine(const char* str, const char* font, int32_t width);
void Utils_GetStringWithNewLines(const char* str, const char* font, int32_t width, MString** assignToThis);