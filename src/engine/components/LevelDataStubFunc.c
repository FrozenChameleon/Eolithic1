#include "LevelDataStubFunc.h"

#include "../resources/LevelDataManager.h"

LevelData* LevelDataStubFunc_GetLevelData(const LevelDataStub* data)
{
	return LevelDataStubFunc_GetLevelDataResource(data)->mData;
}
Resource* LevelDataStubFunc_GetLevelDataResource(const LevelDataStub* data)
{
	return LevelDataManager_GetResource(MString_GetText(data->mLevelName));
}
