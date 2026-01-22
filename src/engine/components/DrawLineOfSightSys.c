#include "DrawLineOfSightSys.h"

#include "../systems/SystemFunc.h"
#include "../core/Func.h"
#include "../globals/Globals.h"
#include "DrawLineOfSightSys.h"

static void Draw(void* givenData, SpriteBatch* spriteBatch)
{
//#ifdef EDITOR_MODE
	SystemFunc_DrawHelper(C_DrawLineOfSight, (SystemFunc_DrawHelperFunc)DrawLineOfSightSys_DrawRoutine, spriteBatch);
//#endif
}

//#ifdef EDITOR_MODE
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

