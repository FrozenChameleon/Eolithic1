#include "SpriteBatch.h"

#include "../utils/Logger.h"
#include "Renderer.h"

#define MINIMUM_DEPTH 0
#define MAXIMUM_DEPTH 200

static void ClampDepth(int32_t* depth)
{
	if (*depth > MAXIMUM_DEPTH)
	{
		Logger_LogWarning("Given depth over maximum depth");
		*depth = MAXIMUM_DEPTH;
	}
	if (*depth < MINIMUM_DEPTH)
	{
		Logger_LogWarning("Given depth under minimum depth");
		*depth = MINIMUM_DEPTH;
	}
}

void SpriteBatch_Init(SpriteBatch* sb)
{
	Utils_memset(sb, 0, sizeof(SpriteBatch));

	for (int i = 0; i < SPRITEBATCH_RENDER_STREAMS_LEN; i += 1)
	{
		sb->_mRenderStreams[i]._mBuffer = DynamicByteBuffer_Create();
	}
}

void SpriteBatch_Clear(SpriteBatch* sb)
{
	for (int32_t i = 0; i < SPRITEBATCH_RENDER_STREAMS_LEN; i += 1)
	{
		RenderStream_Clear(&sb->_mRenderStreams[i]);
	}
}

RenderCommandSheet* SpriteBatch_Draw(SpriteBatch* sb, Texture* texture, Color color, int depth, ShaderProgram* program, Vector2 position, Rectangle sourceRectangle, Vector2 scale, float rotation, bool flipX, bool flipY, Vector2 origin)
{
	ClampDepth(&depth);

	if (texture == NULL)
	{
		Logger_LogInformation("MISSING TEXTURE FOR DRAW");
		//TODO C99texture = OeSheet::GetDefaultSheet()->mTextureResource->GetData();
	}

	RenderCommandSheet* command = RenderStream_GetRenderCommandSheetUninitialized(&sb->_mRenderStreams[depth]);
	command->mType = RENDERER_TYPE_SHEET;
	command->mDepth = depth;
	command->mFlipX = flipX;
	command->mFlipY = flipY;
	command->mIsRectangle = false;
	command->mIsInterpolated = false;
	command->mBlendState = 0;
	command->mExtraPasses = 0;
	command->mColor = color;
	command->mPosition = position;
	command->mLastPosition = Vector2_Zero;
	command->mOrigin = origin;
	command->mScale = scale;
	command->mRotation = rotation;
	command->mSourceRectangle = sourceRectangle;
	command->mDestinationRectangle = Rectangle_Empty();
	command->mTexture = texture;
	command->mShaderProgram = program;

	return command;
}
