#pragma once

#include "PathNode.h"
#include "../math/Vector2.h"
#include "../render/DrawRectangle.h"

typedef struct CollisionEngine
{
	int mDefaultBodyPushAmount;
	bool mIsNullDividePlus;
	Vector2 mFixedGravity;
	int* mCollisionGridPristine;
	int* mCollisionGrid;
	/*std::shared_ptr<OePathNode> mLastNode;
	std::vector<std::shared_ptr<OePathNode>> mTempNodes;
	std::vector<std::shared_ptr<OePathNode>> mOpenNodes;
	std::vector<std::shared_ptr<OePathNode>> mClosedNodes;*/
	DrawRectangle* mDebugNodeRectangles;
	DrawRectangle* mDebugManyRectangles;
	Rectangle mCollisionGridSize;
} CollisionEngine;

