#pragma once

#include "PathNode.h"
#include "../math/Vector2.h"
#include "../render/DrawRectangle.h"

typedef struct CollisionEngine
{
	int32_t mDefaultBodyPushAmount;
	bool mIsNullDividePlus;
	Vector2 mFixedGravity;
	int32_t* mCollisionGridPristine;
	int32_t* mCollisionGrid;
	/*std::shared_ptr<OePathNode> mLastNode;
	std::vector<std::shared_ptr<OePathNode>> mTempNodes;
	std::vector<std::shared_ptr<OePathNode>> mOpenNodes;
	std::vector<std::shared_ptr<OePathNode>> mClosedNodes;*/
	DrawRectangle* arr_debug_node_rectangles;
	DrawRectangle* arr_debug_many_rectangles;
	Rectangle mCollisionGridSize;
} CollisionEngine;

