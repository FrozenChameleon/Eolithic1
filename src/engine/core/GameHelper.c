#include "GameHelper.h"

#include "../gamestate/GameStateManager.h"
#include "../components/Camera.h"

const float GAME_HELPER_DEFAULT_GRAVITY_DECELERATION = 0.233f;
const float GAME_HELPER_DEFAULT_GRAVITY_DECELERATION_MAX = 5.25f;
const int GAME_HELPER_DEFAULT_MOVING_PLATFORM_LEEWAY = 1;

int GAME_HELPER_PLATFORM_UP = -1;
int GAME_HELPER_PLATFORM_DOWN = -1;
int GAME_HELPER_PLATFORM_RIGHT = -1;
int GAME_HELPER_PLATFORM_LEFT = -1;

void GameHelper_DoDefaultSetupThingInstanceSettings(ThingInstance* instance, bool ignoreWarnings)
{
	//OeThingInstance::SetupSettings(instance, ignoreWarnings);
}
Resource* GameHelper_GetDefaultLevelDataResource()
{
	return NULL;
	//TODO
	//OeComLevelDataStub* stub = OeFunc::Get_ActiveGameState()->GetFirstSetComponent<OeComLevelDataStub>();
	//return OeComLevelDataStubFunc::GetLevelDataResource(stub);
}
LevelData* GameHelper_GetDefaultLevelData()
{
	return NULL;
	//TODO
	//OeComLevelDataStub* stub = OeFunc::Get_ActiveGameState()->GetFirstSetComponent<OeComLevelDataStub>();
	//return OeComLevelDataStubFunc::GetLevelData(stub);
}
void GameHelper_UpdateLastRenderPositionNormally()
{
	int32_t stateSystemsLen = GameStateManager_GetStateSystemsLen();
	System* stateSystems = GameStateManager_GetStateSystems();
	for (int i = 0; i < stateSystemsLen; i += 1)
	{
		System* currentSystem = &stateSystems[i];
		currentSystem->_mUpdateLastRenderPosition(currentSystem, GameStateManager_GetGameState());
	}
}
Camera* GameHelper_GetDefaultCameraForRender()
{
	return GameStateManager_GetFirstSetComponent(C_Camera);
}
float GameHelper_GetDefaultPostGameBrightness()
{
	return 1;
}
void GameHelper_UpdateGlobalSystemsNormally()
{
	int32_t globalSystemsLen = GameStateManager_GetGlobalSystemsLen();
	System* globalSystems = GameStateManager_GetGlobalSystems();
	for (int i = 0; i < globalSystemsLen; i += 1)
	{
		System* currentSystem = &globalSystems[i];
		currentSystem->_mUpdate(currentSystem);
	}
}
void GameHelper_DrawGlobalSystemsNormally(SpriteBatch* spriteBatch)
{
	int32_t globalSystemsLen = GameStateManager_GetGlobalSystemsLen();
	System* globalSystems = GameStateManager_GetGlobalSystems();
	for (int i = 0; i < globalSystemsLen; i += 1)
	{
		System* currentSystem = &globalSystems[i];
		currentSystem->_mDraw(currentSystem, spriteBatch);
	}
}
void GameHelper_DrawHudGlobalSystemsNormally(SpriteBatch* spriteBatch)
{
	int32_t globalSystemsLen = GameStateManager_GetGlobalSystemsLen();
	System* globalSystems = GameStateManager_GetGlobalSystems();
	for (int i = 0; i < globalSystemsLen; i += 1)
	{
		System* currentSystem = &globalSystems[i];
		currentSystem->_mDrawHud(currentSystem, spriteBatch);
	}
}
void GameHelper_DrawDebugHudGlobalSystemsNormally(SpriteBatch* spriteBatch)
{
	int32_t globalSystemsLen = GameStateManager_GetGlobalSystemsLen();
	System* globalSystems = GameStateManager_GetGlobalSystems();
	for (int i = 0; i < globalSystemsLen; i += 1)
	{
		System* currentSystem = &globalSystems[i];
		currentSystem->_mDrawDebugHud(currentSystem, spriteBatch);
	}
}
void GameHelper_UpdateStateSystemsNormally()
{
	int32_t stateSystemsLen = GameStateManager_GetStateSystemsLen();
	System* stateSystems = GameStateManager_GetStateSystems();
	for (int i = 0; i < stateSystemsLen; i += 1)
	{
		System* currentSystem = &stateSystems[i];
		currentSystem->_mUpdate(currentSystem);
	}
}
void GameHelper_DrawStateSystemsNormally(SpriteBatch* spriteBatch)
{
	int32_t stateSystemsLen = GameStateManager_GetStateSystemsLen();
	System* stateSystems = GameStateManager_GetStateSystems();
	for (int i = 0; i < stateSystemsLen; i += 1)
	{
		System* currentSystem = &stateSystems[i];
		currentSystem->_mDraw(currentSystem, spriteBatch);
	}
}
void GameHelper_DrawHudStateSystemsNormally(SpriteBatch* spriteBatch)
{
	int32_t stateSystemsLen = GameStateManager_GetStateSystemsLen();
	System* stateSystems = GameStateManager_GetStateSystems();
	for (int i = 0; i < stateSystemsLen; i += 1)
	{
		System* currentSystem = &stateSystems[i];
		currentSystem->_mDrawHud(currentSystem, spriteBatch);
	}
}
void GameHelper_DrawDebugHudStateSystemsNormally(SpriteBatch* spriteBatch)
{
	int32_t stateSystemsLen = GameStateManager_GetStateSystemsLen();
	System* stateSystems = GameStateManager_GetStateSystems();
	for (int i = 0; i < stateSystemsLen; i += 1)
	{
		System* currentSystem = &stateSystems[i];
		currentSystem->_mDrawDebugHud(currentSystem, spriteBatch);
	}
}

void GameHelper_UpdateLastRenderPosition()
{
	//REMOVEME
}

Camera* GameHelper_GetCameraForRender()
{
	return NULL;
	//REMOVEME
}

void GameHelper_OnNormalGameStateChange()
{
	//REMOVEME
}

void GameHelper_UpdateGlobalSystems()
{
	//REMOVEME
}

void GameHelper_DrawGlobalSystems(SpriteBatch* spriteBatch)
{
	//REMOVEME
}

void GameHelper_DrawHudGlobalSystems(SpriteBatch* spriteBatch)
{
	//REMOVEME
}

void GameHelper_DrawDebugHudGlobalSystems(SpriteBatch* spriteBatch)
{
	//REMOVEME
}

void GameHelper_CreateGameStates()
{

}
