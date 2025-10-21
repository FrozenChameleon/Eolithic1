#pragma once

#include "stdint.h"
#include "stdbool.h"

typedef struct MString
{
	char* text;
	int32_t len;
	int32_t capacity;
} MString;

MString* MString_CreateFromSubString(const char* str, int32_t startIndex, int32_t length);
MString* MString_Create(const char* str);
MString* MString_CreateEmpty(int32_t size);
void MString_AddAssignChar(MString** str, char addThisChar);
void MString_AddAssignString(MString** str, const char* addThisStr);
MString* MString_Truncate(MString* str, int newLength);
void MString_Dispose(MString* str);
uint64_t MString_GetRefs();