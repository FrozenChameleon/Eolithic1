#include "MovieImage.h"

#include "../utils/Utils.h"
#include "../render/Texture.h"
#include "../render/Color.h"
#include "../render/Sheet.h"
//#include "MovieSheetsTool.h"

void MovieImage_Init(MovieImage* mi, int scale, const char* image)
{
	Utils_memset(mi, 0, sizeof(MovieImage));
	mi->mScale = scale;
	Utils_strlcpy(mi->mImage, image, EE_FILENAME_MAX);
}
void MovieImage_Init2(MovieImage* mi, int scale, const char* baseImage, int frames, int flip)
{
	Utils_memset(mi, 0, sizeof(MovieImage));

	mi->mScale = scale;

	//TODO C99
	/*std_vector<std_string> images = std_vector<std_string>();
	Animation_CreateAnimationStringArray(images, baseImage, frames, OeUtils_GetAmountOfDigits(frames));

	for (int i = 0; i < frames; i += 1)
	{
		OeResource<OeTexture*>* resource = OeResourceManagers_MovieTextureManager.GetResource(images[i]);
		if (resource == nullptr)
		{
			mSheetsForAnimation.push_back(OeSheet_GetDefaultSheet());
		}
		else
		{
			mSheetsForAnimation.push_back(OeMovieSheetsTool_GetSheet(images[i]));
		}
	}

	Animation_Init(&mi->mAnimation, &mSheetsForAnimation, flip);*/

	mi->mIsAnimationSet = true;
}

void MovieImage_SetIsLoopingDisabled(MovieImage* mi, bool value)
{
	if (mi->mIsAnimationSet)
	{
		mi->mAnimation.mIsLoopingDisabled = value;
	}
}
void MovieImage_SetLoopPoint(MovieImage* mi, int value)
{
	mi->mAnimation.mAnimationLoopPoint = value;
}
void MovieImage_Update(MovieImage* mi)
{
	if (mi->mIsAnimationSet)
	{
		Animation_Update(&mi->mAnimation);
	}
}
void MovieImage_SetIsPermanentImage(MovieImage* mi, bool value)
{
	mi->mIsPermanent = value;
}
void MovieImage_DrawHud(MovieImage* mi, SpriteBatch* spriteBatch)
{
	/*Sheet tempSheet = Sheet();
	Sheet* sheet = NULL;
	if (mIsAnimationSet)
	{
		sheet = OeAnimation_GetCurrentSheet(&mAnimation);
	}
	else
	{
		OeResource<OeTexture*>* resource = OeResourceManagers_MovieTextureManager.GetResource(mImage);
		if (resource == nullptr)
		{
			sheet = OeSheet_GetDefaultSheet();
		}
		else
		{
			tempSheet = OeSheet(resource);
			sheet = &tempSheet;
		}
	}
	Sheet_Draw(sheet, spriteBatch, OeColors_WHITE, mDepth, false, false, nullptr, mPosition + mShake, Vector2(mScale, mScale), 0, false, false, Vector2_Zero);*/
}
