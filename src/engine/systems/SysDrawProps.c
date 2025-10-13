#include "SysDrawProps.h"

#include "../core/Func.h"
#include "../leveldata/LevelData.h"
#include "SysDrawProps.h"

static void Draw(System* sys, SpriteBatch* spriteBatch)
{
	//TODO C99
	//Get_LevelData()->DrawProps(spriteBatch, OeFunc::Get_Camera());
}

System* SysDrawProps_CreateSystem()
{
	System* sys = System_Create();
	sys->_mDraw = Draw;
	return sys;
}
