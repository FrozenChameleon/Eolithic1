/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

 /* Derived from code by Ethan Lee (Copyright 2009-2024).
  * Released under the Microsoft Public License.
  * See fna.LICENSE for details.

  * Derived from code by the Mono.Xna Team (Copyright 2006).
  * Released under the MIT License.
  * See monoxna.LICENSE for details.
  */

#pragma once

#include "stdint.h"
#include "stdbool.h"

#pragma once

#include "../render/Color.h"
#include "../math/Rectangle.h"
#include "../math/Vector2.h"
#include "../math/Matrix.h"
#include "../render/Texture.h"
#include "../render/ShaderProgram.h"
#include "SpriteSortMode.h"
#include "BlendState.h"
#include "SpriteEffects.h"
#include "../io/FixedByteBuffer.h"
#include "SpriteBatch.h"
#include "DrawInstance.h"
#include "../font/BmFont.h"

typedef struct TtFontState
{
	Vector2 mPosition;
	Color mColor;
	float mScaleFactor;
} TtFontState;

typedef struct ImagePixelData
{
	uint8_t* mData;
	int mWidth;
	int mHeight;
} ImagePixelData;

typedef struct PositionFloat3
{
	float X;
	float Y;
	float Z;
} PositionFloat3;

typedef struct ColorFloat4
{
	float R;
	float G;
	float B;
	float A;
} ColorFloat4;

typedef struct TextureCoordinateFloat2
{
	float U;
	float V;
} TextureCoordinateFloat2;

typedef struct VertexPositionColorTexture
{
	PositionFloat3 Position;
	ColorFloat4 Color;
	TextureCoordinateFloat2 TextureCoordinate;
} VertexPositionColorTexture;

typedef struct VertexPositionColorTexture4
{
	PositionFloat3 Position0;
	PositionFloat3 Position1;
	PositionFloat3 Position2;
	PositionFloat3 Position3;
	ColorFloat4 Color0;
	ColorFloat4 Color1;
	ColorFloat4 Color2;
	ColorFloat4 Color3;
	TextureCoordinateFloat2 TextureCoordinate0;
	TextureCoordinateFloat2 TextureCoordinate1;
	TextureCoordinateFloat2 TextureCoordinate2;
	TextureCoordinateFloat2 TextureCoordinate3;
} VertexPositionColorTexture4;

typedef enum ShaderType
{
	RENDERER_SHADER_TYPE_SPRITE_EFFECT = 0,
	RENDERER_SHADER_TYPE_WHITE_HIT_FLASH = 1,
	RENDERER_SHADER_TYPE_MULTI_COLOR_REPLACE = 2,
	RENDERER_SHADER_TYPE_ALPHA_TEST = 3
} ShaderType;

typedef enum DrawType
{
	RENDERER_TYPE_SHEET = 1,
	RENDERER_TYPE_STRING = 2,
	RENDERER_TYPE_STRING_BUILDER = 3,
	RENDERER_TYPE_TILE_LAYER = 3,
	RENDERER_TYPE_MANY_RECTANGLE = 4
} DrawType;

typedef enum DrawMode
{
	RENDERER_DRAWMODE_ASPECT = 0,
	RENDERER_DRAWMODE_SUPERSAMPLE = 1,
	RENDERER_DRAWMODE_PIXELPERFECT = 2,
	RENDERER_DRAWMODE_END_OF_NORMAL_OPTIONS = 2,
	RENDERER_DRAWMODE_STRETCH = 3
} DrawMode;

