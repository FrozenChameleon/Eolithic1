#include "DrawLineOfSightSys.h"

#include "../systems/SystemFunc.h"
#include "../core/Func.h"
#include "../globals/Globals.h"
#include "DrawLineOfSightSys.h"

static void Draw(void* givenData, SpriteBatch* spriteBatch)
{
//#if EDITOR
	SystemFunc_DrawHelper(C_DrawLineOfSight, DrawLineOfSightSys_DrawRoutine, spriteBatch);
//#endif
}

//#if EDITOR
void DrawLineOfSightSys_DrawRoutine(Entity owner, DrawLineOfSight* data, SpriteBatch* spriteBatch)
{
	if (!GLOBALS_DEBUG_SHOW_INGAME_COLLISION)
	{
		return;
	}

	if (Is_OnScreen(owner))
	{
		Do_DrawLineOfSight(owner, spriteBatch, 0, 0, false, 0);
	}
}
//#endif

System* DrawLineOfSightSys_CreateSystem(void)
{
	System* sys = System_Create();
	sys->_mDraw = Draw;
	return sys;
}

