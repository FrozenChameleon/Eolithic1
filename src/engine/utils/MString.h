#pragma once

#include "stdint.h"
#include "stdbool.h"

typedef struct MString MString;
typedef struct BufferReader BufferReader;

char* MString_GetText(const MString* str);
int32_t MString_GetLength(const MString* str);
int32_t MString_GetCapacity(const MString* str);
bool MString_EqualToString(const MString* str, const char* otherStr);
bool MString_EqualTo(const MString* str, const MString* otherStr);
void MString_Assign(MString** str, const char* toThis);
void MString_AssignMString(MString** str, MString* toThis);
void MString_Clear(MString** str);
void MString_AssignEmpty(MString** str, int32_t size);
void MString_AssignSubString(MString** str, const char* fromThis, int32_t startIndex, int32_t length);
void MString_AddAssignInt(MString** str, int32_t addThisInt);
void MString_AddAssignFloat(MString** str, float addThisSingle);
void MString_AddAssignDouble(MString** str, double addThisDouble);
void MString_AddAssignChar(MString** str, char addThisChar);
void MString_AddAssignMString(MString** str, const MString* addThisStr);
void MString_AddAssignString(MString** str, const char* addThisStr);
void MString_Truncate(MString** str, int newLength);
void MString_Dispose(MString** str);
MString* MString_Read(BufferReader* br);
uint64_t MString_GetRefs();