/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../math/Vector2.h"
#include "../math/Point.h"
#include "../render/Color.h"
#include "../utils/Timer.h"
#include "../render/Animation.h"
#include "Particle.h"
#include "../render/Sheet.h"
#include "../render/ShaderProgram.h"
#include "../utils/MString.h"

typedef struct ParticleInstance
{
	int mCounter;
	int mFlickerStart;
	int mInfluencedDepth;
	float mInfluencedRotation;
	bool mAttachedThingFollowFlipX;
	bool mIsFlickering;
	bool mFlipX;
	bool mFlipY;
	bool mIsComplete;
	MString* mName;
	Point mAttachedThingOffset;
	Point mInfluencedDirection;
	Vector2 mCurveMaximum;
	Vector2 mCurrentCurveRate;
	Vector2 mCurveRate;
	Vector2 mOffset;
	Vector2 mLastRenderPosition;
	Vector2 mPosition;
	Vector2 mConstant;
	Color mInfluencedColor;
	Timer mTimerConstantFluctuate;
	Timer mTimerCurveFluctuate;
	Timer mTimerTimeToLive;
	Timer mTimerFlicker;
	Animation mAnimation;
	int mAttachedEntity;
	void* mAttachedThing;
	Particle* mParticle;
	Sheet* mSheet;
	ShaderProgram* mShaderProgram;
} ParticleInstance;

ParticleInstance* ParticleInstance_Dummy();
const ParticleInstance* ParticleInstance_Empty();