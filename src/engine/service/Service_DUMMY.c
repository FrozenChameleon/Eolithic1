#if SERVICE_DUMMY

#include "SDL3/SDL.h"
#include "Service.h"
#include "../io/File.h"
#include "../core/Platform.h"
#include "../utils/Strings.h"

//protected
void Service_UpdateScoreKeepBestHelper(const char* leaderboard, int score, bool isAscending, bool isMilliseconds)
{

}
int Service_GetMinimumRank()
{
	return 0;
}
int Service_GetMaximumRank()
{
	return 0;
}
void Service_RetrieveLeaderboardEntriesHelper(int leaderboardPage, bool isInitialRequest, int direction)
{
}

//public
void Service_Init()
{
}
BufferRequest Service_AskToRetrieveBuffer(bool isPurelyGameSaveData, const char* containerDisplayName, const char* containerName,
	const char* path)
{
	return Service_AskToRetrieveBufferForPC(isPurelyGameSaveData, containerDisplayName, containerName, path);
}
void Service_SaveBuffer(bool isPurelyGameSaveData, const char* containerDisplayName, const char* containerName, const char* path,
	FixedByteBuffer* buffer)
{
	Service_SaveBufferForPC(isPurelyGameSaveData, containerDisplayName, containerName, path, buffer);
}
const char* Service_GetSignedInUserName()
{
	return "NOT_SET";
}
void Service_SignIn(bool trySilentSignIn, bool forceSignIn)
{
}
bool Service_HasSignedIn()
{
	return true;
}
void Service_HandleException(const char* e)
{
}
void Service_HandleSetAchievement(int i, const char* achievement)
{
}
void Service_HandleApplicationExit()
{
}
void Service_Create()
{
}
void Service_UpdateHelper(double delta)
{
}
void Service_Resize(int width, int height)
{
}
void Service_Pause()
{
}
void Service_Resume()
{
}
void Service_Dispose()
{
}
bool Service_IsOverlayEnabled()
{
	return false;
}

int Service_GetPlatformType()
{
	return PLATFORM_STEAM;
}
bool Service_IsSimplifiedLeaderboard()
{
	return false;
}
void Service_FlushStatsToServiceForXbox()
{
}
bool Service_IsLeaderboardRetrievalInProgress()
{
	return false;
}
bool Service_IsShowingLeaderboardCannotConnectError()
{
	return true;
}
bool Service_IsSingleUserApplication()
{
	return true;
}
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
bool Service_PlatformForcesNintendoGlyphs()
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
	return Rectangle_Empty;
}
Rectangle Service_PlatformGetForcedWindowSize()
{
	return Rectangle_Empty;
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
	return 0.5;
}
const char* Service_GetPlatformLanguage()
{
	return Platform_GetPreferredLocalesEFIGS();
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
const char* Service_PlatformSpecificTerminologyFilter(const char* key)
{
	return Strings_Get(key);
}
#endif