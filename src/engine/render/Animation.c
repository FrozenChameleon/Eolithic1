/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Animation.h"

#include "../../third_party/stb_ds.h"
#include "AnimationInfo.h"
#include "../utils/Logger.h"
#include "../utils/Utils.h"
#include "Sheet.h"
#include "../math/Math.h"
#include "../utils/MString.h"
#include "../utils/IStrings.h"

static AnimationInfo* _mDynamicAnimationInfo;
static struct { char* key;  char** value; }*_mAnimationStringMap;
static struct { char* key;  char* value; }*_mConversionMap;
static struct { char* key; Sheet* value; }*_mAnimationSheetMap;
static char** _mDynamicDummyAnimationNames;
static Sheet* _mDynamicDummyAnimationSheets;

//private
static void Animation_SetupSheets(Animation* data, int flipTimer)
{
	data->mIsSuppressed = true;

	Timer_Reset(&data->mFlipTimer);
	data->mFlipTimer.mLimit = flipTimer;

	data->mInitialFlipTimerLimit = data->mFlipTimer.mLimit;

	data->mFrameTimer.mLimit = data->mSheetsLen - 1;
}
static const char** Animation_GetAnimationSheetNames(const char* animation)
{
	ptrdiff_t index = shgeti(_mAnimationStringMap, animation);
	if (index >= 0)
	{
		return _mAnimationStringMap[index].value;
	}

	return NULL;
}
static char Animation_GetNumber(int i)
{
	switch (i)
	{
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	}
	return 'N';
}

void Animation_DebugTest()
{
	Animation_BuildAnimations();
}

