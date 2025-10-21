/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../utils/Macros.h"
#include "../math/Vector2.h"
#include "../utils/MString.h"
#include "../io/BufferReader.h"

typedef struct Particle
{
	bool mIsBlendStateAdditive;
	int mExtraPasses;

	int mMiscTTLMin;
	int mMiscTTLMax;
	bool mMiscDoesDieOffscreen;

	Vector2 mOffsetMinimum;
	Vector2 mOffsetMaximum;
	bool mOffsetIsNegativeX;
	bool mOffsetIsNegativeY;

	bool mFlickerIsFlicker;
	int mFlickerMinimumStart;
	int mFlickerMaximumStart;
	int mFlickerMinimumSpeed;
	int mFlickerMaximumSpeed;

	Vector2 mConstantMinimum;
	Vector2 mConstantMaximum;
	bool mConstantIsNegativeX;
	bool mConstantIsNegativeY;
	bool mConstantIsFluctuating;
	int mConstantFluctuateIntervalMin;
	int mConstantFluctuateIntervalMax;

	Vector2 mCurveTotalMinimum;
	Vector2 mCurveTotalMaximum;
	Vector2 mCurveMinimumIncreaseRate;
	Vector2 mCurveMaximumIncreaseRate;
	bool mCurveIsOppositeX;
	bool mCurveIsOppositeY;
	bool mCurveIsNegativeX;
	bool mCurveIsNegativeY;
	bool mCurveIsFluctuating;
	bool mCurveFluctuateKeepSpeed;
	bool mCurveFluctuateResetRate;
	bool mCurveFluctuateResetTotal;
	int mCurveFluctuateIntervalMin;
	int mCurveFluctuateIntervalMax;

	int mTextureDepth;
	MString* mTextureName;
	int mTextureFlipSpeed;
	bool mTextureIsAnimation;
	int mScaler;
	int mTextureLoopPoint;
	bool mTextureDoesAnimationStop;

	int mPreviewAmount;
	int mPreviewInterval;
} Particle;

Particle* Particle_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br);
void Particle_Dispose(Particle* particle);
