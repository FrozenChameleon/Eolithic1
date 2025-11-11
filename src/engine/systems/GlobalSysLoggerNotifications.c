#include "GlobalSysLoggerNotifications.h"

#include "../globals/Globals.h"
#include "../gamestate/GameStateManager.h"
#include "../utils/Logger.h"
#include "GlobalSysLoggerNotifications.h"

static void DrawHud(System* sys, SpriteBatch* spriteBatch)
{
	//TODO C99 Logger_DrawHud(spriteBatch);
}
static void Update(System* sys)
{
	//TODO C99 Logger_Update();
};

System* GlobalSysLoggerNotifications_CreateSystem()
{
	System* sys = System_Create();
	sys->_mDrawHud = DrawHud;
	sys->_mUpdate = Update;
	return sys;
}
