#include "ThingInstance.h"

#include "../utils/Utils.h"
#include "../io/BufferReader.h"
#include "../io/BufferWriter.h"
//#include "ThingSettings.h"
#include "../render/SpriteBatch.h"
#include "../math/Points.h"
#include "../utils/Logger.h"
#include "../utils/Cvars.h"
#include "../core/Game.h"
#include "../core/GameHelper.h"
#include "../resources/Resource.h"
#include "../utils/Utils.h"
#include "../../GlobalDefs.h"
#include "../../third_party/stb_ds.h"

#define TILE_SIZE GLOBAL_DEF_TILE_SIZE
#define HALF_TILE_SIZE GLOBAL_DEF_HALF_TILE_SIZE

//static std_vector<OeStringPair> _mPairs;

static void BuildGlobalThingSettings()
{
	/*
	_mPairs = {};
	_mPairs.push_back(OeStringPair(ThingInstance_SETTING_DTN_OFFSET_X, "0"));
	_mPairs.push_back(OeStringPair(ThingInstance_SETTING_DTN_OFFSET_Y, "0"));
	if (OeCvars_GetAsInt(OeCvars_ENGINE_NUMBER_OF_DIFFICULTIES) > 1)
	{
		_mPairs.push_back(OeStringPair("BLN_DIFFICULTY_EASY", "T"));
		_mPairs.push_back(OeStringPair("BLN_DIFFICULTY_NORMAL", "T"));
		if (OeCvars_GetAsInt(OeCvars_ENGINE_NUMBER_OF_DIFFICULTIES) > 2)
		{
			_mPairs.push_back(OeStringPair("BLN_DIFFICULTY_HARD", "T"));
		}
		if (OeCvars_GetAsInt(OeCvars_ENGINE_NUMBER_OF_DIFFICULTIES) > 3)
		{
			_mPairs.push_back(OeStringPair("BLN_DIFFICULTY_VERY_HARD", "T"));
		}
	}
	OeGameHelper_AddDefaultThingSettings(_mPairs);*/
}
/*
static std_vector<OeStringPair>& GetGlobalThingSettings()
{
	if (_mPairs.size() == 0)
	{
		BuildGlobalThingSettings();
	}
	return _mPairs;
}
*/

void ThingInstance_Init(ThingInstance* ti)
{
	/*mName = OeUtils_NOT_SET;
	mNodes = {};
	mSettings = {};*/
}

StringPair* ThingInstance_GetSetting(ThingInstance* ti, const char* key)
{
	return NULL;
	/*for (int i = 0; i < mSettings.size(); i++)
	{
		OeStringPair* pair = &mSettings[i];
		if (pair->mKey == key)
		{
			return *pair;
		}
	}
	return OeStringPair_Empty;*/
}
void ThingInstance_SetSetting(ThingInstance* ti, const char* key, const char* value)
{
	/*for (int i = 0; i < mSettings.size(); i++)
	{
		OeStringPair* pair = &mSettings[i];
		if (pair->mKey == key)
		{
			pair->mValue = value;
		}
	}*/
}
void ThingInstance_Write(ThingInstance* ti, BufferWriter* writer)
{
	/*writer->WriteInt32(0); //V3 //Unused - Thing Instance ID
	writer->WriteString(mName);

	writer->WriteSingle(0); //Unused - Offset X
	writer->WriteSingle(0); //Unused - Offset Y

	writer->WriteInt32(mNodes.size());
	for (int i = 0; i < mNodes.size(); i++)
	{
		OePoints_Write(mNodes[i], writer);
	}

	writer->WriteInt32(mSettings.size());
	for (int i = 0; i < mSettings.size(); i++)
	{
		OeStringPair_Write(&mSettings[i], writer);
	}*/
}
void ThingInstance_Read(ThingInstance* ti, int version, BufferReader* reader)
{
	if (version >= 3)
	{
		BufferReader_ReadI32(reader); //Unused - Thing Instance ID
	}
	ti->mName = BufferReader_ReadStringToMString(reader);
	BufferReader_ReadFloat(reader); //Unused - Offset X
	BufferReader_ReadFloat(reader); //Unused - Offset Y

	int sizeNode = BufferReader_ReadI32(reader);
	for (int i = 0; i < sizeNode; i++)
	{
		Point point = { 0 };
		Points_Read(&point, reader);
		arrput(ti->arr_nodes, point);
	}

	int sizeSettings = BufferReader_ReadI32(reader);
	for (int i = 0; i < sizeSettings; i++)
	{
		StringPair pair = { 0 };
		StringPair_Read(&pair, reader);
		arrput(ti->arr_settings, pair);
	}
}
void ThingInstance_SetupSettings(ThingInstance* instance, bool ignoreWarnings)
{
	//WILLNOTDO 05152023
	/*
	OeThingSettings* settings = instance->GetThingSettings();

	if (settings == nullptr)
	{
		return;
	}

	if (!settings->mHasAI)
	{
		return;
	}

	OeDictionary<int, Type> controllerComponentTypeMap = OeGameHelper_GetControllerComponentTypeMap();
	if (!controllerComponentTypeMap.Keys.Contains(settings.mRoutineId))
	{
		return;
	}

	Type controllerComponentType = controllerComponentTypeMap[settings.mRoutineId];

	OeListStruct<OeStringPair> arrayOfStringPairs;
	if (!OeFunc.Is_InitialStringSettingsMapPresent(controllerComponentType))
	{
		arrayOfStringPairs = null;
	}
	else
	{
		arrayOfStringPairs = OeFunc.Get_InitialStringSettingsFromMap(controllerComponentType);
	}
	if (arrayOfStringPairs != null)
	{
		AddMissingPairs(GetGlobalThingSettings(), arrayOfStringPairs, ignoreWarnings);
		RemoveUnrelatedPairs(instance, arrayOfStringPairs, instance.mSettings, ignoreWarnings);
		AddMissingPairs(arrayOfStringPairs, instance.mSettings, ignoreWarnings);
	}
	else
	{
		AddMissingPairs(GetGlobalThingSettings(), instance.mSettings, ignoreWarnings);
	}
	*/
}

