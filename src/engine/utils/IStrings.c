#include "IStrings.h"

#include "../utils/Utils.h"
#include "../../third_party/stb_ds.h"

typedef struct IStrings
{
	struct { IString key; int32_t value; } *sh_values;
} IStrings;

static uint64_t _mRefs;
static IStrings* _mGlobal;
static bool _mHasInitGlobal;

static void InitGlobal()
{
	if (_mHasInitGlobal)
	{
		return;
	}

	_mGlobal = IStrings_Create();

	_mHasInitGlobal = true;
}

IStrings* IStrings_Create()
{
	_mRefs += 1;
	IStrings* is = Utils_calloc(1, sizeof(IStrings));
	sh_new_arena(is->sh_values);
	return is;
}
void IStrings_Dispose(IStrings* is)
{
	_mRefs -= 1;
	shfree(is->sh_values);
	Utils_free(is);
}
IString IStrings_Get(IStrings* is, const char* str)
{
	shput(is->sh_values, str, 0);
	ptrdiff_t index = shgeti(is->sh_values, str);
	return is->sh_values[index].key;
}
size_t IStrings_Length(IStrings* is)
{
	return shlen(is->sh_values);
}
IString IStrings_GetByIndex(IStrings* is, int32_t index)
{
	return is->sh_values[index].key;
}
uint64_t IStrings_GetRefs()
{
	return _mRefs;
}
IString IStrings_GlobalGet(const char* str)
{
	InitGlobal();

	return IStrings_Get(_mGlobal, str);
}
void IStrings_GlobalDispose()
{
	InitGlobal();

	IStrings_Dispose(_mGlobal);
	_mGlobal = NULL;
	_mHasInitGlobal = false;
}
size_t IStrings_GlobalLength()
{
	return IStrings_Length(_mGlobal);
}
