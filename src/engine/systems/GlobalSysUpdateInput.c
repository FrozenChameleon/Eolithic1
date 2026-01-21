#include "GlobalSysUpdateInput.h"

#include "../input/Input.h"

static void Update(void* givenData)
{
	Input_Update(false);
}

System* GlobalSysUpdateInput_CreateSystem(void)
{
	System* sys = System_Create();
	sys->_mUpdate = Update;
	return sys;
}
