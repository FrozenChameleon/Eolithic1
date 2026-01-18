#pragma once

#include "Color.h"
#include "BlendState.h"
#include "../math/Vector2.h"
#include "../math/Rectangle.h"
#include "../render/DrawRectangle.h"
#include "../font/BmFont.h"
#include "../leveldata/Tile.h"
#include "../render/ShaderProgram.h"

typedef struct DrawInstance
{
	int32_t mType;
	int32_t mAlignmentX;
	int32_t mAlignmentY;
	int32_t mX1;
	int32_t mX2;
	int32_t mY1;
	int32_t mY2;
	int32_t mLayer;
	int32_t mExtraPasses;
	int32_t mDepth;
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
	Texture* mTexture;
	BmFont* mFont;
	ShaderProgram* mShaderProgram;
	BlendState mBlendState;
	Tile* mTileData;
	Rectangle mTileDataBounds;
	DrawRectangle* mManyRectangles;
	bool mDoNotReplaceFont;
} DrawInstance;