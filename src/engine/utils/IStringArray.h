#pragma once

#include "stdint.h"
#include "Macros.h"

typedef struct IStringArray IStringArray;

IStringArray* IStringArray_Create();
void IStringArray_Dispose(IStringArray* sa);
void IStringArray_Add(IStringArray* sa, const char* str);
int64_t IStringArray_Length(IStringArray* sa);
IString IStringArray_Get(IStringArray* sa, int32_t index);
uint64_t IStringArray_GetRefs();