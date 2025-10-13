#include "GlobalSysUpdateInput.h"

#include "../input/Input.h"

static void Update(System* sys)
{
	Input_Update(false);
}

System* GlobalSysUpdateInput_CreateSystem()
{
	System* sys = System_Create();
	sys->_mUpdate = Update;
	return sys;
}
