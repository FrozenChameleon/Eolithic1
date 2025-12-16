#pragma once

#include "../math/Vector2.h"
#include "../render/Animation.h"

typedef struct SpriteBatch SpriteBatch;

typedef struct MovieImage
{
	int mScale;
	int mDepth;
	bool mIsAnimationSet;
	bool mIsPermanent;
	Vector2 mPosition;
	Vector2 mShake;
	Animation mAnimation;
	char mImage[EE_FILENAME_MAX];
	//std::vector<OeSheet*> mSheetsForAnimation;
} MovieImage;

void MovieImage_Init(MovieImage* mi, int scale, const char* image);
void MovieImage_Init2(MovieImage* mi, int scale, const char* baseImage, int frames, int flip);
void MovieImage_SetIsLoopingDisabled(MovieImage* mi, bool value);
void MovieImage_SetLoopPoint(MovieImage* mi, int value);
void MovieImage_Update(MovieImage* mi);
void MovieImage_SetIsPermanentImage(MovieImage* mi, bool value);
void MovieImage_DrawHud(MovieImage* mi, SpriteBatch* spriteBatch);