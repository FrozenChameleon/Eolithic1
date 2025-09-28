#include "SystemSimple.h"

#include "../collision/Body.h"
#include "../utils/Utils.h"
#include "SystemFunc.h"
#include "../core/Func.h"

static void InitSystemSimple(SystemSimple* ss)
{
	if (ss->_mHasBeenInit)
	{
		return;
	}

	ss->_mSetupSystem();

	ss->_mHasBeenInit = true;
}

static void InitStringSetting(void* sys, const char* name, const char* value)
{
	SystemSimple* ss = ((System*)sys)->_mData;

	InitSystemSimple(ss);

	//OeSystemFunc::InitStringSetting<T>(name, value);
}
static void Init(void* sys, ComponentType givenType, Entity owner)
{
	SystemSimple* ss = ((System*)sys)->_mData;
	
	InitSystemSimple(ss);

	if (givenType != ss->_mType)
	{
		return;
	}

	if (ss->_mInitRoutine != NULL)
	{
		SystemFunc_InitHelper(ss->_mType, givenType, ss->_mInitRoutine, owner);
		if ((ss->_mBeforeCollideWithBody != NULL) || (ss->_mCollideWithBody != NULL) || (ss->_mCollideWithCollision != NULL))
		{
			Body* body = Get_Body(owner);
			if (ss->_mBeforeCollideWithBody != NULL)
			{
				body->mBeforeCollideWithBody = ss->_mBeforeCollideWithBody;
			}
			if (ss->_mCollideWithBody != NULL)
			{
				body->mCollideWithBody = ss->_mCollideWithBody;
			}
			if (ss->_mCollideWithCollision != NULL)
			{
				body->mCollideWithCollision = ss->_mCollideWithCollision;
			}
		}
	}
}
static void Update(void* sys)
{
	SystemSimple* ss = ((System*)sys)->_mData;

	InitSystemSimple(ss);

	if (ss->_mBeforeUpdateRoutine != NULL)
	{
		ss->_mBeforeUpdateRoutine();
	}
	if (ss->_mUpdateRoutine != NULL)
	{
		SystemFunc_UpdateHelper(ss->_mType, ss->_mUpdateRoutine);
	}
	if (ss->_mAfterUpdateRoutine != NULL)
	{
		ss->_mAfterUpdateRoutine();
	}
}
static void Draw(void* sys, SpriteBatch* spriteBatch)
{
	SystemSimple* ss = ((System*)sys)->_mData;

	InitSystemSimple(ss);

	if (ss->_mDrawRoutine != NULL)
	{
		SystemFunc_DrawHelper(ss->_mType, ss->_mDrawRoutine, spriteBatch);
	}
}
static void DrawHud(void* sys, SpriteBatch* spriteBatch)
{
	SystemSimple* ss = ((System*)sys)->_mData;

	InitSystemSimple(ss);

	if (ss->_mDrawHudRoutine != NULL)
	{
		SystemFunc_DrawHudHelper(ss->_mType, ss->_mDrawHudRoutine, spriteBatch);
	}
}
static void DrawDebugHud(void* sys, SpriteBatch* spriteBatch)
{
	SystemSimple* ss = ((System*)sys)->_mData;

	InitSystemSimple(ss);

	if (ss->_mDrawDebugHudRoutine != NULL)
	{
		SystemFunc_DrawDebugHudHelper(ss->_mType, ss->_mDrawDebugHudRoutine, spriteBatch);
	}
}
static void UpdateLastRenderPosition(void* sys, GameState* gameState)
{
	SystemSimple* ss = ((System*)sys)->_mData;

	InitSystemSimple(ss);

	if (ss->_mUpdateLastRenderPositionRoutine != NULL)
	{
		SystemFunc_UpdateLastRenderPositionHelper(ss->_mType, gameState, ss->_mUpdateLastRenderPositionRoutine);
	}
}
static void ReceiveBroadcast(void* sys, int type, int packet1, int packet2, int packet3)
{
	SystemSimple* ss = ((System*)sys)->_mData;

	InitSystemSimple(ss);

	if (ss->_mReceiveBroadcastRoutine != NULL)
	{
		SystemFunc_ReceiveBroadcastHelper(ss->_mType, ss->_mReceiveBroadcastRoutine, type, packet1, packet2, packet3);
	}
}

SystemSimple* SystemSimple_CreateSystemSimple(ComponentType ctype)
{
	SystemSimple* ss = Utils_malloc(sizeof(SystemSimple));
	Utils_memset(ss, 0, sizeof(SystemSimple));
	ss->_mType = ctype;
	return ss;
}
System* SystemSimple_CreateSystem(SystemSimple* ss)
{
	System* sys = Utils_malloc(sizeof(System));
	Utils_memset(sys, 0, sizeof(System));
	sys->_mData = ss;
	//sys->_mInitStringSettingsHere = InitStringSetting;
	sys->_mInit = Init;
	sys->_mUpdate = Update;
	sys->_mDraw = Draw;
	sys->_mDrawHud = DrawHud;
	sys->_mDrawDebugHud = DrawDebugHud;
	sys->_mUpdateLastRenderPosition = UpdateLastRenderPosition;
	sys->_mReceiveBroadcast = ReceiveBroadcast;
	return sys;
}
