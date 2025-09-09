#pragma once

#include "../math/Vector2.h"
#include "../render/Color.h"

struct OeShaderProgram;

struct DrawActor
{
	int mExtraPasses;
	int mDefaultDrawState;
	int mDefaultDrawPhase;
	int mUniversalDepthOverride;
	float mRotation;
	float mOnScreenCheckMul;
	bool mIsFlipX;
	bool mIsFlipY;
	bool mIsBlendStateAdditive;
	bool mIsOnScreen;
	bool mIsUpdateDisabled;
	Vector2 mRenderPosition;
	Vector2 mLastRenderPosition;
	Vector2 mUniversalNudge;
	Vector2 mScale;
	Vector2 mOffset;
	Color mTintColor;
	OeShaderProgram* mShaderProgram;
};

