#include "Prop.h"

#include "../render/SpriteBatch.h"
#include "../io/File.h"
#include "../utils/Utils.h"
#include "../render/Color.h"
#include "../render/Sheet.h"
#include "../io/BufferReader.h"
#include "../io/BufferWriter.h"
#include "../render/DrawTool.h"
#include "../globals/Align.h"
#include "../utils/Logger.h"
#include "../../GlobalDefs.h"

#define TILE_SIZE GLOBAL_DEF_TILE_SIZE

static const char* TAG_IS_ADDITIVE = "is_additive";
static const char* TAG_SCALER = "scaler";
static const char* TAG_FLIP_SPEED = "flip_speed";
static const char* TAG_IS_ANIMATION = "is_animation";
static const char* TAG_TEXTURE_NAME = "texture_name";
static const char* TAG_TILESET_FILTER = "tileset_filter";

//static const std_vector<std_string> PROPS_DIRECTORY = { OeFile_Combine("data", "props") };

enum
{
	PROP_BINARY_VERSION = 2
};

void Prop_Init(Prop* p)
{
	/*_mIsSetup = false;
	_mAnimation = OeAnimation();
	_mSheet = OeSheet_GetDefaultSheet();

	mIsAdditive = false;
	mScaler = 1;
	mFlipSpeed = 0;
	mIsAnimation = false;
	mTextureName = OeUtils_NOT_SET;
	mTilesetFilter = OeUtils_NOT_SET;*/
}

Sheet* Prop_GetSheet(Prop* p)
{
	if (p->mIsAnimation)
	{
		return Animation_GetCurrentSheet(&p->_mAnimation);
	}
	else
	{
		return p->_mSheet;
	}
}
void Prop_Draw(Prop* p, SpriteBatch* spriteBatch, int depth, Point position, float scale, float rotation, bool flipX, bool flipY, bool showInfo)
{
	/*OeSheet* sheet = GetSheet();
	Rectangle rect = sheet->mRectangle;

	float scaler = mScaler * scale;
	float scaledWidth = (rect.Width * scaler);
	float scaledHeight = (rect.Height * scaler);

	if (showInfo)
	{
		OeDrawTool_DrawRectangle(spriteBatch, OeColors_GREEN, 200, Rectangle(position.X, position.Y, TILE_SIZE / 4, TILE_SIZE / 4), 0, false);

		spriteBatch->DrawString("editor", std_to_string(depth), OeColors_YELLOW, 200,
			Vector2(position.X + (scaledWidth / 2), position.Y + (scaledHeight / 2)), OeAlign_CENTER, OeAlign_CENTER);
	}
	else
	{
		OeDrawInstance* instance = OeSheet_Draw(sheet, spriteBatch, OeColors_WHITE, depth, false, false, nullptr,
			Vector2(position.X + (scaledWidth / 2) - (rect.Width / 2.0f), position.Y + (scaledHeight / 2) - (rect.Height / 2.0f)),
			Vector2(scaler), rotation, flipX, flipY,
			Vector2(rect.Width, rect.Height) / 2.0f);
		if (mIsAdditive)
		{
			instance->mBlendState = BlendState_Additive;
		}
	}*/
}
void Prop_UpdateResource(Prop* p)
{
	if (!p->_mIsSetup)
	{
		Prop_LoadDrawing(p);
		p->_mIsSetup = true;
	}

	if (p->mIsAnimation)
	{
		Animation_Update(&p->_mAnimation);
	}
}
void Prop_LoadDrawing(Prop* p)
{
	if (p->mIsAnimation)
	{
		Animation_Init(&p->_mAnimation, p->mTextureName, p->mFlipSpeed);
	}
	else
	{
		p->_mSheet = Sheet_GetSheet(p->mTextureName);
	}
}
Rectangle Prop_GetRectangle(Prop* p)
{
	if (!p->mIsAnimation)
	{
		return p->_mSheet->mRectangle;
	}
	else
	{
		return Animation_GetCurrentSheet(&p->_mAnimation)->mRectangle;
	}
}
const char* Prop_ToString(Prop* p)
{
	return p->mTextureName;
}
Animation* Prop_GetAnimation(Prop* p)
{
	return &p->_mAnimation;
}
Resource* Prop_CreateNewInstance(Prop* p)
{
	return NULL;
	//return new Prop();
}
void Prop_WriteIni(Prop* p, BufferWriter* writer)
{
	/*writer->WriteBoolean(TAG_IS_ADDITIVE, mIsAdditive);
	writer->WriteInt32(TAG_SCALER, mScaler);
	writer->WriteInt32(TAG_FLIP_SPEED, mFlipSpeed);
	writer->WriteBoolean(TAG_IS_ANIMATION, mIsAnimation);
	writer->WriteString(TAG_TEXTURE_NAME, mTextureName);
	writer->WriteString(TAG_TILESET_FILTER, mTilesetFilter);

	writer->WriteEOF();*/
}
void Prop_ReadIni(Prop* p, BufferReader* reader)
{
	p->mIsAdditive = BufferReader_ReadBoolean(reader);
	p->mScaler = BufferReader_ReadI32(reader);
	p->mFlipSpeed = BufferReader_ReadI32(reader);
	p->mIsAnimation = BufferReader_ReadBoolean(reader);
	p->mTextureName = BufferReader_ReadStringToMString(reader);
	p->mTilesetFilter = BufferReader_ReadStringToMString(reader);
}
Prop* Prop_CreateNew(Prop* p)
{
	return NULL;
}
IStringArray* Prop_GetDirectories()
{
	return NULL;
}
Prop* Prop_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br)
{
	Prop* p = Utils_calloc(1, sizeof(Prop));
	Prop_ReadIni(p, br);
	return p;
}
void Prop_Dispose(Prop* prop)
{
	Utils_free(prop);
}