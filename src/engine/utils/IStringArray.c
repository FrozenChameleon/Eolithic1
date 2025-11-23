#include "IStringArray.h"

#include "../utils/Utils.h"
#include "../../third_party/stb_ds.h"
#include "IStrings.h"
#include "../utils/Logger.h"

static uint64_t _mRefs;

typedef struct IStringArray
{
	IStrings* mStrings;
	struct { int64_t key; IString value; } *hm_values;
} IStringArray;

IStringArray* IStringArray_Create()
{
	_mRefs += 1;
	IStringArray* sa = Utils_calloc(1, sizeof(IStringArray));
	sa->mStrings = IStrings_Create();
	return sa;
}
void IStringArray_Dispose(IStringArray* sa)
{
	if (sa == NULL)
	{
		Logger_LogInformation("Attempted to dispose NULL IStringArray");
		return;
	}

	_mRefs -= 1;
	hmfree(sa->hm_values);
	IStrings_Dispose(sa->mStrings);
	Utils_free(sa);
}
void IStringArray_Clear(IStringArray* sa)
{
	hmfree(sa->hm_values);
	sa->hm_values = NULL;
}
void IStringArray_Add(IStringArray* sa, const char* str)
{
	IString internedString = IStrings_Get(sa->mStrings, str);
	int64_t len = hmlen(sa->hm_values);
	hmput(sa->hm_values, len, internedString);
}
int64_t IStringArray_Length(IStringArray* sa)
{
	return hmlen(sa->hm_values);
}
IString IStringArray_Get(IStringArray* sa, int32_t index)
{
	return sa->hm_values[index].value;
}
uint64_t IStringArray_GetRefs()
{
	return _mRefs;
}
