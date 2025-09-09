#pragma once

#include "../math/Point.h"

#define MOVE_GETTER_MAX_LEN 20

struct MoveGetter
{
	int mLastMove;
	int mMovesCounter;
	bool mIsFixedOrder;
	int mFixedOrderMoves[MOVE_GETTER_MAX_LEN];
	int mLastMoves[MOVE_GETTER_MAX_LEN];
	const char* mMoves[MOVE_GETTER_MAX_LEN];
	int mConstraints[MOVE_GETTER_MAX_LEN];
	int mDebugMyId;
	int mDebugHeight;
	bool mDebugIsShowing;
	bool mDebugDoNotUseMoveForcedByTool;
	const char* mDebugName;
	Point mDebugFirstWindowPosition;
};

void MoveGetter_Setup(MoveGetter* mg, const char* name, int movesToRemember);
void MoveGetter_SetAsFixedOrder(MoveGetter* mg, const int* order);
void MoveGetter_AddMove(MoveGetter* mg, const char* name);
void MoveGetter_OverflowCheck(MoveGetter* mg);
int MoveGetter_GetLastMove(MoveGetter* mg);
void MoveGetter_AddConstraint(MoveGetter* mg, int value);