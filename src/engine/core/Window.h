/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"

int32_t Window_Init();
void* Window_GetWindowContext();
bool Window_IsWindowActive();
void Window_SetWindowActive(bool value);
bool Window_IsFullscreen();