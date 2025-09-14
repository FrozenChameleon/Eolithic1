#pragma once

#include "stdint.h"

typedef struct StringArray StringArray;

StringArray* StringArray_Create();
void StringArray_Dispose(StringArray* sa);
void StringArray_Add(StringArray* sa, const char* str);
int32_t StringArray_Length(StringArray* sa);
const char* StringArray_Get(StringArray* sa, int32_t index);
uint64_t StringArray_GetRefs();