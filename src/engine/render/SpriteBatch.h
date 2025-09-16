#pragma once

#include "RenderStream.h"
#include "DrawInstance.h"
#include "Texture.h"
#include "ShaderProgram.h"

#define SPRITEBATCH_RENDER_STREAMS_LEN 201

typedef struct SpriteBatch
{
	RenderStream _mRenderStreams[SPRITEBATCH_RENDER_STREAMS_LEN];
	bool _mHasInit;
} SpriteBatch;

void SpriteBatch_Init(SpriteBatch* sb);
void SpriteBatch_Clear(SpriteBatch* sb);
RenderCommandSheet* SpriteBatch_Draw(SpriteBatch* sb, Texture* texture, Color color, int depth, ShaderProgram* program, Vector2 position,
	Rectangle sourceRectangle, Vector2 scale, float rotation, bool flipX, bool flipY, Vector2 origin);