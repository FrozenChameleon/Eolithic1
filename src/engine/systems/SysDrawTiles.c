#include "SysDrawTiles.h"

#include "../core/Func.h"
#include "../leveldata/LevelData.h"

static void Draw(System* sys, SpriteBatch* spriteBatch)
{
	LevelData_DrawTiles(Get_LevelData(), spriteBatch, Get_Camera());
}

System* SysDrawTiles_CreateSystem()
{
	System* sys = System_Create();
	sys->_mDraw = Draw;
	return sys;
}
