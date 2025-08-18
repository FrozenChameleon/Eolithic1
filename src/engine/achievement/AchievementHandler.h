/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "Achievement.h"

void AchievementHandler_SetIsUpdateSuppressed(bool value);
void AchievementHandler_DebugUnlockNextAchievement();
void AchievementHandler_SetToUseMask();
void AchievementHandler_Update();
Achievement* AchievementHandler_GetAchievements();
int32_t AchievementHandler_GetAchievementsLength();
Achievement* AchievementHandler_GetAchievement(int32_t i);
int32_t AchievementHandler_GetAmountOfAchievements();
void AchievementHandler_AddAchievement(bool isHidden, const char* name, const char* description, const char* lockedDescription, const char* image, bool (*condition)());
void AchievementHandler_Reset();
int32_t AchievementHandler_GetAmountOfAchievementsComplete();
int32_t AchievementHandler_GetIntegerPercentage();
