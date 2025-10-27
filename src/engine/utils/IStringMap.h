#pragma once

#include "stdint.h"
#include "Macros.h"

typedef struct IStringMap IStringMap;

IStringMap* IStringMap_Create();
void IStringMap_Clear(IStringMap* sm);
void IStringMap_Dispose(IStringMap* sm);
void IStringMap_Add(IStringMap* sm, const char* key, const char* value);
IString IStringMap_Get(IStringMap* sm, const char* key);
bool IStringMap_Contains(IStringMap* sm, const char* key);
int64_t IStringMap_Length(IStringMap* sm);
IString IStringMap_GetByIndex(IStringMap* sm, int32_t index);
uint64_t IStringMap_GetRefs();