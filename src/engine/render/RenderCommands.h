#pragma once

#include "stdint.h"
#include "../render/Color.h"
#include "../math/Vector2.h"
#include "../math/Rectangle.h"
#include "../render/Texture.h"
#include "../render/ShaderProgram.h"

typedef struct RenderCommandSheet
{
	uint8_t mType;
	uint8_t mDepth;
	bool mFlipX;
	bool mFlipY;
	bool mIsRectangle;
	bool mIsInterpolated;
	uint16_t mPadding1;
	int32_t mBlendState;
	int32_t mExtraPasses;
	float mRotation;
	Color mColor;
	Vector2 mPosition;
	Vector2 mLastPosition;
	Vector2 mOrigin;
	Vector2 mScale;
	Rectangle mSourceRectangle;
	Rectangle mDestinationRectangle;
	Texture* mTexture;
	ShaderProgram* mShaderProgram;
} RenderCommandSheet;

/*
struct OeRenderCommandString
{
	uint8_t mType;
	uint8_t mDepth;
	bool mIsInterpolated;
	bool mIsLockedToInt;
	bool mDoNotReplaceFont;
	uint8_t mPadding1;
	uint16_t mPadding2;
	int16_t mAlignmentX;
	int16_t mAlignmentY;
	Vector2 mPosition;
	Vector2 mLastPosition;
	Color mColor;
	OeBmFont* mFont;
	std::string* mString;
};

struct OeRenderCommandManyRectangle
{
	uint8_t mType;
	uint8_t mDepth;
	uint16_t mPadding1;
	std::vector<OeDrawRectangle>* mManyRectangles;
	OeTexture* mTexture;
};

struct OeRenderCommandTileLayer
{
	uint8_t mType;
	uint8_t mDepth;
	uint8_t mLayer;
	uint8_t mPadding1;
	int32_t mX1;
	int32_t mX2;
	int32_t mY1;
	int32_t mY2;
	Color mColor;
	Rectangle mTileDataBounds;
	std::vector<OeTile*>* mTileData;
	OeTexture* mTexture;
};
*/