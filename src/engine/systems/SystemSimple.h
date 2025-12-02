#pragma once

#include "System.h"

typedef struct Body Body;

typedef struct SystemSimple
{
	ComponentType _mType;
	bool _mHasBeenInit;
	bool (*_mBeforeCollideWithBody)(Body* myBody, Body* otherBody, int32_t myDirectionX, int32_t myDirectionY, int32_t otherDirectionX, int32_t otherDirectionY, bool isVertical);
	void (*_mCollideWithBody)(Body* myBody, Body* otherBody, int32_t myDirectionX, int32_t myDirectionY, int32_t otherDirectionX, int32_t otherDirectionY, bool isVertical);
	bool (*_mCollideWithCollision)(Body* myBody, int32_t x, int32_t y, int32_t width, int32_t height, int32_t myDirectionX, int32_t myDirectionY, int32_t collisionBit, bool isVertical);
	void (*_mBeforeUpdateRoutine)();
	void (*_mAfterUpdateRoutine)();
	void (*_mDrawRoutine)(Entity owner, void* data, SpriteBatch* spriteBatch);
	void (*_mDrawHudRoutine)(Entity owner, void* data, SpriteBatch* spriteBatch);
	void (*_mDrawDebugHudRoutine)(Entity owner, void* data, SpriteBatch* spriteBatch);
	void (*_mJustCompletedRoutine)(Entity owner, void* data);
	void (*_mUpdateLastRenderPositionRoutine)(void* data);
	void (*_mReceiveBroadcastRoutine)(Entity owner, void* data, int32_t broadcastType, int32_t packet1, int32_t packet2, int32_t packet3);
	void (*_mUpdateRoutine)(Entity entity, void* data);
	void (*_mInitRoutine)(Entity owner, void* data);
	void (*_mSetupSystem)();
} SystemSimple;

SystemSimple* SystemSimple_Create(ComponentType ctype);
System* SystemSimple_CreateSystem(SystemSimple* ss);