void Renderer_SetGlobalShaderProgram(ShaderProgram* value);
ShaderProgram* Renderer_GetGlobalShaderProgram();
void Renderer_INTERNAL_SetCurrentShaderProgram(ShaderProgram* value);
ShaderProgram* Renderer_INTERNAL_GetCurrentShaderProgram();
void Renderer_INTERNAL_SetCurrentBlendState(BlendState value);
BlendState Renderer_INTERNAL_GetCurrentBlendState();
void Renderer_INTERNAL_SetCurrentCameraPosition(Vector2 value);
Vector2 Renderer_INTERNAL_GetCurrentCameraPosition();
void Renderer_INTERNAL_SetCurrentDepth(int value);
int Renderer_INTERNAL_GetCurrentDepth();
Rectangle Renderer_GetWantedBackBufferBounds();
int Renderer_Init(void* deviceWindowHandle);
int Renderer_InitSpriteBatch();
Texture* Renderer_GetTextureData(const char* path, FixedByteBuffer* blob);
Texture* Renderer_GetNewTextureData(const char* path, int width, int height, bool clearTexture);
void Renderer_UpdateTextureData(Texture* texture, int x, int y, int w, int h, int level, void* data, int dataLength);
SpriteEffects Renderer_GetEffects(bool flipX, bool flipY);
int Renderer_ImageRead(void* context, char* data, int size);
void Renderer_ImageSkip(void* context, int n);
int Renderer_ImageEndOfFile(void* context);
ImagePixelData Renderer_CreateImagePixelData(FixedByteBuffer* blob);
void* Renderer_CreateSurface(FixedByteBuffer* blob);
void Renderer_BeforeCommit();
void Renderer_AfterCommit();
void Renderer_FlushBatch();
void Renderer_EnableDepthBufferWrite();
void Renderer_DisableDepthBufferWrite();
void Renderer_LogInfo(const char* msg);
void Renderer_LogWarning(const char* msg);
void Renderer_LogError(const char* msg);
void Renderer_SetupVerticesForTtFont(VertexPositionColorTexture* vertices, Color fontColor, int pos, const float* verts, const float* tcoords, const unsigned int* colors, int nverts);
const TtFontState* GetTtFontState();
void Renderer_SetupTtFontState(const TtFontState* fontState);
void Renderer_DrawTtText(Texture* texture, const float* verts, const float* tcoords, const unsigned int* colors, int nverts);
void Renderer_SetupVerticesFromVPCT4(VertexPositionColorTexture* vertices, int pos, const VertexPositionColorTexture4* sprite);
void Renderer_DrawVertexPositionColorTexture4(Texture* texture, const VertexPositionColorTexture4* sprite);
void Renderer_GenerateVertexInfo(Texture* texture, float sourceX, float sourceY, float sourceW, float sourceH,
	float destinationX, float destinationY, float destinationW, float destinationH,
	Color color, float originX, float originY, float rotationSin, float rotationCos, float depth, uint8_t effects);
void Renderer_PushSprite(Texture* texture, float sourceX, float sourceY, float sourceW, float sourceH,
	float destinationX, float destinationY, float destinationW, float destinationH,
	Color color, float originX, float originY, float rotationSin, float rotationCos, float depth, uint8_t effects);
void Renderer_Draw(Texture* texture, Rectangle destinationRectangle, Color color);
void Renderer_Draw2(Texture* texture, Vector2 position, Rectangle sourceRectangle, Color color);
void Renderer_Draw3(Texture* texture, Rectangle destinationRectangle, Rectangle sourceRectangle, Color color,
	float rotation, Vector2 origin, SpriteEffects effects, float layerDepth);
void Renderer_Draw4(Texture* texture, Vector2 position, Rectangle sourceRectangle, Color color, float rotation, Vector2 origin,
	Vector2 scale, SpriteEffects effects, float layerDepth);
void Renderer_Draw5(Texture* texture, Vector2 position, Rectangle sourceRectangle, Color color, float rotation,
	Vector2 origin, float scale, SpriteEffects effects, float layerDepth);
void Renderer_DrawSheet(RenderCommandSheet* draw, double delta);
void Renderer_DrawManyRectangles(RenderCommandManyRectangle* draw);
Rectangle Renderer_RenderBmFont(bool drawTheText, BmFont* bmf, const char* text, Color color, Vector2 position);
void Renderer_DrawString(RenderCommandString* draw, double delta);
void Renderer_DrawTiles(RenderCommandTileLayer* draw);
void Renderer_Commit(SpriteBatch* render, Vector2 cameraOffset, double delta);
void Renderer_BeforeRender();
void Renderer_AfterRender();
void Renderer_Render(double delta);
uint16_t* Renderer_GetDefaultIndexBufferData();
bool Renderer_IsVsync();
void Renderer_UpdateVsync();
void Renderer_UpdateViewport();
void Renderer_UpdateScissor();
void Renderer_ApplyChanges();
void Renderer_ResetBackBuffer();
Rectangle Renderer_GetDrawableSize();
void Renderer_UpdateDisplayDimensions();
Point Renderer_GetScreenOffset();
Vector2 Renderer_GetScreenScale();
Rectangle Renderer_GetScreenBounds();
void Renderer_SetupCommit(double delta);
void Renderer_SetupRenderState();
int Renderer_GetFPS();
int Renderer_GetRenderTargetScale(); //TODO 2023 REMOVE THESE!
