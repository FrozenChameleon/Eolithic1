#include "Strings.h"

#include "../core/Game.h"
#include "../core/GameHelper.h"
#include "../utils/Logger.h"
#include "../utils/Utils.h"
#include "../utils/IStringMap.h"
#include "../../third_party/stb_ds.h"

typedef struct MappingInfo
{
	const char* mKey;
	bool mDoNotReplace;
} MappingInfo;

static IStringMap* _mMap;
static MappingInfo* arr_info_list;

static bool _mHasInit;
static char _mTemp[10];

void Strings_Init()
{
	if (_mHasInit)
	{
		return;
	}

	_mMap = IStringMap_Create();

	GameHelper_AddStrings();

	_mHasInit = true;
}

/*
static const char* GetTextToReturn(const char* key, std_unordered_map<std_string, std_string>& map)
{
	auto it = map.find(key);
	if (it == map.end())
	{
		return key;
	}
	else
	{
		return it->second;
	}
}
*/

const char* Strings_Get(const char* key)
{
	if (!IStringMap_Contains(_mMap, key))
	{
		return key;
	}

	return IStringMap_Get(_mMap, key);
	/*
if (OeGlobals.DEBUG_IS_GOD_MODE)
{
string debugString = "";
for (int i = 0; i < returnValue.Length; i++)
{
debugString += "-";
}
return debugString;
}
*/
	//TODO C99
	/*
	std_string textToReturn = GetTextToReturn(key, _mMap);

	std_string language = OeUtils_GetCurrentUserLanguageCode();
	if (language != "en")
	{
		if (OeResourceManagers_StringsTextManager.HasResource(language))
		{
			OeStringsText* languageText = OeResourceManagers_StringsTextManager.GetResourceData(language);
			if (!languageText->IsDictionaryReady())
			{
				languageText->CreateDictionary(_mOrderedKeys);
			}
			if (!languageText->IsDictionaryReady())
			{
				OeLogger_LogInformation("Mismatched language string size");
				return textToReturn;
			}

			textToReturn = GetTextToReturn(key, languageText->mDictionary);
		}
	}*/

	//return textToReturn;
}
void Strings_Add(const char* key, const char* val)
{
	Strings_AddDoNotReplace(key, val, false);
}
void Strings_AddDoNotReplace(const char* key, const char* val, bool doNotReplace)
{
	if (IStringMap_Contains(_mMap, key))
	{
		Logger_LogError("String map already contains string");
		return;
	}

	IStringMap_Add(_mMap, key, val);

	if (doNotReplace)
	{
		MappingInfo info = { 0 };
		info.mKey = key;
		info.mDoNotReplace = true;
		arrput(arr_info_list, info);
	}
}
bool Strings_Contains(const char* key)
{
	return IStringMap_Contains(_mMap, key);
}
