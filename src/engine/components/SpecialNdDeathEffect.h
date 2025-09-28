#pragma once

#include "../utils/Timer.h"
#include "../render/Sheet.h"

typedef struct Sheet Sheet;

typedef struct SpecialNdDeathEffect
{
	int mParticleDirectionX[3];
	int mParticleDirectionY[3];
	int mParticleDistance[3];
	int mParticleJitter[3];
	float mInitialPositionX;
	float mInitialPositionY;
	float mSectionWidth;
	float mSectionHeight;
	Sheet* mSheetReference;
	Timer mTimer;
} SpecialNdDeathEffect;

