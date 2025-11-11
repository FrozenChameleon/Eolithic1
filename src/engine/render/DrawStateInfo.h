#pragma once

#include "../math/Vector2.h"

typedef struct ShaderProgram ShaderProgram;

typedef struct DrawStateInfo
{
	int mState;
	int mCurrentPhase;
	int mDepth;
	float mRotation;
	Vector2 mNudge;
	ShaderProgram* mShader;
} DrawStateInfo;

