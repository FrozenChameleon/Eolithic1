#include "Strings.h"

#include "../core/Game.h"
#include "../core/GameHelper.h"
#include "../utils/Logger.h"
#include "../utils/Utils.h"
//TODO C99 #include "../resources/ResourceManagers.h"

struct MappingInfo
{
	const char* mKey;
	bool mDoNotReplace;
};

//static std_vector<std_string> _mOrderedKeys;
//static std_unordered_map<std_string, std_string> _mMap;
//static std_vector<MappingInfo> _mInfoMap;

static bool _mHasInit;

void Strings_Init()
{
	if (_mHasInit)
	{
		return;
	}

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
	return NULL;
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
	//AddString(key, val, false);
}
void Strings_AddDoNotReplace(const char* key, const char* val, bool doNotReplace)
{
	/*
	if (_mMap.count(key))
	{
		OeLogger_LogError("String map already contains string");
		return;
	}

	_mOrderedKeys.push_back(key);
	_mMap[key] = val;

	if (doNotReplace)
	{
		MappingInfo info = MappingInfo();
		info.mKey = key;
		info.mDoNotReplace = true;
		_mInfoMap.push_back(info);
	}
	*/
}
bool Strings_Contains(const char* key)
{
	return false;
	//return _mMap.count(key);
}
