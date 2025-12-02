#include "System.h"

#include "../utils/Utils.h"

static void DummyInitStringSettingsHere(System* sys)
{
}
static void DummyInit(System* sys, ComponentType givenType, Entity owner)
{
}
static void DummyUpdate(System* sys)
{
}
static void DummyDraw(System* sys, SpriteBatch* spriteBatch)
{
}
static void DummyDrawHud(System* sys, SpriteBatch* spriteBatch)
{
}
static void DummyDrawDebugHud(System* sys, SpriteBatch* spriteBatch)
{
}
static void DummyUpdateLastRenderPosition(System* sys, GameState* gameState)
{
}
static void DummyReceiveBroadcast(System* sys, int32_t broadcastType, int32_t packet1, int32_t packet2, int32_t packet3)
{
}

System* System_Create()
{
	System* sys = Utils_calloc(1, sizeof(System));
	sys->_mInitStringSettingsHere = DummyInitStringSettingsHere;
	sys->_mInit = DummyInit;
	sys->_mUpdate = DummyUpdate;
	sys->_mDraw = DummyDraw;
	sys->_mDrawHud = DummyDrawHud;
	sys->_mDrawDebugHud = DummyDrawDebugHud;
	sys->_mUpdateLastRenderPosition = DummyUpdateLastRenderPosition;
	sys->_mReceiveBroadcast = DummyReceiveBroadcast;
	return sys;
}
