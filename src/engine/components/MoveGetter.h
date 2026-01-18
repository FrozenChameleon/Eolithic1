#pragma once

#include "../math/Point.h"

#define MOVE_GETTER_MAX_LEN 20

typedef struct MoveGetter
{
	int32_t mLastMove;
	int32_t mMovesCounter;
	bool mIsFixedOrder;
	int32_t mFixedOrderMoves[MOVE_GETTER_MAX_LEN];
	int32_t mLastMoves[MOVE_GETTER_MAX_LEN];
	const char* mMoves[MOVE_GETTER_MAX_LEN];
	int32_t mConstraints[MOVE_GETTER_MAX_LEN];
	int32_t mDebugMyId;
	int32_t mDebugHeight;
	bool mDebugIsShowing;
	bool mDebugDoNotUseMoveForcedByTool;
	const char* mDebugName;
	Point mDebugFirstWindowPosition;
} MoveGetter;

void MoveGetter_Setup(MoveGetter* mg, const char* name, int32_t movesToRemember);
void MoveGetter_SetAsFixedOrder(MoveGetter* mg, const int32_t* order);
void MoveGetter_AddMove(MoveGetter* mg, const char* name);
void MoveGetter_OverflowCheck(MoveGetter* mg);
int32_t MoveGetter_GetLastMove(MoveGetter* mg);
void MoveGetter_AddConstraint(MoveGetter* mg, int32_t value);