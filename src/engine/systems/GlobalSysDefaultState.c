#include "GlobalSysDefaultState.h"

#include "../globals/Globals.h"
#include "../gamestate/GameStateManager.h"
#include "../gamestate/GameState.h"

static void Draw(System* sys, SpriteBatch* spriteBatch)
{
	if (GLOBALS_DEBUG_IS_EDITOR_MODE)
	{
#if EDITOR
		//WILLNOTDO 06262023 (EDITOR) 2023 OeEditor.Draw(spriteBatch);
#endif
	}
	else
	{
		GameState_Draw(GameStateManager_GetGameState(), spriteBatch);
	}
}
static void DrawHud(System* sys, SpriteBatch* spriteBatch)
{
	if (GLOBALS_DEBUG_IS_EDITOR_MODE)
	{
#if EDITOR
		//WILLNOTDO 06262023 (EDITOR) 2023 OeEditor.DrawHud(spriteBatch);
#endif
	}
	else
	{
		GameState_DrawHud(GameStateManager_GetGameState(), spriteBatch);
	}
}
/*void OeGlobalSysDefaultState_DrawDebugHud(OeSpriteBatch* spriteBatch)
{
#if EDITOR
	//WILLNOTDO 06262023 (EDITOR) 2023 OeGameStateManager.ActiveGameState.DrawDebugHud(spriteBatch);
#endif
}*/
static void Update(System* sys)
{
#if EDITOR
	if (GLOBALS_DEBUG_IS_EDITOR_MODE)
	{
		//WILLNOTDO 06262023 (EDITOR) 2023 OeEditor.Update();
	}
	else
	{
		//WILLNOTDO 06262023 (EDITOR) 2023 OeGuiThingViewer.Update();
		//WILLNOTDO 06262023 (EDITOR) 2023 if (!OeConsole.IsPresent())
		//WILLNOTDO 06262023 (EDITOR) 2023 {
		GameState_Update(GameStateManager_GetGameState());
		//WILLNOTDO 06262023 (EDITOR) 2023 }
	}
#else
	GameState_Update(GameStateManager_GetGameState());
#endif
}

System* GlobalSysDefaultState_CreateSystem()
{
	System* sys = System_Create();
	sys->_mDraw = Draw;
	sys->_mDrawHud = DrawHud;
	sys->_mUpdate = Update;
	return sys;
}
