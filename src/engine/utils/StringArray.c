#include "StringArray.h"

#include "../utils/Utils.h"
#include "../../third_party/stb_ds.h"
#include "InternedStrings.h"

static uint64_t _mRefs;

typedef struct StringArray
{
	InternedStrings* mInternedStrings;
	struct { int32_t key; const char* value; } *mHashMap;
} StringArray;

StringArray* StringArray_Create()
{
	_mRefs += 1;
	StringArray* sa = Utils_malloc(sizeof(StringArray));
	memset(sa, 0, sizeof(StringArray));
	sa->mInternedStrings = InternedStrings_Create();
	return sa;
}
void StringArray_Dispose(StringArray* sa)
{
	_mRefs -= 1;
	hmfree(sa->mHashMap);
	InternedStrings_Dispose(sa->mInternedStrings);
	Utils_free(sa);
}
void StringArray_Add(StringArray* sa, const char* str)
{
	InternedStrings_Add(sa->mInternedStrings, str);
	int32_t len = hmlen(sa->mHashMap);
	const char* internedString = InternedStrings_Get(sa->mInternedStrings, str);
	hmput(sa->mHashMap, len, internedString);
}
int32_t StringArray_Length(StringArray* sa)
{
	return hmlen(sa->mHashMap);
}
const char* StringArray_Get(StringArray* sa, int32_t index)
{
	return sa->mHashMap[index].value;
}
uint64_t StringArray_GetRefs()
{
	return _mRefs;
}
