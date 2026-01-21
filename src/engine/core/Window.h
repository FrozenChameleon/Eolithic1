/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "../math/Rectangle.h"

Rectangle Window_GetWindowSize(void);
Rectangle Window_GetDisplayBounds(void);
Rectangle* Window_GetAllDisplayModeBounds(int32_t* length);
int32_t Window_Init(void);
bool Window_IsFullscreen(void);
void Window_UpdateFullscreen(void);
void Window_SetWindowPositionToCentered(void);
void* Window_GetWindowContext(void);
void Window_Dispose(void);
void Window_SetTheMouseVisible(bool isVisible);
bool Window_IsTheMouseVisible(void);
bool Window_IsWindowActive(void);
void Window_SetWindowActive(bool value);
void Window_LoadIcon(void);