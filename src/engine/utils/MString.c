#include "MString.h"

#include "Utils.h"
#include "Logger.h"

static uint64_t _mRefs;

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
void MString_AddAssignChar(MString** str, char addThisChar)
{
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
MString* MString_Truncate(MString* str, int newLength)
{
	if (newLength >= str->len)
	{
		return;
	}

	for (int i = 0; i < str->capacity; i += 1)
	{
		if (i >= newLength)
		{
			str->text[i] = '\0';
		}
	}
	str->len = newLength;
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

uint64_t MString_GetRefs()
{
	return _mRefs;
}
