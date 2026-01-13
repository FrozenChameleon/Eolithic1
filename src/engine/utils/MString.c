#include "MString.h"

#include "Utils.h"
#include "Logger.h"
#include "Macros.h"
#include "../io/BufferReader.h"
#include "../../third_party/stb_ds.h"

//#define FIND_THE_LEAKS

typedef struct MString
{
	char* text;
	int32_t len;
	int32_t capacity;
} MString;

static uint64_t _mRefs;

static char _mTempBuffer[EE_SAFE_BUFFER_LEN_FOR_DOUBLE];

#ifdef FIND_THE_LEAKS
typedef struct LeakTest
{ 
	MString* key; 
	int value;
} LeakTest;

static LeakTest* _mLeakTest;
static bool _mHasLeakTestBegun;
#endif

static void ClearTempBuffer()
{
	Utils_memset(_mTempBuffer, 0, EE_SAFE_BUFFER_LEN_FOR_DOUBLE * sizeof(char));
}

static MString* MString_CreateEmpty(int32_t size)
{
	_mRefs += 1;
	MString* mstring = Utils_calloc(1, sizeof(MString));
#ifdef FIND_THE_LEAKS
	if (_mHasLeakTestBegun)
	{
		hmput(_mLeakTest, mstring, 0);
	}
#endif
	mstring->text = Utils_calloc(1, size);
	mstring->len = 0;
	mstring->capacity = size;
	return mstring;
}
static MString* MString_Create(const char* fromThisStr)
{
	int32_t strLen = (int32_t)Utils_strlen(fromThisStr);
	MString* mstring = MString_CreateEmpty(strLen + 1);
	Utils_strlcpy(mstring->text, fromThisStr, strLen + 1);
	mstring->len = strLen;
	mstring->capacity = strLen + 1;
	return mstring;
}
static bool CheckDoublePointerSafetyForComparison(MString** str)
{
	if (str == NULL)
	{
		Logger_LogWarning("MString double pointer is not safe...");
		return false;
	}

	if (*str == NULL)
	{
		return false;
	}

	return true;
}
static void CheckAndReplaceNullString(MString** str)
{
	if (str == NULL)
	{
		Logger_LogWarning("Handed NULL MString Double Pointer...");
		return;
	}

	if (*str != NULL)
	{
		return;
	}

	*str = MString_Create(EE_STR_EMPTY);
}

