/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "../math/Rectangle.h"

//supposed to be public
enum ServicePlatformCrashText
{
	PLATFORM_CRASH_TEXT_NOTHING = 0,
	PLATFORM_CRASH_TEXT_WITH_LOG = 1,
	PLATFORM_CRASH_TEXT_NO_LOG = 2
};

enum ServicePlatform
{
	PLATFORM_S = 0,
	PLATFORM_X = 1,
	PLATFORM_P = 2,
	PLATFORM_N = 3
};

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
int Service_PlatformGetForcedSpecificGlyph();
bool Service_PlatformForcesPlatformNGlyphs();
bool Service_PlatformDisablesWritingRecordings();
bool Service_PlatformUsesLocalStorageForSaveData();
Rectangle Service_PlatformGetForcedWindowSize();
Rectangle Service_PlatformGetForcedBackBufferSize();
bool Service_PlatformForcesVsync();
bool Service_PlatformForcesFullscreen();
bool Service_PlatformDisablesSimultaneousInputForController();
bool Service_PlatformShowsControllerDisconnectScreen();
bool Service_PlatformHidesWindowSizeOption();
int Service_PlatformAchievementCrawlingTime();
bool Service_PlatformDoesNotDoNormalPausing();
bool Service_PlatformGoesToPauseMenuWhenGameIsNotActive();
bool Service_PlatformMutesInputWhenGameIsNotActive();
bool Service_PlatformStopsPollingInputWhenGameIsNotActive();
const char* Service_GetPlatformLanguage();
bool Service_ShowSignInFailure();
int Service_PlatformCrashText();
//void Service_LogMessage(const char* message);
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
bool Service_AreLeaderboardDisabled();
void Service_DisableLeaderboards();
bool Service_HasSignedIn();
void Service_HandleSetAchievement(int index, const char* name);