//public
void Animation_Init(Animation* data, const char* spriteSheet, int flipTimer)
{
	/*
	Utils_memset(data, 0, sizeof(Animation));

	if (spriteSheet.size() <= 0)
	{
		return;
	}

	data->mSheets = GetAnimationSheets(spriteSheet);
	if (data->GetSheets().size() > 0)
	{
		SetupSheets(data, flipTimer);
	}
	else
	{
		OeLogger_LogError("Unable to setup animation: " + spriteSheet);
	}
	*/
}
void Animation_Init2(Animation* data, Sheet* sheets, int sheetsLen, int flipTimer)
{
	Utils_memset(data, 0, sizeof(Animation));
	data->mSheets = sheets;
	data->mSheetsLen = sheetsLen;
	Animation_SetupSheets(data, flipTimer);
}
const char* Animation_GetCurrentSheetName(Animation* data)
{
	return NULL;
	/*
	return GetCurrentSheet(data)->mSheetName;
	*/
}
bool Animation_Update(Animation* data)
{
	if (data->mIsUpdateDisabled)
	{
		return true;
	}

	if (!data->mIsSuppressed)
	{
		if (Timer_Update(&data->mFlipTimer))
		{
			if (!data->mIsGoingInReverse)
			{
				data->mFrameTimer.mCurrent += 1;
			}
			else
			{
				data->mFrameTimer.mCurrent -= 1;
			}
		}
	}
	else
	{
		data->mIsSuppressed = false;
	}

	if (((data->mFrameTimer.mCurrent > data->mFrameTimer.mLimit) && !data->mIsGoingInReverse) || ((data->mFrameTimer.mCurrent < 0) && data->mIsGoingInReverse))
	{
		if (!data->mIsLoopingDisabled)
		{
			if (data->mAnimationLoopPoint != 0)
			{
				data->mFrameTimer.mCurrent = data->mAnimationLoopPoint;
			}
			else
			{
				if (data->mIsGoingInReverse)
				{
					data->mFrameTimer.mCurrent = data->mFrameTimer.mLimit;
				}
				else
				{
					data->mFrameTimer.mCurrent = 0;
				}
			}
		}
		else
		{
			if (data->mIsGoingInReverse)
			{
				data->mFrameTimer.mCurrent = 0;
			}
			else
			{
				data->mFrameTimer.mCurrent = data->mFrameTimer.mLimit;
			}

			data->mIsAnimationComplete = true;
		}
	}

	return data->mIsAnimationComplete;
}
void Animation_ResetAnimation(Animation* data)
{
	data->mIsReverse = false;

	data->mIsSuppressed = true;

	data->mIsAnimationComplete = false;

	data->mFrameTimer.mCurrent = 0;

	Timer_Reset(&data->mFlipTimer);
	data->mFlipTimer.mLimit = data->mInitialFlipTimerLimit;
}
Sheet* Animation_GetCurrentSheet(Animation* data)
{
	return NULL;
	/*
	int counter = data->mFrameTimer.mCurrent;
	if (data->mIsReverse)
	{
		counter = data->mFrameTimer.mLimit - counter;
	}

	int sheetsSize = data->GetSheets().size();
	if ((sheetsSize <= 0) || (counter > sheetsSize - 1))
	{
		return OeSheet_GetDefaultSheet();
	}

	return data->GetSheets()[counter];*/
}
int Animation_DigitsAtEnd(const char* sheetName, int sheetNameLength)
{
	int numberOfDigits = 0;
	for (int i = (sheetNameLength - 1); i >= 0; i -= 1) // See how many digits there are at the end...
	{
		if (Utils_CharIsDigit(sheetName[i]))
		{
			numberOfDigits += 1;
		}
		else
		{
			return numberOfDigits; // IMMEDIATELY stop once we detect the base.
		}
	}
	return numberOfDigits;
}
void Animation_CheckForAnimation(const char* textureName)
{
	const char* sheetName = textureName;
	int nameLength = Utils_strlen(sheetName);

	char lastDigit = sheetName[nameLength - 1];
	if (!Utils_CharIsDigit(lastDigit))
	{
		return;
	}

	int numberOfDigits = Animation_DigitsAtEnd(sheetName, nameLength);
	if (numberOfDigits == nameLength)
	{
		return;
	}
	
	MString* baseName = MString_CreateFromSubString(sheetName, 0, nameLength - numberOfDigits); //We have our base name, time to find out how many frames there are.
	bool isStart = (lastDigit == '0');
	ptrdiff_t animationInfoLen = arrlen(_mDynamicAnimationInfo);
	for (int i = 0; i < animationInfoLen; i += 1)
	{
		AnimationInfo* existingInfo = &_mDynamicAnimationInfo[i];
		if (Utils_StringEqualTo(existingInfo->mBaseName, baseName->str))
		{
			if (isStart)
			{
				existingInfo->mHasStart = true;
			}
			existingInfo->mFrames += 1;
			MString_Dispose(baseName);
			return;
		}
	}

	AnimationInfo newInfo = { 0 };
	newInfo.mSheetName = IStrings_GlobalGet(sheetName);
	newInfo.mBaseName = IStrings_GlobalGet(baseName->str);
	newInfo.mNumberOfDigits = numberOfDigits;
	newInfo.mFrames += 1;
	if (isStart)
	{
		newInfo.mHasStart = true;
	}
	arrput(_mDynamicAnimationInfo, newInfo);

	MString_Dispose(baseName);
}
void Animation_BuildAnimations()
{
	shfree(_mAnimationStringMap);
	shfree(_mConversionMap);
	shfree(_mAnimationSheetMap);
	arrfree(_mDynamicAnimationInfo);

	IStringArray* sheets = Sheet_CreateListOfSheetNames();
	int32_t sheetsLen = IStringArray_Length(sheets);
	for (int i = 0; i < sheetsLen; i += 1)
	{
		const char* sheetName = IStringArray_Get(sheets, i);
		Animation_CheckForAnimation(sheetName);
	}
	IStringArray_Dispose(sheets);

	ptrdiff_t animationInfoLen = arrlen(_mDynamicAnimationInfo);
	for (int i = 0; i < animationInfoLen; i += 1)
	{
		AnimationInfo* info = &_mDynamicAnimationInfo[i];
		if (info->mHasStart)
		{
			Animation_AddToAnimationMap(info->mBaseName, info->mSheetName, info->mFrames, info->mNumberOfDigits);
		}
		else
		{
			Logger_LogWarning("Animation is incorrectly setup:");
			Logger_LogWarning(info->mSheetName);
		}
	}
}
void Animation_AddToAnimationMap(const char* baseName, const char* sheetName, int frames, int digits)
{
	IStringArray* sheetNames = IStringArray_Create();
	Animation_CreateAnimationStringArray(sheetNames, baseName, frames, digits);
	shput(_mConversionMap, baseName, sheetName);
	shput(_mAnimationStringMap, sheetName, sheetNames);
}
void Animation_CreateAnimationStringArray(IStringArray* listToAddTo, const char* baseName, int frames, int digits)
{
	MString* stringBuilder = MString_Create(baseName);

	for (int i = 0; i < digits; i += 1)
	{
		stringBuilder = MString_AddAssignChar(stringBuilder, '0');
	}

	for (int i = 0; i < frames; i += 1)
	{
		int currentNumber = i;

		double placeAsDouble = Math_pow(10, digits - 1);
		int place = (int)placeAsDouble;
		do
		{
			for (int j = 0; j < digits; j += 1)
			{
				int number = currentNumber / place;
				stringBuilder->str[stringBuilder->len - digits + j] = Animation_GetNumber(number);
				currentNumber -= number * place;
				place /= 10;
			}
		} while (place != 0);
		IStringArray_Add(listToAddTo, stringBuilder->str);
	}

	MString_Dispose(stringBuilder);
}
const char* Animation_GetConvertedName(const char* baseName)
{
	return shget(_mConversionMap, baseName);
}
const char** Animation_GetAnimationSheets(const char* animation)
{
	return NULL;
	/*if (_mAnimationSheetMap.count(animation))
	{
		return &_mAnimationSheetMap[animation];
	}

	const std_vector<std_string>& sheetNames = GetAnimationSheetNames(animation);
	if (sheetNames.size() > 0)
	{
		std_vector<OeSheet*> sheets = std_vector<OeSheet*>();
		for (int i = 0; i < sheetNames.size(); i += 1)
		{
			sheets.push_back(OeSheet_GetSheet(sheetNames[i]));
		}
		_mAnimationSheetMap[animation] = sheets;
		return GetAnimationSheets(animation);
	}

	return &_mDummyAnimationSheets;*/
}
