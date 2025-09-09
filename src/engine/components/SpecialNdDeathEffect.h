#pragma once

#include "../utils/Timer.h"

struct OeSheet;

struct SpecialNdDeathEffect
{
	int mParticleDirectionX[3];
	int mParticleDirectionY[3];
	int mParticleDistance[3];
	int mParticleJitter[3];
	float mInitialPositionX;
	float mInitialPositionY;
	float mSectionWidth;
	float mSectionHeight;
	OeSheet* mSheetReference;
	Timer mTimer;
};

