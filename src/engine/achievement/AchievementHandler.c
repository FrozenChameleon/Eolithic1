/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "AchievementHandler.h"

#include "../../third_party/stb_ds.h"

static int32_t _mCertifyCrawlingCounter;
static bool _mIsUsingMask;
static bool _mIsNotFirstUpdate;
static bool _mIsUpdateSuppressed;
static Achievement* _mDynamicAchievements;

void AchievementHandler_SetIsUpdateSuppressed(bool value)
{
	_mIsUpdateSuppressed = value;
}
void AchievementHandler_DebugUnlockNextAchievement()
{
	int32_t len = AchievementHandler_GetAchievementsLength();
	for (int32_t i = 0; i < len; i += 1)
	{
		Achievement* achievement = &_mDynamicAchievements[i];
		if (!achievement->mIsUnlocked)
		{
			Achievement_UnlockAchievement(false, achievement, i);
			return;
		}
	}
}
void AchievementHandler_SetToUseMask()
{
	_mIsUsingMask = true;
}
void AchievementHandler_Update()
{

}
Achievement* AchievementHandler_GetAchievements()
{
	return _mDynamicAchievements;
}
Achievement* AchievementHandler_GetAchievement(int32_t i)
{
	return &_mDynamicAchievements[i];
}
int32_t AchievementHandler_GetAchievementsLength()
{
	return arrlen(_mDynamicAchievements);
}
int32_t AchievementHandler_GetAmountOfAchievements()
{
	return AchievementHandler_GetAchievementsLength();
}
void AchievementHandler_AddAchievement(bool isHidden, const char* name, const char* description, const char* lockedDescription, const char* image, bool (*condition)())
{
	int32_t current = AchievementHandler_GetAchievementsLength();
	//std::string nameToUse = name;
	//std::string descriptionToUse = description;
	if (_mIsUsingMask)
	{
		//TODO
		//nameToUse = "ACHIEVEMENT_" + std::to_string(current) + "_NAME";
		//descriptionToUse = "ACHIEVEMENT_" + std::to_string(current) + "_DESCRIPTION";
	}
	Achievement achievement;
	Achievement_Init(&achievement, condition, name, description, lockedDescription, image, isHidden);
	arrput(_mDynamicAchievements, achievement);
}
void AchievementHandler_Reset()
{
	int32_t len = AchievementHandler_GetAchievementsLength();
	for (int32_t i = 0; i < len; i += 1)
	{
		_mDynamicAchievements[i].mIsUnlocked = false;
	}
}
int32_t AchievementHandler_GetAmountOfAchievementsComplete()
{
	int32_t currentAchievementsDone = 0;

	int32_t len = AchievementHandler_GetAchievementsLength();
	for (int32_t i = 0; i < len; i += 1)
	{
		if (_mDynamicAchievements[i].mIsUnlocked)
		{
			currentAchievementsDone += 1;
		}
	}

	return currentAchievementsDone;
}
int32_t AchievementHandler_GetIntegerPercentage()
{
	float temp = (float)AchievementHandler_GetAmountOfAchievementsComplete() / AchievementHandler_GetAmountOfAchievements();
	float value = temp * 100.0f;
	return (int32_t)temp;
}