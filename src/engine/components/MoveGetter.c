#include "MoveGetter.h"

#include "../utils/Utils.h"

void MoveGetter_Setup(MoveGetter* mg, const char* name, int32_t movesToRemember)
{
	/*
	mg->mDebugName = name;
	mg->mLastMoves = std_vector<int32_t>(movesToRemember);
	OeUtils_ResetArrayToNegativeOneAsInt(mLastMoves);*/
}
void MoveGetter_SetAsFixedOrder(MoveGetter* mg, const int32_t* order)
{
	/*
	mIsFixedOrder = true;
	mFixedOrderMoves = order;*/
}
void MoveGetter_AddMove(MoveGetter* mg, const char* name)
{
	//mMoves.push_back(name);
}
void MoveGetter_OverflowCheck(MoveGetter* mg)
{
	/*
	if (mLastMoves.size() < mMoves.size())
	{
		return;
	}

	bool reset = true;
	for (int32_t i = 0; i < mLastMoves.size(); i += 1)
	{
		if (mLastMoves[i] == -1)
		{
			reset = false;
		}
	}
	if (reset)
	{
		mMovesCounter = 0;
		OeUtils_ResetArrayToNegativeOneAsInt(mLastMoves);
	}*/
}
int32_t MoveGetter_GetLastMove(MoveGetter* mg)
{
	return 0;
	//return mLastMoves[0];
}
void MoveGetter_AddConstraint(MoveGetter* mg, int32_t value)
{
	//mConstraints.push_back(value);
}