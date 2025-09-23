#pragma once

#include "System.h"

typedef struct Body Body;

typedef struct SystemSimple
{
	ComponentType _mType;
	bool _mHasBeenInit;
	bool (*_mBeforeCollideWithBody)(Body* myBody, Body* otherBody, int myDirectionX, int myDirectionY, int otherDirectionX, int otherDirectionY, bool isVertical);
	void (*_mCollideWithBody)(Body* myBody, Body* otherBody, int myDirectionX, int myDirectionY, int otherDirectionX, int otherDirectionY, bool isVertical);
	bool (*_mCollideWithCollision)(Body* myBody, int x, int y, int width, int height, int myDirectionX, int myDirectionY, int collisionBit, bool isVertical);
	void (*_mBeforeUpdateRoutine)();
	void (*_mAfterUpdateRoutine)();
	void (*_mDrawRoutine)(Entity owner, void* data, SpriteBatch* spriteBatch);
	void (*_mDrawHudRoutine)(Entity owner, void* data, SpriteBatch* spriteBatch);
	void (*_mDrawDebugHudRoutine)(Entity owner, void* data, SpriteBatch* spriteBatch);
	void (*_mJustCompletedRoutine)(Entity owner, void* data);
	void (*_mUpdateLastRenderPositionRoutine)(void* data);
	void (*_mReceiveBroadcastRoutine)(Entity owner, void* data, int broadcastType, int packet1, int packet2, int packet3);
	void (*_mUpdateRoutine)(Entity entity, void* data);
	void (*_mInitRoutine)(Entity owner, void* data);
	void (*_mSetupSystem)();
} SystemSimple;

System* SystemSimple_CreateSystemSimple(ComponentType ctype, void (*setupSystem)());