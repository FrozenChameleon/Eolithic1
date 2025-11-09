/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Achievement.h"

#include "../utils/Macros.h"
#include "../utils/Utils.h"
#include "../utils/Logger.h"
#include "../service/Service.h"
#include "../globals/Globals.h"
#include "../utils/Cvars.h"

void Achievement_Init(Achievement* achievement, bool (*condition)(), const char* name, const char* description, const char* lockedDescription, const char* image, bool isHidden)
{
	Utils_memset(achievement, 0, sizeof(Achievement));

	achievement->mIsCertified = false;
	achievement->mIsHidden = isHidden;
	achievement->mIsUnlocked = false;
	MString_Assign(&achievement->mName, name);
	MString_Assign(&achievement->mDescription, description);
	MString_Assign(&achievement->mLockedDescription, lockedDescription);
	achievement->mCondition = condition;
	achievement->mSheet = Sheet_GetDefaultSheet();
	if (!Utils_StringEqualTo(image, ""))
	{
		achievement->mSheet = Sheet_GetSheet(image);
	}
}
void Achievement_Update(bool doNotCertify, Achievement* achievement, int index)
{
	if (!achievement->mIsUnlocked)
	{
		if (achievement->mCondition())
		{
			Achievement_UnlockAchievement(doNotCertify, achievement, index);
		}
	}
}
void Achievement_UnlockAchievement(bool doNotCertify, Achievement* achievement, int index)
{
	if (achievement->mIsUnlocked)
	{
		return;
	}

	achievement->mIsUnlocked = true;
	Logger_printf("Achievement %d - %s has been unlocked", index, achievement->mName);
	if (!doNotCertify)
	{
		Achievement_CertifyAchievement(achievement, index);
	}
}
void Achievement_CertifyAchievement(Achievement* achievement, int index)
{
	if (!achievement->mIsUnlocked || achievement->mIsCertified || !Service_HasSignedIn() || Globals_AreAchievementsDisabled())
	{
		return;
	}

	achievement->mIsCertified = true;

	if (Cvars_GetAsBool(CVARS_ENGINE_DISABLE_SERVICE_ACHIEVEMENTS))
	{
		return;
	}

	Service_HandleSetAchievement(index, MString_GetText(achievement->mName));
}