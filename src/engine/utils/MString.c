#include "MString.h"

#include "Utils.h"
#include "Logger.h"

static uint64_t _mRefs;

MString* MString_CreateFromSubString(const char* str, int32_t startIndex, int32_t length)
{
	MString* mstring = MString_Create(str);
	Utils_memset(mstring->str, 0, mstring->capacity);
	Utils_strlcpy(mstring->str, str + startIndex, length + 1);
	mstring->len = length;
	return mstring;
}
MString* MString_Create(const char* fromThisStr)
{
	int32_t strLen = Utils_strlen(fromThisStr);
	MString* mstring = MString_CreateEmpty(strLen + 1);
	Utils_strlcpy(mstring->str, fromThisStr, strLen + 1);
	mstring->len = strLen;
	mstring->capacity = strLen + 1;
	return mstring;
}
MString* MString_CreateEmpty(int32_t size)
{
	_mRefs += 1;

	MString* mstring = Utils_malloc(sizeof(MString));
	mstring->str = Utils_calloc(1, size);
	mstring->len = 0;
	mstring->capacity = size;
	return mstring;
}
MString* MString_AddAssignChar(MString* thisWillBeDisposed, char c)
{
	MString* stringToReturn = MString_CreateEmpty(thisWillBeDisposed->capacity + 1);
	Utils_strlcpy(stringToReturn->str, thisWillBeDisposed->str, thisWillBeDisposed->len + 1);
	stringToReturn->str[thisWillBeDisposed->len] = c;
	stringToReturn->str[thisWillBeDisposed->len + 1] = '\0';
	stringToReturn->len = thisWillBeDisposed->len + 1;
	MString_Dispose(thisWillBeDisposed);
	return stringToReturn;
}
void MString_Dispose(MString* cstr)
{
	if (cstr == NULL)
	{
		return;
	}

	_mRefs -= 1;

	Utils_free(cstr->str);
	Utils_free(cstr);
}

uint64_t MString_GetRefs()
{
	return _mRefs;
}
