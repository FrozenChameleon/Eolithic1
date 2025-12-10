#include "ThingSettings.h"

#include "../utils/MString.h"
#include "../utils/Utils.h"
#include "../io/File.h"
//#include "../utils/OeIniReader.h"
//#include "../utils/OeIniWriter.h"
#include "../../third_party/stb_ds.h"

//TODO C99 static const std::vector<std::string> THINGS_DIRECTORY = { OeFile::Combine("data", "things") };

static const char* TAG_ID = "id";
static const char* TAG_ROUTINE_ID = "routine_id";
static const char* TAG_COLLISION_WIDTH = "collision_width";
static const char* TAG_COLLISION_HEIGHT = "collision_height";
static const char* TAG_DO_NOT_DISPOSE = "do_not_dispose";
static const char* TAG_HAS_AI = "has_ai";
static const char* TAG_HAS_DRAWING = "has_drawing";
static const char* TAG_HAS_COLLISION = "has_collision";
static const char* TAG_DEFAULT_STATE = "default_state";
static const char* TAG_DEFAULT_PHASE = "default_phase";
static const char* TAG_PREVIEW_SHEET = "preview_sheet";
static const char* TAG_GRAPHICS_STATE_COUNT = "state_count";

/*
OeResourceData* OeThingSettings::CreateNewInstance()
{
	return CreateNew();
}
OeThingSettings* OeThingSettings::CreateNew()
{
	return new OeThingSettings();
}
void OeThingSettings::WriteIni(std::shared_ptr<OeIniWriter> writer)
{
	writer->WriteInt32(TAG_ID, 0); //ID has been removed
	writer->WriteInt32(TAG_ROUTINE_ID, mRoutineId);
	writer->WriteInt32(TAG_COLLISION_WIDTH, mCollisionWidth);
	writer->WriteInt32(TAG_COLLISION_HEIGHT, mCollisionHeight);
	writer->WriteBoolean(TAG_DO_NOT_DISPOSE, mDoNotDispose);
	writer->WriteBoolean(TAG_HAS_AI, mHasAI);
	writer->WriteBoolean(TAG_HAS_DRAWING, mHasDrawing);
	writer->WriteBoolean(TAG_HAS_COLLISION, mHasCollision);
	writer->WriteString(TAG_DEFAULT_STATE, mDefaultState);
	writer->WriteString(TAG_DEFAULT_PHASE, mDefaultPhase);
	writer->WriteString(TAG_PREVIEW_SHEET, mPreviewSheet);

	writer->WriteInt32(TAG_GRAPHICS_STATE_COUNT, mMapGraphicsData.Count());
	std::vector<std::string>& firstKeys = mMapGraphicsData.Keys;
	for (int i = 0; i < firstKeys.size(); i++)
	{
		std::string tempState = "state_" + std::to_string(i) + "_";
		std::string key1 = firstKeys[i];
		OeDictionary<std::string, std::vector<OeImageData>>& innerMap = mMapGraphicsData[key1];
		writer->WriteString(tempState + "name", key1);

		writer->WriteInt32(tempState + "phase_count", innerMap.Count());
		std::vector<std::string>& secondKeys = mMapGraphicsData[key1].Keys;
		for (int j = 0; j < secondKeys.size(); j++)
		{
			std::string tempPhase = tempState + "phase_" + std::to_string(j) + "_";
			std::string key2 = secondKeys[j];
			writer->WriteString(tempPhase + "name", key2);

			std::vector<OeImageData>& arrayOfImages = mMapGraphicsData[key1][key2];
			writer->WriteInt32(tempPhase + "image_count", arrayOfImages.size());
			for (int k = 0; k < arrayOfImages.size(); k++)
			{
				std::string tempImage = tempPhase + "image_" + std::to_string(k) + "_";
				arrayOfImages[k].WriteIni(writer, tempImage);
			}
		}
	}
	writer->WriteEOF();
}
void OeThingSettings::ReadIni(std::shared_ptr<OeIniReader> reader)
{

}
const std::vector<std::string>& OeThingSettings::GetDirectories()
{
	return THINGS_DIRECTORY;
}
*/

void ThingSettings_Init(ThingSettings* ts)
{
	Utils_memset(ts, 0, sizeof(ThingSettings));

	Utils_strlcpy(ts->mDefaultState, "DEFAULT", EE_FILENAME_MAX);
	Utils_strlcpy(ts->mDefaultPhase, "DEFAULT", EE_FILENAME_MAX);
	Utils_strlcpy(ts->mPreviewSheet, EE_STR_NOT_SET, EE_FILENAME_MAX);

	sh_new_arena(ts->sh_graphics_data);
}

void ThingSettings_Read(ThingSettings* ts, BufferReader* br)
{
	BufferReader_ReadI32(br); //ID has been removed
	ts->mRoutineId = BufferReader_ReadI32(br);

	ts->mCollisionWidth = BufferReader_ReadI32(br);
	ts->mCollisionHeight = BufferReader_ReadI32(br);
	ts->mDoNotDispose = BufferReader_ReadBoolean(br);
	ts->mHasAI = BufferReader_ReadBoolean(br);
	ts->mHasDrawing = BufferReader_ReadBoolean(br);
	ts->mHasCollision = BufferReader_ReadBoolean(br);
	BufferReader_ReadString(br, ts->mDefaultState, EE_FILENAME_MAX);
	BufferReader_ReadString(br, ts->mDefaultPhase, EE_FILENAME_MAX);
	BufferReader_ReadString(br, ts->mPreviewSheet, EE_FILENAME_MAX);

	int stateCount = BufferReader_ReadI32(br);
	for (int i = 0; i < stateCount; i += 1)
	{
		MString* key1 = BufferReader_ReadMString(br);

		ThingGraphicsEntry* entry = NULL;
		sh_new_arena(entry);

		int phaseCount = BufferReader_ReadI32(br);
		for (int j = 0; j < phaseCount; j += 1)
		{
			MString* key2 = BufferReader_ReadMString(br);

			ImageData* arr_images = NULL;

			int imageCount = BufferReader_ReadI32(br);
			for (int k = 0; k < imageCount; k += 1)
			{
				ImageData data = { 0 };
				ImageData_Init(&data);
				ImageData_Read(&data, br);
				arrput(arr_images, data);
			}

			shput(entry, MString_GetText(key2), arr_images);

			MString_Dispose(&key2);
		}

		shput(ts->sh_graphics_data, MString_GetText(key1), entry);

		MString_Dispose(&key1);
	}
}

ThingSettings* ThingSettings_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br)
{
	ThingSettings* ts = Utils_calloc(1, sizeof(ThingSettings));
	ThingSettings_Init(ts);
	ThingSettings_Read(ts, br);
	return ts;
}

void ThingSettings_Dispose(ThingSettings* ts)
{
	Utils_free(ts);
}
