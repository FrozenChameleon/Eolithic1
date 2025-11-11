#pragma once

#include "../resources/Resource.h"
//#include "../collections/OeDictionary.h"
#include "ImageData.h"

typedef struct MString MString;
typedef struct BufferReader BufferReader;

enum
{
	THING_SETTINGS_BINARY_VERSION = 3
};

typedef struct ThingGraphicsEntry
{
	char* key; 
	ImageData* value; //THIS IS AN STB ARRAY, SHOULD BE ARR_VALUE
} ThingGraphicsEntry;

typedef struct ThingGraphicsData
{
	char* key;
	ThingGraphicsEntry* value;
} ThingGraphicsData;

typedef struct ThingSettings
{
	int mRoutineId;
	int mCollisionWidth;
	int mCollisionHeight;
	bool mDoNotDispose;
	bool mHasAI;
	bool mHasDrawing;
	bool mHasCollision;
	MString* mDefaultState;
	MString* mDefaultPhase;
	MString* mPreviewSheet;
	ThingGraphicsData* sh_graphics_data;
} ThingSettings;

void ThingSettings_Init(ThingSettings* ts);
void ThingSettings_Read(ThingSettings* ts, BufferReader* br);
ThingSettings* ThingSettings_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br);
void ThingSettings_Dispose(ThingSettings* ts);

//OeResourceData* ThingSettings_CreateNewInstance() override;
//static OeThingSettings* ThingSettings_CreateNew();
//void ThingSettings_WriteIni(std::shared_ptr<OeIniWriter> writer) override;
//void ThingSettings_ReadIni(std::shared_ptr<OeIniReader> reader) override;
//static const std::vector<std::string>& ThingSettings_GetDirectories();