const char* ThingInstance_SETTING_DTN_OFFSET_X = "DTN_OFFSET_X";
const char* ThingInstance_SETTING_DTN_OFFSET_Y = "DTN_OFFSET_Y";

const char* ThingInstance_SETTING_BLN_DIFFICULTY_EASY = "BLN_DIFFICULTY_EASY";
const char* ThingInstance_SETTING_BLN_DIFFICULTY_NORMAL = "BLN_DIFFICULTY_NORMAL";
const char* ThingInstance_SETTING_BLN_DIFFICULTY_HARD = "BLN_DIFFICULTY_HARD";
const char* ThingInstance_SETTING_BLN_DIFFICULTY_VERY_HARD = "BLN_DIFFICULTY_VERY_HARD";

void ThingInstance_RemoveUnrelatedPairs(ThingInstance* instance, StringPair* arr_from, StringPair* arr_to, bool ignoreWarnings)
{
	/*for (int i = 0; i < instance->mSettings.size(); i++)
	{
		OeStringPair& pair = arrayTo[i];
		if (!Contains(pair, arrayFrom))
		{
			if (!ignoreWarnings)
			{
				OeLogger_LogWarning("Removed unrelated string pair for " + pair.mKey);
			}
			arrayTo.erase(arrayTo.begin() + i);
			i--;
		}
	}*/
}
void ThingInstance_AddMissingPairs(StringPair* arr_from, StringPair* arr_to, bool ignoreWarnings)
{
	/*for (int i = 0; i < arrayFrom.size(); i++)
	{
		const OeStringPair& pair = arrayFrom[i];
		if (!Contains(pair, arrayTo))
		{
			if (!ignoreWarnings)
			{
				OeLogger_LogWarning("Missing string pair for " + pair.mKey);
			}
			arrayTo.insert(arrayTo.begin() + i, pair);
		}
	}*/
}
bool ThingInstance_Contains(StringPair* pair, StringPair* arr_string_pairs)
{
	/*for (int i = 0; i < arrayOfStringPairs.size(); i++)
	{
		const const char*& keyOne = arrayOfStringPairs[i].mKey;
		const const char*& keyTwo = pair.mKey;
		if (keyOne == keyTwo)
		{
			return true;
		}
	}*/

	return false;
}
ThingInstance* ThingInstance_GetClone(ThingInstance* ti)
{
	return NULL;
	/*ThingInstance copy = ThingInstance();

	copy.mName = mName;

	for (int i = 0; i < mNodes.size(); i++)
	{
		copy.mNodes.push_back(mNodes[i]);
	}

	for (int i = 0; i < mSettings.size(); i++)
	{
		copy.mSettings.push_back(mSettings[i]);
	}

	return copy;*/
}
bool ThingInstance_IsEqualTo(ThingInstance* ti, ThingInstance* instance)
{
	return false;

	//WILLNOTDO 05152023
	/*
	if (instance->mName != mName)
	{
		return false;
	}

	if (mNodes.size() != instance->mNodes.size())
	{
		return false;
	}
	for (int i = 0; i < mNodes.size(); i++)
	{
		if (mNodes[i] != instance->mNodes[i])
		{
			return false;
		}
	}

	if (!OeUtils_IsArrayEqualTo(mSettings, instance.mSettings))
	{
		return false;
	}

	return true;
	*/
}
ThingSettings* ThingInstance_GetThingSettings(ThingInstance* ti)
{
	return NULL;
	//return OeResourceManagers_ThingSettingsManager.GetResourceData(mName);
}
void ThingInstance_Draw(ThingInstance* ti, SpriteBatch* spriteBatch, Color color, Point position, bool isSelected)
{
	//Draw(spriteBatch, color, 100, position, isSelected);
}
void ThingInstance_Draw2(ThingInstance* ti, SpriteBatch* spriteBatch, Color color, int depth, Point position, bool isSelected)
{
	//WILLNOTDO 05152023
	/*
	OeDrawTool.DrawRectangle(spriteBatch, color, depth - 1, new Rectangle(position.X, position.Y, GetWidth(), GetHeight()), 0, false);

	OeThingSettings settings = GetThingSettings();
	string sheetName;
	if (settings == null)
	{
		sheetName = OeUtils.NOT_SET;
	}
	else
	{
		sheetName = settings.mPreviewSheet;
	}

	Point center = position + OePoints.HalfTileSize();

	OeSheet.Draw(ref OeSheet.GetSheet(sheetName), spriteBatch, OeColors.WHITE, depth, true, true, null, new Vector2(center.X, center.Y), Vector2.One, 0);

	if (isSelected)
	{
		int tileSize = TILE_SIZE
		int halfTileSize = OeUtils.GetHalfTileSize();
		for (int i = 0; i < mNodes.Count; i++)
		{
			Point nodeOne = mNodes[i];

			int nodeOnePositionX = position.X + nodeOne.X * tileSize + halfTileSize;
			int nodeOnePositionY = position.Y + nodeOne.Y * tileSize + halfTileSize;

			OeDrawTool.DrawRectangle(spriteBatch, OeColors.PINK, depth + 5, new Rectangle(nodeOnePositionX, nodeOnePositionY, tileSize, tileSize), 0, true);
			spriteBatch.DrawString("editor", i.ToString(), OeColors.BLUE, 200,
				new Vector2(nodeOnePositionX, nodeOnePositionY), OeAlign.CENTER, OeAlign.CENTER);

			int size = 1;
			if (i == 0)
			{
				OeDrawTool.DrawLine(spriteBatch, OeColors.RED, 100, 4, 0, size, nodeOnePositionX, nodeOnePositionY, center.X, center.Y);
			}
			else if (i > 0)
			{
				Point nodeTwo = mNodes[i - 1];
				int nodeTwoPositionX = position.X + nodeTwo.X * tileSize + halfTileSize;
				int nodeTwoPositionY = position.Y + nodeTwo.Y * tileSize + halfTileSize;
				OeDrawTool.DrawLine(spriteBatch, OeColors.BLUE, 100, 4, 0, size, nodeOnePositionX, nodeOnePositionY, nodeTwoPositionX, nodeTwoPositionY);
			}
			if (i == mNodes.Count - 1 && mNodes.Count > 1)
			{
				OeDrawTool.DrawLine(spriteBatch, OeColors.YELLOW, 100, 4, 0, size, nodeOnePositionX, nodeOnePositionY, center.X, center.Y);
			}
		}
	}
	*/
}
const char* ThingInstance_GetName(ThingInstance* ti)
{
	return ti->mName->text;
}
int ThingInstance_GetLeft(ThingInstance* ti, float positionX)
{
	float value = positionX + HALF_TILE_SIZE - ThingInstance_GetWidth(ti) / 2;
	return (int)value;
}
int ThingInstance_GetTop(ThingInstance* ti, float positionY)
{
	float value = positionY + HALF_TILE_SIZE - ThingInstance_GetHeight(ti) / 2;
	return (int)value;
}
int ThingInstance_GetWidth(ThingInstance* ti)
{
	return TILE_SIZE;
}
int ThingInstance_GetHeight(ThingInstance* ti)
{
	return TILE_SIZE;
}