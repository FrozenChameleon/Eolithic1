#pragma once

#include "../utils/Macros.h"

enum
{
	BACK_AND_FORTH = 0,
	END_TO_BEGIN = 1,
	STOP = 2,
	END_TO_FIRST_NODE = 3
};

typedef struct NodeMovingKit
{
	int mType;
	int mCurrentNode;
	bool mIsOnTarget;
	bool mBackwards;
	bool mIsComplete;
	bool mMoveContacts;
} NodeMovingKit;

/*
void Setup(OeEntity owner, int32_t type, bool moveContacts);
bool IsOnTarget();
int GetCurrentNode();
bool IsComplete();
int GetDistanceToNextNodeY(OeEntity owner);
void HandleNodeMoving(OeEntity owner);
void HandleNodeMoving(OeEntity owner, float speed);*/