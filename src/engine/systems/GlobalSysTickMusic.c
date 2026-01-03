#include "GlobalSysTickMusic.h"

#include "../audio/Music.h"

static void Update(void* givenData)
{
	Music_Tick();
}

System* GlobalSysTickMusic_CreateSystem()
{
	System* sys = System_Create();
	sys->_mUpdate = Update;
	return sys;
}
