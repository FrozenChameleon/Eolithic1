#pragma once

#include "../utils/Macros.h"

typedef struct NodeMovingKit
{
	int32_t mType;
	int32_t mCurrentNode;
	bool mIsOnTarget;
	bool mBackwards;
	bool mIsComplete;
	bool mMoveContacts;
} NodeMovingKit;