#pragma once

#include "../math/Rectangle.h"
#include "../render/Animation.h"
#include "../resources/Resource.h"

typedef struct SpriteBatch SpriteBatch;
typedef struct Sheet Sheet;
typedef struct MString MString;
typedef struct BufferWriter BufferWriter;
typedef struct BufferReader BufferReader;

typedef struct Prop
{
	bool _mIsSetup;
	Animation _mAnimation;
	Sheet* _mSheet;
	bool mIsAdditive;
	int mScaler;
	int mFlipSpeed;
	bool mIsAnimation;
	char mTextureName[EE_FILENAME_MAX];
	char mTilesetFilter[EE_FILENAME_MAX];
} Prop;

void Prop_Init(Prop* p);
Sheet* Prop_GetSheet(Prop* p);
void Prop_Draw(Prop* p, SpriteBatch* spriteBatch, int32_t depth, Point position, float scale, float rotation, bool flipX, bool flipY, bool showInfo);
void Prop_UpdateResource(Prop* p);
void Prop_LoadDrawing(Prop* p);
Rectangle Prop_GetRectangle(Prop* p);
const char* Prop_ToString(Prop* p);
Animation* Prop_GetAnimation(Prop* p);
void Prop_WriteIni(Prop* p, BufferWriter* writer);
void Prop_ReadIni(Prop* p, BufferReader* reader);
IStringArray* Prop_GetDirectories();
Prop* Prop_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br);
void Prop_Dispose(Prop* prop);