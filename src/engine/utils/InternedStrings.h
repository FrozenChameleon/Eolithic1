#pragma once

#include "stdint.h"

typedef struct InternedStrings InternedStrings;

InternedStrings* InternedStrings_Create();
void InternedStrings_Dispose(InternedStrings* is);
void InternedStrings_Add(InternedStrings* is, const char* str);
const char* InternedStrings_Get(InternedStrings* is, const char* str);
int32_t InternedStrings_Length(InternedStrings* is);
const char* InternedStrings_GetByIndex(InternedStrings* is, int32_t index);
uint64_t InternedStrings_GetRefs();