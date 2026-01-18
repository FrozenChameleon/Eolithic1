#include "NodeMovingKit.h"

#include "../core/Func.h"
#include "../math/Math.h"

/*
void OeComNodeMovingKit::Setup(OeEntity owner, int32_t type, bool moveContacts)
{
	mType = type;
	mMoveContacts = moveContacts;
	if (!Is_NodesPresent(owner))
	{
		mIsComplete = true;
	}
	else
	{
		mIsComplete = false;
	}
}
bool OeComNodeMovingKit::IsOnTarget()
{
	return mIsOnTarget;
}
int32_t OeComNodeMovingKit::GetCurrentNode()
{
	return mCurrentNode;
}
bool OeComNodeMovingKit::IsComplete()
{
	return mIsComplete;
}
int32_t OeComNodeMovingKit::GetDistanceToNextNodeY(OeEntity owner)
{
	if (mCurrentNode >= Get_AmountOfNodes(owner))
	{
		return -1;
	}

	Point point = Get_Node(owner, mCurrentNode);

	return static_cast<int32_t>(OeMath::Abs(Get_Y(owner) - point.Y));
}
void OeComNodeMovingKit::HandleNodeMoving(OeEntity owner)
{
	HandleNodeMoving(owner, 1);
}
void OeComNodeMovingKit::HandleNodeMoving(OeEntity owner, float speed)
{
	mIsOnTarget = false;

	if (mIsComplete)
	{
		return;
	}

	if (mCurrentNode >= 0)
	{
		Point point = Get_Node(owner, mCurrentNode);

		if (Do_MoveSomewhere(owner, point.X, point.Y, speed))
		{
			mIsOnTarget = true;

			if (!mBackwards)
			{
				mCurrentNode++;
			}
			else
			{
				mCurrentNode--;
			}

			if (mCurrentNode > Get_AmountOfNodes(owner) - 1)
			{
				if (mType == BACK_AND_FORTH)
				{
					mBackwards = true;
					mCurrentNode = Get_AmountOfNodes(owner) - 1;
				}
				else if (mType == END_TO_BEGIN)
				{
					mCurrentNode = -1;
				}
				else if (mType == STOP)
				{
					mIsComplete = true;
				}
				else if (mType == END_TO_FIRST_NODE)
				{
					mCurrentNode = 0;
				}
			}
		}
		if (mMoveContacts)
		{
			//Do_MoveAllThings(contacts, point.X, point.Y, speed);
		}
	}
	else
	{
		if (Do_MoveSomewhere(owner, Get_InitialX(owner), Get_InitialY(owner), speed))
		{
			mIsOnTarget = true;

			mCurrentNode = 0;
			mBackwards = false;
		}
		if (mMoveContacts)
		{
			//Do_MoveAllThings(contacts, Get_InitialX(owner), Get_InitialY(owner), speed);
		}
	}
}
*/