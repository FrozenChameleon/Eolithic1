#pragma once

#include "../math/Vector2.h"
#include "../render/DrawRectangle.h"

typedef struct CollisionEngine
{
	int32_t mDefaultBodyPushAmount;
	bool mIsNullDividePlus;
	Vector2 mFixedGravity;
	int32_t* mCollisionGridPristine;
	int32_t* mCollisionGrid;
	Rectangle mCollisionGridSize;
} CollisionEngine;

