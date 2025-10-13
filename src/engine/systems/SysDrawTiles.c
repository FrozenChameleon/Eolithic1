#include "SysDrawTiles.h"

#include "../core/Func.h"
#include "../leveldata/LevelData.h"

static void Draw(System* sys, SpriteBatch* spriteBatch)
{
	//TODO C99
	//Get_LevelData()->DrawTiles(spriteBatch, OeFunc::Get_Camera());
}

System* SysDrawTiles_CreateSystem()
{
	System* sys = System_Create();
	sys->_mDraw = Draw;
	return sys;
}
