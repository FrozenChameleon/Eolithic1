/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"

const char* GameUpdater_GetFpsString();
float GameUpdater_GetAutoSpeedUpdateSpeed();
int32_t GameUpdater_GetFPS();
bool GameUpdater_IsInterpolated();
void GameUpdater_Update(double delta);
void GameUpdater_DebugReloadMap();
void GameUpdater_DebugSaveMap();
void GameUpdater_FastReset();
void GameUpdater_FastResetPlusMove();
void GameUpdater_ToggleEditor();
void GameUpdater_ToggleDebugAutoSpeed();
void GameUpdater_DebugReloadGraphics();
void GameUpdater_CycleDebugShowInfo();
uint64_t GameUpdater_GetGlobalTicks();
bool GameUpdater_IsDebugAutoSpeedOn();
double GameUpdater_GetLastDelta();
double GameUpdater_GetDeltaAccumulator();
uint64_t GameUpdater_GetSkippedFrames();
