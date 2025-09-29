#include "BodySys.h"

#include "../core/GameHelper.h"
#include "../core/Func.h"

static void InitRoutine(Entity owner, Body* data)
{
	data->mOwner = owner;
	data->mMaxDeceleration = GameHelper_GetGravityDecelerationMax();
	data->mLastCollisionBitTouched = -1;
	Body_ResetBeforeCollideWithBody(data);
	Body_ResetCollideWithBody(data);
	Body_ResetCollideWithCollision(data);
}
static void UpdateRoutine(Entity owner, Body* data)
{
	if (data->mIsExtraBody || data->mIsExtraBodyThatFollows)
	{
		Entity parent = Get_ParentEntity(owner);
		if (parent != ENTITY_NOTHING)
		{
			if (data->mIsExtraBodyThatFollows)
			{
				Vector2 pos = Get_Position(parent);
				Body_ForcePosition(data, pos.X + data->mOffset.X, pos.Y + data->mOffset.Y);
			}
		}
		else
		{
			Do_RemoveComponent(C_Body, owner);
			Do_SetComplete(owner);
		}
	}
}
static void UpdateLastRenderPositionRoutine(Body* data)
{
	Body_UpdateLastRenderPosition(data);
}

System* BodySys_CreateSystem()
{
	SystemSimple* ss = SystemSimple_CreateSystemSimple(C_CrThingEnemyAnchorManData);
	ss->_mInitRoutine = InitRoutine;
	ss->_mUpdateRoutine = UpdateRoutine;
	ss->_mUpdateLastRenderPositionRoutine = UpdateLastRenderPositionRoutine;
	return SystemSimple_CreateSystem(ss);
}
