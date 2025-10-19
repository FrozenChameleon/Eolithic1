#pragma once

#include "stdint.h"
#include "stdbool.h"

typedef struct MString
{
	char* str;
	int32_t len;
	int32_t capacity;
} MString;

MString* MString_CreateFromSubString(const char* str, int32_t startIndex, int32_t length);
MString* MString_Create(const char* str);
MString* MString_CreateEmpty(int32_t size);
MString* MString_AddAssignChar(MString* thisWillBeDisposed, char c);
void MString_Dispose(MString* cstr);
uint64_t MString_GetRefs();