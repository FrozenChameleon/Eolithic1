/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "../math/Rectangle.h"

Rectangle Window_GetWindowSize();
Rectangle Window_GetDisplayBounds();
void Window_GetAllDisplayModeBounds(Rectangle* displayModeBounds);
int Window_Init();
bool Window_IsFullscreen();
void Window_UpdateFullscreen();
void Window_SetWindowPositionToCentered();
void* Window_GetWindowContext();
void Window_Dispose();
void Window_SetTheMouseVisible(bool isVisible);
bool Window_IsTheMouseVisible();
bool Window_IsWindowActive();
void Window_SetWindowActive(bool value);
void Window_LoadIcon();