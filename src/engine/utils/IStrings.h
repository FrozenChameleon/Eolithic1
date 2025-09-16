#pragma once

#include "../utils/Macros.h"
#include "stdint.h"

typedef struct IStrings IStrings;

IStrings* IStrings_Create();
void IStrings_Dispose(IStrings* is);
IString IStrings_Get(IStrings* is, const char* str);
size_t IStrings_Length(IStrings* is);
IString IStrings_GetByIndex(IStrings* is, int32_t index);
uint64_t IStrings_GetRefs();
IString IStrings_GlobalGet(const char* str);
void IStrings_GlobalDispose();
size_t IStrings_GlobalLength();