/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"

void Logger_SetLevel(int level);
void Logger_LogInformation(const char* message);
void Logger_LogInformationSilently(const char* message);
void Logger_LogWarning(const char* message);
void Logger_LogWarningSilently(const char* message);
void Logger_LogError(const char* message);
void Logger_LogErrorSilently(const char* message);
void Logger_Log(const char* message);
void Logger_LogSilently(const char* message);
void Logger_printf(const char* fmt, ...);
//void DrawHud(OeSpriteBatch* spriteBatch);
//void Update();