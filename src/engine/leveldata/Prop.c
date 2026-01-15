#include "Prop.h"

#include "../render/SpriteBatch.h"
#include "../io/File.h"
#include "../utils/Utils.h"
#include "../render/Color.h"
#include "../render/Sheet.h"
#include "../io/BufferReader.h"
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

//static const std_vector<std_string> PROPS_DIRECTORY = { OeFile_PathCombine("data", "props") };

enum
{
	PROP_BINARY_VERSION = 2
};

void Prop_Init(Prop* p)
{
	Utils_memset(p, 0, sizeof(Prop));

	p->_mSheet = Sheet_GetDefaultSheet();
	p->mScaler = 1;
	Utils_strlcpy(p->mTextureName, EE_STR_EMPTY, EE_FILENAME_MAX);
	Utils_strlcpy(p->mTilesetFilter, EE_STR_EMPTY, EE_FILENAME_MAX);
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
void Prop_Draw(Prop* p, SpriteBatch* spriteBatch, int32_t depth, Point position, float scale, float rotation, bool flipX, bool flipY, bool showInfo)
{
	Sheet* sheet = Prop_GetSheet(p);
	Rectangle rect = sheet->mRectangle;

	float scaler = p->mScaler * scale;
	float scaledWidth = (rect.Width * scaler);
	float scaledHeight = (rect.Height * scaler);

	if (showInfo)
	{
		DrawTool_DrawRectangle2(spriteBatch, COLOR_GREEN, 200, Rectangle_Create(position.X, position.Y, TILE_SIZE / 4, TILE_SIZE / 4), 0, false);
		SpriteBatch_DrawString2(spriteBatch, "editor", Utils_IntToStringGlobalBuffer(depth), COLOR_YELLOW, 200,
			Vector2_Create(position.X + (scaledWidth / 2), position.Y + (scaledHeight / 2)), ALIGN_CENTER, ALIGN_CENTER);
	}
	else
	{
		RenderCommandSheet* instance = Sheet_Draw5(sheet, spriteBatch, COLOR_WHITE, depth, false, false, NULL,
			Vector2_Create(position.X + (scaledWidth / 2) - (rect.Width / 2.0f), position.Y + (scaledHeight / 2) - (rect.Height / 2.0f)),
			Vector2_Create2(scaler), rotation, flipX, flipY,
			Vector2_DivFloat(Vector2_Create((float)rect.Width, (float)rect.Height), 2.0f));
		if (p->mIsAdditive)
		{
			instance->mBlendState = BLENDSTATE_ADDITIVE;
		}
	}
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
	BufferReader_ReadString(reader, p->mTextureName, EE_FILENAME_MAX);
	BufferReader_ReadString(reader, p->mTilesetFilter, EE_FILENAME_MAX);
}
IStringArray* Prop_GetDirectories()
{
	return NULL;
}
Prop* Prop_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br)
{
	Prop* p = Utils_malloc(sizeof(Prop));
	Prop_Init(p);
	Prop_ReadIni(p, br);
	return p;
}
void Prop_Dispose(Prop* prop)
{
	Utils_free(prop);
}