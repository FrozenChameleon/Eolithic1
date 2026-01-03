#include "GlobalSysTickSoundEffect.h"

#include "../audio/SoundEffect.h"

static void Update(void* givenData)
{
	SoundEffect_Tick();
}

System* GlobalSysTickSoundEffect_CreateSystem()
{
	System* sys = System_Create();
	sys->_mUpdate = Update;
	return sys;
}
