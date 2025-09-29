#include "PathNode.h"

/*
#include "../math/OeMath.h"
#include "../utils/OeUtils.h"
#include "../../OeGlobalDefs.h"

#define TILE_SIZE GLOBAL_DEF_TILE_SIZE

void OePathNode::Setup(std::shared_ptr<OePathNode> givenParent, int gridX, int gridY, int targetX, int targetY)
{
	if (givenParent != nullptr)
	{
		mParent = givenParent;
		mParent->mChild = std::shared_ptr<OePathNode>(this);
	}

	mGridX = gridX;
	mGridY = gridY;

	mTargetX = targetX;
	mTargetY = targetY;

	if (givenParent != nullptr)
	{
		mPathDistance = GetPathDistance(givenParent);
	}
	else
	{
		mPathDistance = 0;
	}

	int diffX = OeMath::Abs(targetX - mGridX);
	int diffY = OeMath::Abs(targetY - mGridY);

	mTargetDistance = (diffX + diffY) * 10;

	mTotalDistance = mPathDistance + mTargetDistance;
}
float OePathNode::GetRealX()
{
	return mGridX * TILE_SIZE;
}
float OePathNode::GetRealY()
{
	return mGridY * TILE_SIZE;
}
int OePathNode::GetDirectionToHereX()
{
	return mGridX - mParent->mGridX;
}
int OePathNode::GetDirectionToHereY()
{
	return mGridY - mParent->mGridY;
}
int OePathNode::GetPathDistance(std::shared_ptr<OePathNode> parent)
{
	int addPathDistance = 0;

	if ((parent->mGridX == mGridX) || (parent->mGridY == mGridY))
	{
		addPathDistance = 10;
	}
	else
	{
		addPathDistance = 14;
	}

	return addPathDistance + parent->mPathDistance;
}
std::shared_ptr<OePathNode> OePathNode::GetByIndex(int index)
{
	std::shared_ptr<OePathNode> tempNode = std::shared_ptr<OePathNode>(this);
	for (int i = 0; i < index; i++)
	{
		tempNode = tempNode->mChild;
	}
	return tempNode;
}
bool OePathNode::IsEqualTo(std::shared_ptr<OePathNode> node)
{
	if ((node->mGridX == mGridX) && (node->mGridY == mGridY))
	{
		return true;
	}
	return false;
}
void OePathNode::Reset()
{
	mParent = nullptr;
	mChild = nullptr;

	mGridX = 0;
	mGridY = 0;

	mTargetX = 0;
	mTargetY = 0;

	mPathDistance = 0;
	mTargetDistance = 0;
	mTotalDistance = 0;
}
int OePathNode::Count()
{
	int counter = 0;
	std::shared_ptr<OePathNode> tempNode = std::shared_ptr<OePathNode>(this);
	while (tempNode != nullptr)
	{
		tempNode = tempNode->mChild;
		counter++;
	}
	return counter;
}
std::shared_ptr<OePathNode> OePathNode::GetRoot()
{
	std::shared_ptr<OePathNode> wantedNode = nullptr;
	std::shared_ptr<OePathNode> tempNode = std::shared_ptr<OePathNode>(this);

	while (wantedNode == nullptr)
	{
		if (tempNode->mParent == nullptr)
		{
			return tempNode;
		}
		else
		{
			if (tempNode->mParent->mParent == nullptr)
			{
				return tempNode;
			}
			else
			{
				tempNode = tempNode->mParent;
			}
		}
	}

	return nullptr;
}
std::shared_ptr<OePathNode> OePathNode::Obtain(std::shared_ptr<OePathNode> givenParent, int gridX, int gridY, int targetX, int targetY)
{
	std::shared_ptr<OePathNode> node = std::shared_ptr<OePathNode>(new OePathNode());
	node->Setup(givenParent, gridX, gridY, targetX, targetY);
	return node;
}*/