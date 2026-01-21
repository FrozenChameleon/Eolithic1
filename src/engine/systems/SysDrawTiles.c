#include "SysDrawTiles.h"

#include "../core/Func.h"
#include "../leveldata/LevelData.h"

static void Draw(void* givenData, SpriteBatch* spriteBatch)
{
	LevelData_DrawTiles(Get_LevelData(), spriteBatch, Get_Camera());
}

System* SysDrawTiles_CreateSystem(void)
{
	System* sys = System_Create();
	sys->_mDraw = Draw;
	return sys;
}
