#pragma once

#include "stdint.h"
#include "stdbool.h"

typedef struct MString MString;

MString* MString_CreateFromSubString(const char* str, int32_t startIndex, int32_t length);
MString* MString_Create(const char* str);
MString* MString_CreateEmpty(int32_t size);
char* MString_Text(MString* str);
int32_t MString_Length(MString* str);
int32_t MString_Capacity(MString* str);
void MString_Assign(MString** str, const char* toThis);
void MString_AddAssignInt(MString** str, int32_t addThisInt);
void MString_AddAssignFloat(MString** str, float addThisSingle);
void MString_AddAssignDouble(MString** str, double addThisDouble);
void MString_AddAssignChar(MString** str, char addThisChar);
void MString_AddAssignString(MString** str, const char* addThisStr);
void MString_Truncate(MString** str, int newLength);
void MString_Dispose(MString* str);
bool MString_EqualToString(const MString* str, const char* otherStr);
bool MString_EqualTo(const MString* str, const MString* otherStr);
uint64_t MString_GetRefs();