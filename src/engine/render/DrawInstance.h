#pragma once

#include "Color.h"
#include "BlendState.h"
#include "../math/Vector2.h"
#include "../math/Rectangle.h"
#include "../render/DrawRectangle.h"

typedef struct DrawInstance
{
	int mType;
	int mAlignmentX;
	int mAlignmentY;
	int mX1;
	int mX2;
	int mY1;
	int mY2;
	int mLayer;
	int mExtraPasses;
	int mDepth;
	float mRotation;
	bool mIsInterpolated;
	bool mIsRectangle;
	bool mFlipX;
	bool mFlipY;
	bool mIsCenteredX;
	bool mIsCenteredY;
	bool mIsLockedToInt;
	const char* mString;
	const char* mStrings;
	Vector2 mPosition;
	Vector2 mLastPosition;
	Vector2 mOrigin;
	Vector2 mScale;
	Rectangle mDestinationRectangle;
	Rectangle mSourceRectangle;
	Color mColor;
	Texture2D* mTexture;
	BmFont* mFont;
	ShaderProgram* mShaderProgram;
	BlendState mBlendState;
	Tile* mTileData;
	Rectangle mTileDataBounds;
	DrawRectangle* mManyRectangles;
	bool mDoNotReplaceFont;
};