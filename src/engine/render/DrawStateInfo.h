#pragma once

#include "../math/Vector2.h"

typedef struct ShaderProgram ShaderProgram;

typedef struct DrawStateInfo
{
	int32_t mState;
	int32_t mCurrentPhase;
	int32_t mDepth;
	float mRotation;
	Vector2 mNudge;
	ShaderProgram* mShader;
} DrawStateInfo;

