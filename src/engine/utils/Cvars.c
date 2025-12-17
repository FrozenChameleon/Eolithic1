/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Cvars.h"

#include "stdio.h"
#include "../../third_party/stb_ds.h"
#include "Utils.h"
#include "Macros.h"
#include "../io/INIFile.h"
#include "../utils/MString.h"

#define STR_NOT_SET "NOT_SET"
#define STR_ZERO "0"
#define STR_ONE "1"

//private to definition
typedef struct CvarData
{
	float mCachedNumber;
	bool mHasBeenSet;
	bool mDoNotRefreshCachedNumber;
	char mKey[EE_FILENAME_MAX];
	char mValue[EE_FILENAME_MAX];
} CvarData;

static struct { char* key; CvarData value; } *sh_cvars;
static bool _mHasInit;

static CvarData* GetCvarData(const char* key, const char* valueIfCvarHasNotBeenSet)
{
	int64_t index = shgeti(sh_cvars, key);
	if (index == -1)
	{
		CvarData cvar = { 0 };
		cvar.mCachedNumber = 0;
		cvar.mHasBeenSet = true;
		cvar.mDoNotRefreshCachedNumber = false;
		Utils_strlcpy(cvar.mKey, key, EE_FILENAME_MAX);
		Utils_strlcpy(cvar.mValue, valueIfCvarHasNotBeenSet, EE_FILENAME_MAX);
		shput(sh_cvars, key, cvar);
	}
	return &shgetp(sh_cvars, key)->value;
}
static void SetupCvarForSet(CvarData* cvar, const char* key)
{
	cvar->mCachedNumber = 0;
	cvar->mHasBeenSet = true;
	cvar->mDoNotRefreshCachedNumber = false;
	Utils_strlcpy(cvar->mKey, key, EE_FILENAME_MAX);
}

static void Init()
{
	if (_mHasInit)
	{
		return;
	}

	sh_new_arena(sh_cvars);

	_mHasInit = true;
}

void Cvars_FlipAsBool(const char* key)
{
	//
	Init();
	//

	Cvars_SetAsBool(key, !Cvars_GetAsBool(key));
}
void Cvars_SetAsBool(const char* key, bool value)
{
	//
	Init();
	//

	if (!value)
	{
		Cvars_Set(key, STR_ZERO);
	}
	else
	{
		Cvars_Set(key, STR_ONE);
	}
}
void Cvars_SetAsInt(const char* key, int32_t value)
{
	//
	Init();
	//

	CvarData* cvar = GetCvarData(key, STR_NOT_SET);
	SetupCvarForSet(cvar, key);
	Utils_IntToString(value, cvar->mValue, EE_FILENAME_MAX);
}
void Cvars_SetAsFloat(const char* key, float value)
{
	//
	Init();
	//

	CvarData* cvar = GetCvarData(key, STR_NOT_SET);
	SetupCvarForSet(cvar, key);
	Utils_FloatToString(value, cvar->mValue, EE_FILENAME_MAX);
}
void Cvars_Set(const char* key, const char* value)
{
	//
	Init();
	//

	CvarData* cvar = GetCvarData(key, value);
	SetupCvarForSet(cvar, key);
	Utils_strlcpy(cvar->mValue, value, EE_FILENAME_MAX);
}
const char* Cvars_Get(const char* key)
{
	//
	Init();
	//

	return GetCvarData(key, STR_NOT_SET)->mValue;
}
float Cvars_GetAsFloat(const char* key)
{
	//
	Init();
	//

	CvarData* data = GetCvarData(key, STR_ZERO);
	if (data->mDoNotRefreshCachedNumber)
	{
		return data->mCachedNumber;
	}
	else
	{
		data->mCachedNumber = Utils_ParseFloat(data->mValue);
		data->mDoNotRefreshCachedNumber = true;
		return data->mCachedNumber;
	}
}
int Cvars_GetAsInt(const char* key)
{
	//
	Init();
	//

	return (int)(Cvars_GetAsFloat(key));
}
bool Cvars_GetAsBool(const char* key)
{
	//
	Init();
	//

	const char* value = Cvars_Get(key);
	if (Utils_StringEqualTo(value, STR_ZERO))
	{
		return false;
	}
	else
	{
		return true;
	}
}
void Cvars_Read(const char* path)
{
	//
	Init();
	//

	INIFile* ini = INIFile_Create_From_Binary(path);
	int64_t len = INIFile_GetLength(ini);
	for (int i = 0; i < len; i += 1)
	{
		const char* key = INIFile_GetKey(ini, i);
		const char* value = INIFile_GetValue(ini, i);
		Cvars_Set(key, value);
	}
	INIFile_Dispose(ini);
}
int64_t Cvars_Length()
{
	//
	Init();
	//

	return shlen(sh_cvars);
}
void Cvars_SaveUserConfig()
{
	//
	Init();
	//
	//TODO
}
