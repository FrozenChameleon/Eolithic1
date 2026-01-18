/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Logger.h"

#include "SDL3/SDL.h"
#include "stdarg.h"
#include "stdio.h"

static const char* _mMessageStr = "INFORMATION : ";
static const char* _mWarningStr = "WARNING : ";
static const char* _mErrorStr = "ERROR : ";

void Logger_SetLevel(int32_t level)
{

}

static void LogHelper(const char* type, const char* message, bool isSilent)
{
#ifdef GLOBAL_DEF_DISABLE_ALL_LOGGING
	return;
#endif

	if (message == NULL)
	{
		return;
	}

	if (type == NULL)
	{
		SDL_Log("%s", message);
	}
	else
	{
		SDL_Log("%s%s", type, message);
	}

#ifdef DEBUG_DEF_ENABLE_CONSOLE_NOTIFICATIONS
	if (!silent && OeGlobals::IsGameLoaded())
	{
		if (_mNotifications.size() < HARD_LIMIT_ON_NOTIFICATIONS)
		{
			OeLoggerNotification notification = OeLoggerNotification();
			notification.mPosition = Vector2::Zero;
			notification.mTimer.mLimit = TOTAL_TIME;
			notification.mFadeTimer.mLimit = FADE_OUT_TIME;
			notification.mText = message;
			_mNotifications.push_back(notification);
		}
	}
#endif
}

void Logger_LogInformation(const char* message)
{
	LogHelper(_mMessageStr, message, false);
}
void Logger_LogInformationSilently(const char* message)
{
	LogHelper(_mMessageStr, message, true);
}
void Logger_LogWarning(const char* message)
{
	LogHelper(_mWarningStr, message, false);
}
void Logger_LogWarningSilently(const char* message)
{
	LogHelper(_mWarningStr, message, true);
}
void Logger_LogError(const char* message)
{
	LogHelper(_mErrorStr, message, false);
}
void Logger_LogErrorSilently(const char* message)
{
	LogHelper(_mErrorStr, message, true);
}
void Logger_Log(const char* message)
{
	LogHelper(NULL, message, false);
}
void Logger_LogSilently(const char* message)
{
	LogHelper(NULL, message, true);
}
void Logger_printf(const char* fmt, ...)
{
#ifdef GLOBAL_DEF_DISABLE_ALL_LOGGING
	return;
#endif

	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
}
