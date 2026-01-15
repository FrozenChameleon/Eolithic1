#pragma once

#include "stdint.h"
#include "stdbool.h"

typedef struct MString MString;
typedef struct BufferReader BufferReader;

char* MString_GetText(const MString* str);
char MString_GetLastChar(const MString* str);
int32_t MString_GetLength(const MString* str);
int32_t MString_GetCapacity(const MString* str);
bool MString_EqualToString(const MString* str, const char* otherStr);
bool MString_EqualTo(const MString* str, const MString* otherStr);
void MString_Assign(MString** str, const char* toThis);
void MString_AssignMString(MString** str, MString* toThis);
void MString_Clear(MString** str);
void MString_AssignEmpty(MString** str, int32_t capacity);
void MString_AssignSubString(MString** str, const char* fromThis, int32_t startIndex, int32_t length);
void MString_AddAssignInt(MString** str, int32_t addThisInt);
void MString_AddAssignUInt64(MString** str, uint64_t addThisUInt64);
void MString_AddAssignFloat(MString** str, float addThisSingle);
void MString_AddAssignDouble(MString** str, double addThisDouble);
void MString_AddAssignChar(MString** str, char addThisChar);
void MString_AddAssignMString(MString** str, const MString* addThisStr);
void MString_AddAssignString(MString** str, const char* addThisStr);
void MString_Truncate(MString** str, int32_t newLength);
void MString_Dispose(MString** str);
void MString_Read(MString** str, BufferReader* br);
uint64_t MString_GetRefs();
void MString_Combine2(MString** str, const char* str1, const char* str2);
void MString_Combine3(MString** str, const char* str1, const char* str2, const char* str3);
void MString_Combine4(MString** str, const char* str1, const char* str2, const char* str3, const char* str4);
void MString_Combine5(MString** str, const char* str1, const char* str2, const char* str3, const char* str4, const char* str5);
void MString_Combine6(MString** str, const char* str1, const char* str2, const char* str3, const char* str4, const char* str5, const char* str6);
void MString_Combine7(MString** str, const char* str1, const char* str2, const char* str3, const char* str4, const char* str5, const char* str6, const char* str7);
void MString_Combine8(MString** str, const char* str1, const char* str2, const char* str3, const char* str4, const char* str5, const char* str6, const char* str7, const char* str8);
void MString_DebugPrintLeakInfo();