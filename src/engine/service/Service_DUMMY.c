/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Service.h"

bool Service_PlatformHidesOptionChangeControllerGlyphs()
{
	return false;
}
bool Service_PlatformHidesOptionExitGame()
{
	return false;
}
bool Service_PlatformHidesAllVideoOptions()
{
	return false;
}
bool Service_PlatformHidesKeyboardBindings()
{
	return false;
}
bool Service_PlatformForcesRelyOnVsync()
{
	return false;
}
bool Service_PlatformHidesResetAllBindings()
{
	return false;
}
bool Service_PlatformHidesMenuBindings()
{
	return false;
}
bool Service_PlatformHidesFocusLossToggles()
{
	return false;
}
bool Service_PlatformForcesControllerOnPressStartScreen()
{
	return false;
}
bool Service_PlatformDisablesKeyboardUse()
{
	return false;
}
bool Service_PlatformHidesResetAllData()
{
	return false;
}
bool Service_PlatformForcesSpecificGlyph()
{
	return false;
}
int Service_PlatformGetForcedSpecificGlyph()
{
	return -1;
}
bool Service_PlatformForcesPlatformNGlyphs()
{
	return false;
}
bool Service_PlatformDisablesWritingRecordings()
{
	return false;
}
bool Service_PlatformUsesLocalStorageForSaveData()
{
	return true;
}
Rectangle Service_PlatformGetForcedBackBufferSize()
{
	return Rectangle_Empty();
}
Rectangle Service_PlatformGetForcedWindowSize()
{
	return Rectangle_Empty();
}
bool Service_PlatformForcesVsync()
{
	return false;
}
bool Service_PlatformForcesFullscreen()
{
	return false;
}
void Service_ResetAchievements()
{
}
bool Service_PlatformDisablesSimultaneousInputForController()
{
	return false;
}
bool Service_PlatformForcesControllerGlyphs()
{
	return false;
}
bool Service_PlatformShowsControllerDisconnectScreen()
{
	return false;
}
bool Service_PlatformHidesWindowSizeOption()
{
	return false;
}
int Service_PlatformAchievementCrawlingTime()
{
	return 5;
}
bool Service_PlatformDoesNotDoNormalPausing()
{
	return false;
}
bool Service_PlatformGoesToPauseMenuWhenGameIsNotActive()
{
	return false;
}
bool Service_PlatformMutesInputWhenGameIsNotActive()
{
	return false;
}
bool Service_PlatformStopsPollingInputWhenGameIsNotActive()
{
	return false;
}
bool Service_IsSigningIn()
{
	return false;
}
double Service_GetPlatformLeaderboardDelayTime()
{
	return .5;
}
const char* Service_GetPlatformLanguage()
{
	return "en";
	//return OePlatform::GetPreferredLocalesEFIGS();
}
bool Service_ShowSignInFailure()
{
	return false;
}
int Service_PlatformCrashText()
{
	return PLATFORM_CRASH_TEXT_WITH_LOG;
}
bool Service_IsOnlineRightNow()
{
	return true;
}
bool Service_PlatformDoesNotAllowLeaderboardScrollingForFriendScope()
{
	return false;
}
bool Service_AreNetworkFeaturesAreAvailableRightNow(bool isSilent)
{
	return true;
}
bool Service_LeaveTheLeaderboardMenuRightNow()
{
	return false;
}
void Service_TurnOffLeaderboardCannotConnectError()
{

}
bool Service_IsWaitingOnServiceToFinishLoading(double delta)
{
	return false;
}
bool Service_SuppressDrawing()
{
	return false;
}
bool Service_PlatformDisablesDepthBufferForRender()
{
	return true;
}
bool Service_PlatformRequiresOffscreenTargetForRender()
{
	return true;
}
bool Service_PlatformCanShowWebsites()
{
	return true;
}
bool Service_PlatformShouldLoadWindowIcon()
{
	return true;
}
bool Service_PlatformForcesWindowedModeOnBoot()
{
	return false;
}
bool Service_PlatformNeedsShaderStutterFix()
{
	return false;
}
bool Service_PlatformIsSayingToPauseTheGameIfPossible()
{
	return false;
}
void Service_SignalThatCampaignHasBeenStarted()
{

}
void Service_SignalThatCampaignHasBeenCompleted()
{

}
void Service_SignalThatCampaigHasBeenAbandoned()
{

}
void Service_SignalThatCampaigHasBeenFailed()
{

}
bool Service_AreLeaderboardDisabled()
{
	return true;
}
void Service_DisableLeaderboards()
{

}
bool Service_HasSignedIn()
{
	return true;
}
void Service_HandleSetAchievement(int index, const char* name)
{

}
