#include "GlobalSysDrawFPS.h"

#include "../utils/Cvars.h"
#include "../render/Color.h"
#include "../utils/Utils.h"
#include "../core/GameUpdater.h"
#include "../math/Rectangle.h"
#include "../render/DrawTool.h"
#include "../render/SpriteBatch.h"

#define TIME_TO_STOP_DRAWING 5

static int _mDoNotDrawThisCounter = TIME_TO_STOP_DRAWING;
static int _mOffsetFromCorner;
static const char* _mFont = "game";

void GlobalSysDrawFPS_SetOffsetFromCorner(int offset)
{
	_mOffsetFromCorner = offset;
}
void GlobalSysDrawFPS_SetFont(const char* font)
{
	_mFont = font;
}
void GlobalSysDrawFPS_DoNotDrawThisRightNow()
{
	_mDoNotDrawThisCounter = TIME_TO_STOP_DRAWING;
}
static void Update(System* sys)
{
	if (_mDoNotDrawThisCounter > 0)
	{
		_mDoNotDrawThisCounter -= 1;
	}
}
static void DrawHud(System* sys, SpriteBatch* spriteBatch)
{
	if (_mDoNotDrawThisCounter > 0)
	{
		return;
	}

	if (!Cvars_GetAsBool(CVARS_USER_IS_SHOWING_FPS))
	{
		return;
	}

	//TODO C99
	/*
	const char* stringToDraw = GameUpdater_GetFpsString();
	Rectangle bounds = OeDrawTool_GetBounds(stringToDraw, _mFont);
	int shadowOffset = 1;
	float x = _mOffsetFromCorner;
	float y = OeUtils_GetInternalRenderHeight() - bounds.Height - shadowOffset - _mOffsetFromCorner;
	spriteBatch->DrawString(_mFont, stringToDraw, OeColors_BLACK, 200, Vector2(x + shadowOffset, y + shadowOffset));
	spriteBatch->DrawString(_mFont, stringToDraw, OeColors_WHITE, 200, Vector2(x, y));
	*/
}

System* GlobalSysDrawFPS_CreateSystem()
{
	System* sys = System_Create();
	sys->_mDrawHud = DrawHud;
	sys->_mUpdate = Update;
	return sys;
}
