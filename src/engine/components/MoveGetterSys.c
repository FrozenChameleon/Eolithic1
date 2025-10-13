#include "MoveGetterSys.h"

/*
static bool DEBUG_IS_FORCED_MOVE;
static int DEBUG_FORCED_MOVE;
static int DEBUG_ID_COUNTER;

void OeComMoveGetterSys::SetupSystem()
{
	_mInitRoutine = InitRoutine;
	_mUpdateRoutine = UpdateRoutine;
}
int OeComMoveGetterSys::GetMove(OeComMoveGetter* data, OeRandom* random)
{
	if (data->mMoves.size() <= 1)
	{
		return 0;
	}

	if (DEBUG_IS_FORCED_MOVE && !data->mDebugDoNotUseMoveForcedByTool)
	{
		return DEBUG_FORCED_MOVE;
	}

	if (data->mIsFixedOrder)
	{
		int fixedMoveToReturn = data->mFixedOrderMoves[data->mMovesCounter];
		data->mMovesCounter++;
		if (data->mMovesCounter >= data->mFixedOrderMoves.size())
		{
			data->mMovesCounter = 0;
		}
		return fixedMoveToReturn;
	}

	int currentMove = -1;
	bool good;
	int counter = 0;
	do //get the new one
	{
		if (counter == 100)
		{
			OeLogger::LogInformation(data->mDebugName + " ran out of moves, resetting queue");
			OeUtils::ResetArrayToNegativeOneAsInt(data->mLastMoves);
		}
		if (counter >= 1000)
		{
			break;
		}
		currentMove = OeRandom::NextInt(random, data->mMoves.size());
		good = true;
		for (int i = 0; i < data->mLastMoves.size(); i++)
		{
			if (data->mLastMoves[i] == currentMove)
			{
				good = false;
			}
		}
		for (int i = 0; i < data->mConstraints.size(); i++)
		{
			if (currentMove == data->mConstraints[i])
			{
				good = false;
			}
		}
		if (currentMove == data->mLastMove)
		{
			good = false;
		}
		counter++;
	} while (!good);

	for (int i = data->mLastMoves.size() - 1; i > 0; i--) //push the old ones
	{
		data->mLastMoves[i] = data->mLastMoves[i - 1];
		data->mLastMoves[i - 1] = -1;
	}
	data->mLastMoves[0] = currentMove;

	data->mMovesCounter++;

	data->mConstraints.clear();

	data->OverflowCheck();

	data->mLastMove = currentMove;

	return currentMove;
}
void OeComMoveGetterSys::InitRoutine(OeEntity owner, OeComMoveGetter* data)
{
	data->mMoves = std::vector<std::string>();
	data->mConstraints = std::vector<int>();
	data->mDebugMyId = DEBUG_ID_COUNTER;
	DEBUG_ID_COUNTER++;
	data->mLastMove = -1;
	data->mMoves.clear();
	data->mConstraints.clear();
}
void OeComMoveGetterSys::UpdateRoutine(OeEntity owner, OeComMoveGetter* data)
{
}
*/