#include "LevelDataStubFunc.h"

LevelData* LevelDataStubFunc_GetLevelData(const LevelDataStub* data)
{
	return NULL;
//TODO C99	return GetLevelDataResource(data)->GetData();
}

Resource* LevelDataStubFunc_GetLevelDataResource(const LevelDataStub* data)
{
	return NULL;
	//TODO C99	return OeResourceManagers::LevelDataManager.GetResource(data->mLevelName.Get());
}
