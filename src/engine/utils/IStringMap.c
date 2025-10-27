#include "IStringMap.h"

#include "../utils/Utils.h"
#include "../../third_party/stb_ds.h"
#include "IStrings.h"

static uint64_t _mRefs;

typedef struct IStringMap
{
	IStrings* mStrings;
	struct { IString key; IString value; } *sh_values;
} IStringMap;

IStringMap* IStringMap_Create()
{
	_mRefs += 1;
	IStringMap* sa = Utils_calloc(1, sizeof(IStringMap));
	sa->mStrings = IStrings_Create();
	return sa;
}
void IStringMap_Dispose(IStringMap* sm)
{
	_mRefs -= 1;
	shfree(sm->sh_values);
	IStrings_Dispose(sm->mStrings);
	Utils_free(sm);
}
void IStringMap_Clear(IStringMap* sm)
{
	shfree(sm->sh_values);
	sm->sh_values = NULL;
}
void IStringMap_Add(IStringMap* sm, const char* key, const char* value)
{
	IString internedKey = IStrings_Get(sm->mStrings, key);
	IString internedValue = IStrings_Get(sm->mStrings, value);
	shput(sm->sh_values, internedKey, internedValue);
}
IString IStringMap_Get(IStringMap* sm, const char* key)
{
	return shget(sm->sh_values, key);
}
bool IStringMap_Contains(IStringMap* sm, const char* key)
{
	int64_t index = shgeti(sm->sh_values, key);
	if (index < 0)
	{
		return false;
	}
	return true;
}
int64_t IStringMap_Length(IStringMap* sm)
{
	return shlen(sm->sh_values);
}
IString IStringMap_GetByIndex(IStringMap* sm, int32_t index)
{
	return sm->sh_values[index].value;
}
uint64_t IStringMap_GetRefs()
{
	return _mRefs;
}
