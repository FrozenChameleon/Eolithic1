#include "MString.h"

#include "Utils.h"
#include "Logger.h"
#include "Macros.h"

static uint64_t _mRefs;

static char _mTempBuffer[EE_SAFE_BUFFER_LENGTH_FOR_DOUBLE];

static void ClearTempBuffer()
{
	Utils_memset(_mTempBuffer, 0, EE_SAFE_BUFFER_LENGTH_FOR_DOUBLE * sizeof(char));
}
static void FixNullString(MString** str)
{
	if (*str != NULL)
	{
		return;
	}

	*str = MString_Create("");
}

MString* MString_CreateFromSubString(const char* str, int32_t startIndex, int32_t length)
{
	MString* mstring = MString_Create(str);
	Utils_memset(mstring->text, 0, mstring->capacity);
	Utils_strlcpy(mstring->text, str + startIndex, length + 1);
	mstring->len = length;
	return mstring;
}
MString* MString_Create(const char* fromThisStr)
{
	int32_t strLen = Utils_strlen(fromThisStr);
	MString* mstring = MString_CreateEmpty(strLen + 1);
	Utils_strlcpy(mstring->text, fromThisStr, strLen + 1);
	mstring->len = strLen;
	mstring->capacity = strLen + 1;
	return mstring;
}
MString* MString_CreateEmpty(int32_t size)
{
	_mRefs += 1;

	MString* mstring = Utils_calloc(1, sizeof(MString));
	mstring->text = Utils_calloc(1, size);
	mstring->len = 0;
	mstring->capacity = size;
	return mstring;
}
void MString_Assign(MString** str, const char* toThis)
{
	FixNullString(str);

	MString* oldStr = *str;
	MString* newStr = MString_Create(toThis);
	MString_Dispose(oldStr);
	*str = newStr;
}
void MString_AddAssignInt(MString** str, int32_t addThisInt)
{
	ClearTempBuffer();
	Utils_IntToString(addThisInt, _mTempBuffer, EE_SAFE_BUFFER_LENGTH_FOR_DOUBLE);
	MString_AddAssignString(str, _mTempBuffer);
}
void MString_AddAssignSingle(MString** str, float addThisSingle)
{
	ClearTempBuffer();
	Utils_FloatToString(addThisSingle, _mTempBuffer, EE_SAFE_BUFFER_LENGTH_FOR_DOUBLE);
	MString_AddAssignString(str, _mTempBuffer);
}
void MString_AddAssignDouble(MString** str, double addThisDouble)
{
	ClearTempBuffer();
	Utils_DoubleToString(addThisDouble, _mTempBuffer, EE_SAFE_BUFFER_LENGTH_FOR_DOUBLE);
	MString_AddAssignString(str, _mTempBuffer);
}
void MString_AddAssignChar(MString** str, char addThisChar)
{
	FixNullString(str);

	MString* oldStr = *str;
	size_t newLen = oldStr->len + 1;
	size_t newCapacity = newLen + 1;
	MString* newStr = MString_CreateEmpty(newCapacity);
	Utils_strlcpy(newStr->text, oldStr->text, oldStr->len + 1);
	newStr->text[newLen - 1] = addThisChar;
	newStr->text[newLen] = '\0';
	newStr->len = (int32_t)newLen;
	MString_Dispose(oldStr);
	*str = newStr;
}
void MString_AddAssignString(MString** str, const char* addThisStr)
{
	FixNullString(str);

	MString* oldStr = *str;
	size_t addThisStrLen = Utils_strlen(addThisStr);
	size_t newLen = oldStr->len + addThisStrLen;
	size_t newCapacity = newLen + 1;
	MString* newStr = MString_CreateEmpty((int32_t)newCapacity);
	Utils_strlcpy(newStr->text, oldStr->text, oldStr->len + 1);
	Utils_strlcpy(newStr->text + oldStr->len, addThisStr, addThisStrLen + 1);
	newStr->len = (int32_t)newLen;
	newStr->text[newLen] = '\0';
	MString_Dispose(oldStr);
	*str = newStr;
}
void MString_Truncate(MString** str, int newLength)
{
	FixNullString(str);

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
void MString_Dispose(MString* str)
{
	if (str == NULL)
	{
		return;
	}

	_mRefs -= 1;

	Utils_free(str->text);
	Utils_free(str);
}
bool MString_EqualToChar(MString* str, const char* otherStr)
{
	return Utils_StringEqualTo(str->text, otherStr);
}
bool MString_EqualTo(MString* str, MString* otherStr)
{
	return Utils_StringEqualTo(str->text, otherStr->text);
}
uint64_t MString_GetRefs()
{
	return _mRefs;
}
