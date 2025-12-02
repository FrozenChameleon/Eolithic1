#pragma once

/*
#include <memory>

struct OePathNode final
{
	std::shared_ptr<OePathNode> mParent;
	std::shared_ptr<OePathNode> mChild;

	int mTargetX;
	int mTargetY;

	int mGridX;
	int mGridY;

	int mPathDistance;
	int mTargetDistance;
	int mTotalDistance;

	void Setup(std::shared_ptr<OePathNode> givenParent, int32_t gridX, int32_t gridY, int32_t targetX, int32_t targetY);
	float GetRealX();
	float GetRealY();
	int GetDirectionToHereX();
	int GetDirectionToHereY();
	int GetPathDistance(std::shared_ptr<OePathNode> parent);
	std::shared_ptr<OePathNode> GetByIndex(int index);
	bool IsEqualTo(std::shared_ptr<OePathNode> node);
	void Reset();
	int Count();
	std::shared_ptr<OePathNode> GetRoot();
	static std::shared_ptr<OePathNode> Obtain(std::shared_ptr<OePathNode> givenParent, int32_t gridX, int32_t gridY, int32_t targetX, int32_t targetY);
};

*/