#include "GlobalSysTickSoundEffect.h"

#include "../audio/SoundEffect.h"

static void Update(System* sys)
{
	SoundEffect_Tick();
}

System* GlobalSysTickSoundEffect_CreateSystem()
{
	System* sys = System_Create();
	sys->_mUpdate = Update;
	return sys;
}
