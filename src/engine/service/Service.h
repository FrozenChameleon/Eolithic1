#pragma once

#include "ServiceLeaderboard.h"
#include "SaveBlobDataRequest.h"
#include "../io/FixedByteBuffer.h"
#include "../math/Rectangle.h"
#include "../input/InputChecks.h"
#include "../input/InputBindings.h"

//supposed to be protected
const int32_t* Service_GetAchievementMap();
BufferRequest Service_AskToRetrieveBufferForPC(bool isPurelyGameSaveData, const char* containerDisplayName, const char* containerName, const char* path);
int32_t Service_SaveBufferForPC(bool isPurelyGameSaveData, const char* containerDisplayName, const char* containerName, const char* path,
	FixedByteBuffer* buffer);

//supposed to be public
typedef enum ServicePlatformCrashText
{
	PLATFORM_CRASH_TEXT_NOTHING = 0,
	PLATFORM_CRASH_TEXT_WITH_LOG = 1,
	PLATFORM_CRASH_TEXT_NO_LOG = 2
} ServicePlatformCrashText;

typedef enum ServicePlatform
{
	PLATFORM_STEAM = 0,
	PLATFORM_XBOX = 1,
	PLATFORM_PLAYSTATION = 2,
	PLATFORM_NINTENDO = 3
} ServicePlatform;

void Service_Init();
bool Service_IsPlatformSteam();
void Service_ResetAchievements();
int32_t Service_GetPlatformType();
void Service_SetAchievementMap(int32_t* achievementMap, int32_t achievementMapLength);
BufferRequest Service_AskToRetrieveBuffer(bool isPurelyGameSaveData, const char* containerDisplayName, const char* containerName, const char* path);
void Service_SaveBuffer(bool isPurelyGameSaveData, const char* containerDisplayName, const char* containerName, const char* path,
	FixedByteBuffer* buffer);
const char* Service_GetSignedInUserName();
void Service_SignIn(bool trySilentSignIn, bool forceSignIn);
bool Service_HasSignedIn();
bool Service_IsSigningIn();
bool Service_IsOverlayEnabled();
void Service_Create();
void Service_Update(double delta);
void Service_UpdateHelper(double delta);
void Service_Resize(int32_t width, int32_t height);
void Service_Pause();
void Service_Resume();
void Service_Dispose();
void Service_HandleException(const char* e);
void Service_HandleSetAchievement(int32_t index, const char* achievement);
void Service_HandleApplicationExit();
bool Service_PlatformDisablesKeyboardUse();
bool Service_IsSingleUserApplication();
bool Service_PlatformForcesControllerOnPressStartScreen();
bool Service_PlatformForcesControllerGlyphs();
bool Service_PlatformForcesRelyOnVsync();
bool Service_PlatformHidesOptionChangeControllerGlyphs();
bool Service_PlatformHidesOptionExitGame();
bool Service_PlatformHidesAllVideoOptions();
bool Service_PlatformHidesKeyboardBindings();
bool Service_PlatformHidesResetAllBindings();
bool Service_PlatformHidesMenuBindings();
bool Service_PlatformHidesFocusLossToggles();
bool Service_PlatformHidesResetAllData();
bool Service_PlatformForcesSpecificGlyph();
int32_t Service_PlatformGetForcedSpecificGlyph();
bool Service_PlatformForcesNintendoGlyphs();
bool Service_PlatformDisablesWritingRecordings();
bool Service_PlatformUsesLocalStorageForSaveData();
Rectangle Service_PlatformGetForcedWindowSize();
Rectangle Service_PlatformGetForcedBackBufferSize();
bool Service_PlatformForcesVsync();
bool Service_PlatformForcesFullscreen();
bool Service_PlatformDisablesSimultaneousInputForController();
bool Service_PlatformShowsControllerDisconnectScreen();
bool Service_PlatformHidesWindowSizeOption();
int32_t Service_PlatformAchievementCrawlingTime();
bool Service_PlatformDoesNotDoNormalPausing();
bool Service_PlatformGoesToPauseMenuWhenGameIsNotActive();
bool Service_PlatformMutesInputWhenGameIsNotActive();
bool Service_PlatformStopsPollingInputWhenGameIsNotActive();
const char* Service_GetPlatformLanguage();
bool Service_ShowSignInFailure();
int32_t Service_PlatformCrashText();
void Service_LogMessage(const char* message);
bool Service_IsOnlineRightNow();
bool Service_AreNetworkFeaturesAreAvailableRightNow(bool isSilent);
bool Service_IsWaitingOnServiceToFinishLoading(double delta);
bool Service_SuppressDrawing();
bool Service_PlatformDisablesDepthBufferForRender();
bool Service_PlatformRequiresOffscreenTargetForRender();
bool Service_PlatformCanShowWebsites();
bool Service_PlatformShouldLoadWindowIcon();
bool Service_PlatformForcesWindowedModeOnBoot();
bool Service_PlatformNeedsShaderStutterFix();
bool Service_PlatformIsSayingToPauseTheGameIfPossible();
void Service_SignalThatCampaignHasBeenStarted();
void Service_SignalThatCampaignHasBeenCompleted();
void Service_SignalThatCampaigHasBeenAbandoned();
void Service_SignalThatCampaigHasBeenFailed();
const char* Service_PlatformSpecificTerminologyFilter(const char* key);