char* MString_GetText(const MString* str)
{
	if (str == NULL)
	{
		return EE_STR_NOT_SET;
	}

	return str->text;
}
char MString_GetLastChar(const MString* str)
{
	if ((str == NULL) || (str->len <= 0))
	{
		return '\0';
	}

	return str->text[str->len - 1];
}
int32_t MString_GetLength(const MString* str)
{
	if (str == NULL)
	{
		return 0;
	}

	return str->len;
}
int32_t MString_GetCapacity(const MString* str)
{
	if (str == NULL)
	{
		return 0;
	}

	return str->capacity;
}
bool MString_EqualToString(const MString* str, const char* otherStr)
{
	return Utils_StringEqualTo(MString_GetText(str), otherStr);
}
bool MString_EqualTo(const MString* str, const MString* otherStr)
{
	return Utils_StringEqualTo(MString_GetText(str), MString_GetText(otherStr));
}
void MString_Assign(MString** str, const char* toThis)
{
	CheckAndReplaceNullString(str);

	MString* oldStr = *str;
	MString* newStr = MString_Create(toThis);
	MString_Dispose(&oldStr);
	*str = newStr;
}
void MString_AssignMString(MString** str, MString* toThis)
{
	MString_Assign(str, MString_GetText(toThis));
}
void MString_Clear(MString** str)
{
	MString_Assign(str, EE_STR_EMPTY);
}
void MString_AssignEmpty(MString** str, int32_t size)
{
	CheckAndReplaceNullString(str);

	MString* oldStr = *str;
	MString* newStr = MString_CreateEmpty(size);
	MString_Dispose(&oldStr);
	*str = newStr;
}
void MString_AssignSubString(MString** str, const char* fromThis, int32_t startIndex, int32_t length)
{
	CheckAndReplaceNullString(str);

	MString* oldStr = *str;
	MString* newStr = MString_Create(fromThis);
	Utils_memset(newStr->text, 0, newStr->capacity);
	Utils_strlcpy(newStr->text, fromThis + startIndex, length + 1);
	newStr->len = length;
	MString_Dispose(&oldStr);
	*str = newStr;
}
void MString_AddAssignInt(MString** str, int32_t addThisInt)
{
	ClearTempBuffer();
	Utils_IntToString(addThisInt, _mTempBuffer, EE_SAFE_BUFFER_LEN_FOR_DOUBLE);
	MString_AddAssignString(str, _mTempBuffer);
}
void MString_AddAssignUInt64(MString** str, uint64_t addThisUInt64)
{
	ClearTempBuffer();
	Utils_UInt64ToString(addThisUInt64, _mTempBuffer, EE_SAFE_BUFFER_LEN_FOR_DOUBLE);
	MString_AddAssignString(str, _mTempBuffer);
}
void MString_AddAssignFloat(MString** str, float addThisSingle)
{
	ClearTempBuffer();
	Utils_FloatToString(addThisSingle, _mTempBuffer, EE_SAFE_BUFFER_LEN_FOR_DOUBLE);
	MString_AddAssignString(str, _mTempBuffer);
}
void MString_AddAssignDouble(MString** str, double addThisDouble)
{
	ClearTempBuffer();
	Utils_DoubleToString(addThisDouble, _mTempBuffer, EE_SAFE_BUFFER_LEN_FOR_DOUBLE);
	MString_AddAssignString(str, _mTempBuffer);
}
void MString_AddAssignChar(MString** str, char addThisChar)
{
	CheckAndReplaceNullString(str);

	MString* oldStr = *str;
	size_t newLen = oldStr->len + 1;
	size_t newCapacity = newLen + 1;
	MString* newStr = MString_CreateEmpty((int32_t)newCapacity);
	Utils_strlcpy(newStr->text, oldStr->text, oldStr->len + 1);
	newStr->text[newLen - 1] = addThisChar;
	newStr->text[newLen] = '\0';
	newStr->len = (int32_t)newLen;
	MString_Dispose(&oldStr);
	*str = newStr;
}
void MString_AddAssignMString(MString** str, const MString* addThisStr)
{
	MString_AddAssignString(str, MString_GetText(addThisStr));
}
void MString_AddAssignString(MString** str, const char* addThisStr)
{
	CheckAndReplaceNullString(str);

	MString* oldStr = *str;
	size_t addThisStrLen = Utils_strlen(addThisStr);
	size_t newLen = oldStr->len + addThisStrLen;
	size_t newCapacity = newLen + 1;
	MString* newStr = MString_CreateEmpty((int32_t)newCapacity);
	Utils_strlcpy(newStr->text, oldStr->text, oldStr->len + 1);
	Utils_strlcpy(newStr->text + oldStr->len, addThisStr, addThisStrLen + 1);
	newStr->len = (int32_t)newLen;
	newStr->text[newLen] = '\0';
	MString_Dispose(&oldStr);
	*str = newStr;
}
void MString_Truncate(MString** str, int32_t newLength)
{
	CheckAndReplaceNullString(str);

	MString* actualStr = *str;

	if (newLength >= actualStr->len)
	{
		return;
	}

	for (int i = 0; i < actualStr->capacity; i += 1)
	{
		if (i >= newLength)
		{
			actualStr->text[i] = '\0';
		}
	}
	actualStr->len = newLength;
}
void MString_Dispose(MString** str)
{
	if (!CheckDoublePointerSafetyForComparison(str))
	{
		return;
	}

#ifdef FIND_THE_LEAKS
	if (_mHasLeakTestBegun)
	{
		hmdel(_mLeakTest, *str);
	}
#endif

	_mRefs -= 1;

	Utils_free((*str)->text);
	Utils_free((*str));
	*str = NULL;
}
void MString_Read(MString** str, BufferReader* br)
{
	uint8_t newStringLength = BufferReader_ReadJustTheStringLength(br);
	int32_t newStrCapacity = newStringLength + 1;
	MString_AssignEmpty(str, newStrCapacity);
	(*str)->len = newStringLength;
	BufferReader_ReadJustTheStringData(br, newStringLength, MString_GetText(*str), newStrCapacity);
}
uint64_t MString_GetRefs()
{
	return _mRefs;
}
void MString_Combine2(MString** str, const char* str1, const char* str2)
{
	MString_Assign(str, str1);
	MString_AddAssignString(str, str2);
}
void MString_Combine3(MString** str, const char* str1, const char* str2, const char* str3)
{
	MString_Combine2(str, str1, str2);
	MString_AddAssignString(str, str3);
}
void MString_Combine4(MString** str, const char* str1, const char* str2, const char* str3, const char* str4)
{
	MString_Combine3(str, str1, str2, str3);
	MString_AddAssignString(str, str4);
}
void MString_Combine5(MString** str, const char* str1, const char* str2, const char* str3, const char* str4, const char* str5)
{
	MString_Combine4(str, str1, str2, str3, str4);
	MString_AddAssignString(str, str5);
}
void MString_Combine6(MString** str, const char* str1, const char* str2, const char* str3, const char* str4, const char* str5, const char* str6)
{
	MString_Combine5(str, str1, str2, str3, str4, str5);
	MString_AddAssignString(str, str6);
}
void MString_Combine7(MString** str, const char* str1, const char* str2, const char* str3, const char* str4, const char* str5, const char* str6, const char* str7)
{
	MString_Combine6(str, str1, str2, str3, str4, str5, str6);
	MString_AddAssignString(str, str7);
}
void MString_Combine8(MString** str, const char* str1, const char* str2, const char* str3, const char* str4, const char* str5, const char* str6, const char* str7, const char* str8)
{
	MString_Combine7(str, str1, str2, str3, str4, str5, str6, str7);
	MString_AddAssignString(str, str8);
}
void MString_DebugPrintLeakInfo()
{
#ifdef FIND_THE_LEAKS
	_mHasLeakTestBegun = true;
	int64_t len = hmlen(_mLeakTest);
	for (int i = 0; i < len; i += 1)
	{
		Logger_printf(MString_GetText(_mLeakTest[i].key));
		Logger_printf("\n");
	}
#endif
}
