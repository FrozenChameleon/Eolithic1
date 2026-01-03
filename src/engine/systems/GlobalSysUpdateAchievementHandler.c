#include "GlobalSysUpdateAchievementHandler.h"

#include "../achievement/AchievementHandler.h"

static void Update(void* givenData)
{
	AchievementHandler_Update();
}

System* GlobalSysUpdateAchievementHandler_CreateSystem()
{
	System* sys = System_Create();
	sys->_mUpdate = Update;
	return sys;
}
