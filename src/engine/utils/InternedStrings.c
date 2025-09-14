#include "InternedStrings.h"

#include "../utils/Utils.h"
#include "../../third_party/stb_ds.h"

static uint64_t _mRefs;

typedef struct InternedStrings
{
	struct { const char* key; int32_t value; } *mStringHashMap;
} InternedStrings;

InternedStrings* InternedStrings_Create()
{
	_mRefs += 1;
	InternedStrings* is = Utils_malloc(sizeof(InternedStrings));
	memset(is, 0, sizeof(InternedStrings));
	sh_new_arena(is->mStringHashMap);
	return is;
}
void InternedStrings_Dispose(InternedStrings* is)
{
	_mRefs -= 1;
	shfree(is->mStringHashMap);
	Utils_free(is);
}
void InternedStrings_Add(InternedStrings* is, const char* str)
{
	shput(is->mStringHashMap, str, 0);
}
const char* InternedStrings_Get(InternedStrings* is, const char* str)
{
	InternedStrings_Add(is, str);
	int32_t index = shgeti(is->mStringHashMap, str);
	return is->mStringHashMap[index].key;
}
int32_t InternedStrings_Length(InternedStrings* is)
{
	return shlen(is->mStringHashMap);
}
const char* InternedStrings_GetByIndex(InternedStrings* is, int32_t index)
{
	return is->mStringHashMap[index].value;
}
uint64_t InternedStrings_GetRefs()
{
	return _mRefs;
}
