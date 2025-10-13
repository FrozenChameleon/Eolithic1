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

#include "Renderer.h"

#include "../utils/Logger.h"
#include "RenderStream.h"
#include "RendererMacros.h"
#include "SDL3/SDL.h"
#include "../utils/Cvars.h"
#include "../render/Texture.h"
#include "../math/Math.h"
#include "../math/MathHelper.h"
#include "../font/BmFont.h"
#include "../globals/Align.h"
#include "../leveldata/DrawTile.h"
#include "../leveldata/AnimTile.h"
#include "../leveldata/Tile.h"
#include "../render/DrawInstance.h"
//#include "../render/SpriteBatch.h"
//#include "../render/DrawTool.h"
#include "../render/Sheet.h"
//#include "../resources/ResourceManagers.h"
#include "../core/Game.h"
#include "../service/Service.h"
#include "../utils/FpsTool.h"
//#include "../core/GameLoader.h"
#include "../core/GameUpdater.h"
//#include "../gamestate/GameStateManager.h"
#include "../components/Camera.h"
#define STBI_ONLY_PNG
#define STB_IMAGE_IMPLEMENTATION
#include "../../third_party/stb_image.h"
//#include "../font/FontMap.h"
//#include "../render/RenderTtFont.h"
#include "../../DebugDefs.h"
#include "../../GlobalDefs.h"
#include "../../GlobalDefs.h"

#define TILE_SIZE GLOBAL_DEF_TILE_SIZE

static const float _mCornerOffsetX[] = { 0.0f ,1.0f, 0.0f, 1.0f };
static const float _mCornerOffsetY[] = { 0.0f, 0.0f, 1.0f, 1.0f };

//static SpriteBatch _mOrangeSpriteBatch;
//static SpriteBatch _mOrangeSpriteBatchDrawHud;
static FPSTool _mFpsToolDraw;

static Rectangle _mScreenBounds;
static Vector2 _mScreenScale;
static Point _mScreenOffset;

static TtFontState _mFontState;

static bool _mIndexBufferDataSet;
static uint16_t _mIndexBufferData[MAX_INDICES];

static int _mCurrentDepth;
static Vector2 _mCurrentCameraPosition;
static BlendState _mCurrentBlendState;
static ShaderProgram* _mCurrentShaderProgram;
static ShaderProgram* _mGlobalShaderProgram;

static bool _mHasInitSpriteBatch;
static SpriteBatch _mOrangeSpriteBatch;
static SpriteBatch _mOrangeSpriteBatchHud;
static SpriteBatch _mOrangeSpriteBatchFinal;

static float GetCurrentDepthForRender()
{
	return (1.0f - ((float)(_mCurrentDepth) / 200.0f)); //Max layers is 200
}

int Renderer_InitSpriteBatch()
{
	if (_mHasInitSpriteBatch)
	{
		return 0;
	}

	SpriteBatch_Init(&_mOrangeSpriteBatch);
	SpriteBatch_Init(&_mOrangeSpriteBatchHud);
	SpriteBatch_Init(&_mOrangeSpriteBatchFinal);

	_mHasInitSpriteBatch = false;

	return 0;
}
void Renderer_SetGlobalShaderProgram(ShaderProgram* value)
{
	_mGlobalShaderProgram = value;
}
ShaderProgram* Renderer_GetGlobalShaderProgram()
{
	return _mGlobalShaderProgram;
}
void Renderer_INTERNAL_SetCurrentShaderProgram(ShaderProgram* value)
{
	_mCurrentShaderProgram = value;
}
ShaderProgram* Renderer_INTERNAL_GetCurrentShaderProgram()
{
	return _mCurrentShaderProgram;
}
void Renderer_INTERNAL_SetCurrentBlendState(BlendState value)
{
	_mCurrentBlendState = value;
}
BlendState Renderer_INTERNAL_GetCurrentBlendState()
{
	return _mCurrentBlendState;
}
void Renderer_INTERNAL_SetCurrentCameraPosition(Vector2 value)
{
	_mCurrentCameraPosition = value;
}
Vector2 Renderer_INTERNAL_GetCurrentCameraPosition()
{
	return _mCurrentCameraPosition;
}
void Renderer_INTERNAL_SetCurrentDepth(int value)
{
	_mCurrentDepth = value;
}
int Renderer_INTERNAL_GetCurrentDepth()
{
	return _mCurrentDepth;
}
Rectangle Renderer_GetWantedBackBufferBounds()
{
	Rectangle forcedBackBuffer = Service_PlatformGetForcedBackBufferSize();
	if (!Rectangle_IsEmpty(&forcedBackBuffer))
	{
		return forcedBackBuffer;
	}

	int internalRenderWidth = Utils_GetInternalRenderWidth();
	int internalRenderHeight = Utils_GetInternalRenderHeight();

	int mul = Renderer_GetRenderTargetScale();

#ifdef DEBUG_DEF_FORCE_LOWEST_BACK_BUFFER_SIZE
	mul = 1;
#endif

	Rectangle bounds;
	bounds.X = 0;
	bounds.Y = 0;
	bounds.Width = mul * internalRenderWidth;
	bounds.Height = mul * internalRenderHeight;
	return bounds;
}
void Renderer_SetupVerticesForTtFont(VertexPositionColorTexture* vertices, Color fontColor, int pos, const float* verts, const float* tcoords, const unsigned int* colors, int nverts)
{
	ColorFloat4 colorToUse;
	colorToUse.R = (float)(fontColor.R) / 0xFF;
	colorToUse.G = (float)(fontColor.G) / 0xFF;
	colorToUse.B = (float)(fontColor.B) / 0xFF;
	colorToUse.A = (float)(fontColor.A) / 0xFF;

	float renderDepth = GetCurrentDepthForRender();
	for (int i = 0; i < nverts; i += 1)
	{
		VertexPositionColorTexture* vertice = &vertices[pos + i];
		int offset = i * 2;
		vertice->Position.X = verts[offset];
		vertice->Position.Y = verts[offset + 1];
		vertice->Position.Z = renderDepth;
		vertice->TextureCoordinate.U = tcoords[offset];
		vertice->TextureCoordinate.V = tcoords[offset + 1];
		vertice->Color = colorToUse;
	}
}
const TtFontState* Renderer_GetTtFontState()
{
	return &_mFontState;
}
void Renderer_SetupTtFontState(const TtFontState* fontState)
{
	_mFontState = *fontState;
}
void Renderer_SetupVerticesFromVPCT4(VertexPositionColorTexture* vertices, int pos, const VertexPositionColorTexture4* sprite)
{
	vertices[pos + 0].Position = sprite->Position0; //UPPER LEFT
	vertices[pos + 1].Position = sprite->Position1; //UPPER RIGHT
	vertices[pos + 2].Position = sprite->Position2; //LOWER LEFT
	vertices[pos + 3].Position = sprite->Position3; //LOWER RIGHT

	vertices[pos + 0].TextureCoordinate = sprite->TextureCoordinate0; //UPPER LEFT
	vertices[pos + 1].TextureCoordinate = sprite->TextureCoordinate1; //UPPER RIGHT
	vertices[pos + 2].TextureCoordinate = sprite->TextureCoordinate2; //LOWER LEFT
	vertices[pos + 3].TextureCoordinate = sprite->TextureCoordinate3; //LOWER RIGHT

	vertices[pos + 0].Color = sprite->Color0;
	vertices[pos + 1].Color = sprite->Color1;
	vertices[pos + 2].Color = sprite->Color2;
	vertices[pos + 3].Color = sprite->Color3;
}
void Renderer_GenerateVertexInfo(Texture* texture, float sourceX, float sourceY, float sourceW, float sourceH,
	float destinationX, float destinationY, float destinationW, float destinationH,
	Color color, float originX, float originY, float rotationSin, float rotationCos, float depth, uint8_t effects)
{
	VertexPositionColorTexture4 sprite = { 0 };

	float cornerX = -originX * destinationW;
	float cornerY = -originY * destinationH;
	sprite.Position0.X = (
		(-rotationSin * cornerY) +
		(rotationCos * cornerX) +
		destinationX
		);
	sprite.Position0.Y = (
		(rotationCos * cornerY) +
		(rotationSin * cornerX) +
		destinationY
		);
	cornerX = (1.0f - originX) * destinationW;
	cornerY = -originY * destinationH;
	sprite.Position1.X = (
		(-rotationSin * cornerY) +
		(rotationCos * cornerX) +
		destinationX
		);
	sprite.Position1.Y = (
		(rotationCos * cornerY) +
		(rotationSin * cornerX) +
		destinationY
		);
	cornerX = -originX * destinationW;
	cornerY = (1.0f - originY) * destinationH;
	sprite.Position2.X = (
		(-rotationSin * cornerY) +
		(rotationCos * cornerX) +
		destinationX
		);
	sprite.Position2.Y = (
		(rotationCos * cornerY) +
		(rotationSin * cornerX) +
		destinationY
		);
	cornerX = (1.0f - originX) * destinationW;
	cornerY = (1.0f - originY) * destinationH;
	sprite.Position3.X = (
		(-rotationSin * cornerY) +
		(rotationCos * cornerX) +
		destinationX
		);
	sprite.Position3.Y = (
		(rotationCos * cornerY) +
		(rotationSin * cornerX) +
		destinationY
		);

	sprite.TextureCoordinate0.U = (_mCornerOffsetX[0 ^ effects] * sourceW) + sourceX;
	sprite.TextureCoordinate0.V = (_mCornerOffsetY[0 ^ effects] * sourceH) + sourceY;
	sprite.TextureCoordinate1.U = (_mCornerOffsetX[1 ^ effects] * sourceW) + sourceX;
	sprite.TextureCoordinate1.V = (_mCornerOffsetY[1 ^ effects] * sourceH) + sourceY;
	sprite.TextureCoordinate2.U = (_mCornerOffsetX[2 ^ effects] * sourceW) + sourceX;
	sprite.TextureCoordinate2.V = (_mCornerOffsetY[2 ^ effects] * sourceH) + sourceY;
	sprite.TextureCoordinate3.U = (_mCornerOffsetX[3 ^ effects] * sourceW) + sourceX;
	sprite.TextureCoordinate3.V = (_mCornerOffsetY[3 ^ effects] * sourceH) + sourceY;

	float renderDepth = GetCurrentDepthForRender();
	sprite.Position0.Z = renderDepth;
	sprite.Position1.Z = renderDepth;
	sprite.Position2.Z = renderDepth;
	sprite.Position3.Z = renderDepth;

	float colorR = (float)(color.R) / 0xFF;
	float colorG = (float)(color.G) / 0xFF;
	float colorB = (float)(color.B) / 0xFF;
	float colorA = (float)(color.A) / 0xFF;

	ColorFloat4 colorForSprite;
	colorForSprite.R = colorR;
	colorForSprite.G = colorG;
	colorForSprite.B = colorB;
	colorForSprite.A = colorA;

	sprite.Color0 = colorForSprite;
	sprite.Color1 = colorForSprite;
	sprite.Color2 = colorForSprite;
	sprite.Color3 = colorForSprite;

	Renderer_DrawVertexPositionColorTexture4(texture, &sprite);
}
void Renderer_PushSprite(Texture* texture, float sourceX, float sourceY, float sourceW, float sourceH,
	float destinationX, float destinationY, float destinationW, float destinationH,
	Color color, float originX, float originY, float rotationSin, float rotationCos, float depth, uint8_t effects)
{
	Renderer_GenerateVertexInfo(texture,
		sourceX,
		sourceY,
		sourceW,
		sourceH,
		destinationX,
		destinationY,
		destinationW,
		destinationH,
		color,
		originX,
		originY,
		rotationSin,
		rotationCos,
		depth,
		effects
	);
}
void Renderer_Draw9(Texture* texture, Vector2 position, Rectangle sourceRectangle, Color color, float rotation, Vector2 origin,
	Vector2 scale, SpriteEffects effects, float layerDepth
)
{
	float sourceX, sourceY, sourceW, sourceH;
	sourceX = sourceRectangle.X / (float)texture->mBounds.Width;
	sourceY = sourceRectangle.Y / (float)texture->mBounds.Height;
	sourceW = Math_SignumInt32(sourceRectangle.Width) * Math_MaxSingle(
		Math_abs((float)sourceRectangle.Width),
		MathHelper_GetMachineEpsilonFloat()
	) / (float)texture->mBounds.Width;
	sourceH = Math_SignumInt32(sourceRectangle.Height) * Math_MaxSingle(
		Math_abs((float)sourceRectangle.Height),
		MathHelper_GetMachineEpsilonFloat()
	) / (float)texture->mBounds.Height;
	scale.X *= sourceRectangle.Width;
	scale.Y *= sourceRectangle.Height;

	Renderer_PushSprite(
		texture,
		sourceX,
		sourceY,
		sourceW,
		sourceH,
		position.X,
		position.Y,
		scale.X,
		scale.Y,
		color,
		origin.X / sourceW / (float)texture->mBounds.Width,
		origin.Y / sourceH / (float)texture->mBounds.Height,
		(float)Math_sin(rotation),
		(float)Math_cos(rotation),
		layerDepth,
		(uint8_t)(effects & (SpriteEffects)0x03)
	);
}
void Renderer_Draw99(Texture* texture, Vector2 position, Rectangle sourceRectangle, Color color, float rotation,
	Vector2 origin, float scale, SpriteEffects effects, float layerDepth
) {
	float sourceX, sourceY, sourceW, sourceH;
	float destW = scale;
	float destH = scale;

	sourceX = sourceRectangle.X / (float)texture->mBounds.Width;
	sourceY = sourceRectangle.Y / (float)texture->mBounds.Height;
	sourceW = Math_SignumInt32(sourceRectangle.Width) * Math_MaxSingle(
		Math_abs((float)sourceRectangle.Width),
		MathHelper_GetMachineEpsilonFloat()
	) / (float)texture->mBounds.Width;
	sourceH = Math_SignumInt32(sourceRectangle.Height) * Math_MaxSingle(
		Math_abs((float)sourceRectangle.Height),
		MathHelper_GetMachineEpsilonFloat()
	) / (float)texture->mBounds.Height;
	destW *= sourceRectangle.Width;
	destH *= sourceRectangle.Height;

	Renderer_PushSprite(
		texture,
		sourceX,
		sourceY,
		sourceW,
		sourceH,
		position.X,
		position.Y,
		destW,
		destH,
		color,
		origin.X / sourceW / (float)texture->mBounds.Width,
		origin.Y / sourceH / (float)texture->mBounds.Height,
		(float)Math_sin(rotation),
		(float)Math_cos(rotation),
		layerDepth,
		(uint8_t)(effects & (SpriteEffects)0x03)
	);
}
void Renderer_Draw3(Texture* texture, Rectangle destinationRectangle, Color color)
{
	Renderer_PushSprite(
		texture,
		0.0f,
		0.0f,
		1.0f,
		1.0f,
		destinationRectangle.X,
		destinationRectangle.Y,
		destinationRectangle.Width,
		destinationRectangle.Height,
		color,
		0.0f,
		0.0f,
		0.0f,
		1.0f,
		0.0f,
		0
	);
}
void Renderer_Draw8(Texture* texture, Rectangle destinationRectangle, Rectangle sourceRectangle, Color color,
	float rotation, Vector2 origin, SpriteEffects effects, float layerDepth
) {
	float sourceX, sourceY, sourceW, sourceH;

	sourceX = sourceRectangle.X / (float)texture->mBounds.Width;
	sourceY = sourceRectangle.Y / (float)texture->mBounds.Height;
	sourceW = Math_SignumInt32(sourceRectangle.Width) * Math_MaxSingle(
		Math_abs((float)sourceRectangle.Width),
		MathHelper_GetMachineEpsilonFloat()
	) / (float)texture->mBounds.Width;
	sourceH = Math_SignumInt32(sourceRectangle.Height) * Math_MaxSingle(
		Math_abs((float)sourceRectangle.Height),
		MathHelper_GetMachineEpsilonFloat()
	) / (float)texture->mBounds.Height;

	Renderer_PushSprite(
		texture,
		sourceX,
		sourceY,
		sourceW,
		sourceH,
		destinationRectangle.X,
		destinationRectangle.Y,
		destinationRectangle.Width,
		destinationRectangle.Height,
		color,
		origin.X / sourceW / (float)texture->mBounds.Width,
		origin.Y / sourceH / (float)texture->mBounds.Height,
		(float)Math_sin(rotation),
		(float)Math_cos(rotation),
		layerDepth,
		(uint8_t)(effects & (SpriteEffects)0x03)
	);
}
void Renderer_Draw4(
	Texture* texture,
	Vector2 position,
	Rectangle sourceRectangle,
	Color color
) {
	float sourceX, sourceY, sourceW, sourceH;
	float destW, destH;

	sourceX = sourceRectangle.X / (float)texture->mBounds.Width;
	sourceY = sourceRectangle.Y / (float)texture->mBounds.Height;
	sourceW = sourceRectangle.Width / (float)texture->mBounds.Width;
	sourceH = sourceRectangle.Height / (float)texture->mBounds.Height;
	destW = sourceRectangle.Width;
	destH = sourceRectangle.Height;

	Renderer_PushSprite(
		texture,
		sourceX,
		sourceY,
		sourceW,
		sourceH,
		position.X,
		position.Y,
		destW,
		destH,
		color,
		0.0f,
		0.0f,
		0.0f,
		1.0f,
		0.0f,
		0
	);
}
void Renderer_DrawSheet(RenderCommandSheet* draw, double delta)
{
	SpriteEffects effects = Renderer_GetEffects(draw->mFlipX, draw->mFlipY);
	Texture* sheetTex = draw->mTexture;
	if (!draw->mIsRectangle)
	{
		if (!draw->mIsInterpolated)
		{
			Renderer_Draw9(sheetTex, Vector2_Add(draw->mPosition, draw->mOrigin), draw->mSourceRectangle, draw->mColor,
				Math_ToRadians(draw->mRotation), draw->mOrigin, draw->mScale, effects, draw->mDepth);
		}
		else
		{
			Vector2 position = { (float)Utils_GetInterpolated(delta, draw->mPosition.X, draw->mLastPosition.X) ,
				(float)Utils_GetInterpolated(delta, draw->mPosition.Y, draw->mLastPosition.Y) };
			Renderer_Draw9(sheetTex, Vector2_Add(position, draw->mOrigin),
				draw->mSourceRectangle, draw->mColor, Math_ToRadians(draw->mRotation), draw->mOrigin, draw->mScale, effects, draw->mDepth);
		}
	}
	else
	{
		Renderer_Draw8(sheetTex, draw->mDestinationRectangle, draw->mSourceRectangle, draw->mColor, draw->mRotation, Vector2_Zero, effects, draw->mDepth);
	}
}
void Renderer_DrawManyRectangles(DrawInstance* draw)
{
	/*
	const std::vector<OeDrawRectangle>& manyRectangles = *draw->mManyRectangles;

	for (int i = 0; i < manyRectangles.size(); i += 1)
	{
		Draw(draw->mTexture, manyRectangles[i].mRectangle,
			draw->mSourceRectangle, manyRectangles[i].mColor, 0, Vector2_Zero, SpriteEffects_None, draw->mDepth);
	}
	*/
}
static BmFont* GetBmFont(const char* font)
{
	return NULL;

	//return OeResourceManagers::FontManager.GetResourceData(font);
}
Rectangle Renderer_RenderBmFont(bool drawTheText, BmFont* font, const char* text, Color color, Vector2 position)
{
	return Rectangle_Empty;
	/*
	Texture* tex = font->GetFontTexture();
	if (tex == nullptr)
	{
		return Rectangle::Empty;
	}

	int boundsMaxWidth = 0;
	int boundsWidth = 0;
	int boundsHeight = font->GetBaseHeight();
	float currentX = position.X;
	float currentY = position.Y;

	for (int i = 0; i < text.size(); i += 1)
	{
		if (text[i] == '\n')
		{
			boundsWidth = 0;
			boundsHeight += font->GetLineHeight();
			currentY += font->GetLineHeight();
			currentX = position.X;
		}
		else
		{
			BmFontDataChar* bmChar = nullptr;
			auto it = font->_mFontCharMap.find(text[i]); //TryGetValue equivalent
			if (it != font->_mFontCharMap.end())
			{
				bmChar = &it->second;
			}

			if (bmChar != nullptr)
			{
				boundsWidth += bmChar->XAdvance;
				if (boundsWidth > boundsMaxWidth)
				{
					boundsMaxWidth = boundsWidth;
				}

				if (drawTheText)
				{
					Draw(tex, Vector2(currentX + bmChar->XOffset, currentY + bmChar->YOffset), Rectangle(bmChar->X, bmChar->Y, bmChar->Width, bmChar->Height), color);
				}

				currentX += bmChar->XAdvance;
			}
		}
	}

	return Rectangle(0, 0, boundsMaxWidth, boundsHeight);
	*/
}
void Renderer_DrawString(DrawInstance* draw, double delta)
{
	/*
	const std::string& strToDraw = *draw->mString;

	Vector2 offset = Vector2_Zero;

	if (draw->mAlignmentX == OeAlign::CENTER || draw->mAlignmentX == OeAlign::RIGHT ||
		draw->mAlignmentY == OeAlign::CENTER || draw->mAlignmentY == OeAlign::BOTTOM)
	{
		Rectangle layout = draw->mFont->GetBounds(strToDraw, draw->mDoNotReplaceFont);

		if (draw->mAlignmentX == OeAlign::CENTER)
		{
			offset.X = -(layout.Width / 2.0f);
		}
		else if (draw->mAlignmentX == OeAlign::RIGHT)
		{
			offset.X = -layout.Width;
		}
		if (draw->mAlignmentY == OeAlign::CENTER)
		{
			offset.Y = -(layout.Height / 2.0f);
		}
		else if (draw->mAlignmentY == OeAlign::BOTTOM)
		{
			offset.Y = -layout.Height;
		}
	}

	Vector2 offsetPosition = draw->mPosition + offset;
	Vector2 offsetLastPosition = draw->mLastPosition + offset;
	if (draw->mIsLockedToInt)
	{
		offsetPosition = Vector2((int)(offsetPosition.X), (int)(offsetPosition.Y));
		offsetLastPosition = Vector2((int)(offsetLastPosition.X), (int)(offsetLastPosition.Y));
	}

	Vector2 finalPos;
	if (draw->mIsInterpolated)
	{
		finalPos = Vector2((float)(Utils_GetInterpolated(delta, offsetPosition.X, offsetLastPosition.X)),
			(float)(Utils_GetInterpolated(delta, offsetPosition.Y, offsetLastPosition.Y)));
	}
	else
	{
		finalPos = offsetPosition;
	}

	bool doNotRender = false;
	//#if !DISABLE_TT_FONT
	const OeFontMapData* replacement = OeFontMap::GetReplacement(draw->mFont->GetFontName());
	if (replacement != nullptr && !draw->mDoNotReplaceFont)
	{
		doNotRender = true;
		if (replacement->mIsBitmap)
		{
			RenderBmFont(true, GetBmFont(replacement->mFontName), strToDraw, draw->mColor, finalPos);
		}
		else
		{
			OeRenderTtFont::Draw(replacement, strToDraw, draw->mColor, finalPos);
		}
	}
	//#endif
	if (!doNotRender)
	{
		RenderBmFont(true, draw->mFont, strToDraw, draw->mColor, finalPos);
	}
	*/
}
void Renderer_DrawTiles(DrawInstance* draw)
{
	/*
	std::vector<OeTile*>& tileData = *draw->mTileData;
	Rectangle tileDataBounds = draw->mTileDataBounds;
	Vector2 origin = Vector2(TILE_SIZE / 2, TILE_SIZE / 2);
	int depth = draw->mDepth;
	for (int i = draw->mX1; i < draw->mX2; i += 1)
	{
		for (int j = draw->mY1; j < draw->mY2; j += 1)
		{
			//Draw The Tile
			Vector2 position = Vector2(i * TILE_SIZE, j * TILE_SIZE);
			int gridPos = i + (j * tileDataBounds.Width);
			OeDrawTile* drawTile = &tileData[gridPos]->mDrawTiles[draw->mLayer];
			if (drawTile->mPoint.X != -1)
			{
				Point point = OeDrawTile::GetCorrectPoint(drawTile);
				Draw(draw->mTexture, position + origin, Rectangle(point.X, point.Y, TILE_SIZE, TILE_SIZE), draw->mColor, Math_ToRadians(drawTile->mRotation),
					origin, 1, Renderer_GetEffects(drawTile->mFlipX, drawTile->mFlipY), depth);
			}
			else if (drawTile->mAnimation.size() != 0)
			{
				OeAnimTile* animTile = OeResourceManagers::AnimTileManager.GetResourceData(drawTile->mAnimation);
				if (animTile != nullptr)
				{
					//Draw The Anim Tile
					bool flippingX = drawTile->mFlipX ? !animTile->mIsFlipX : animTile->mIsFlipX;
					bool flippingY = drawTile->mFlipY ? !animTile->mIsFlipY : animTile->mIsFlipY;

					SpriteEffects effects = Renderer_GetEffects(flippingX, flippingY);

					if (animTile->mIsWrap)
					{
						Rectangle source = Rectangle(0 + animTile->_mWrapOffset.X, 0 + animTile->_mWrapOffset.Y, TILE_SIZE, TILE_SIZE);
						Vector2 halfRect = Vector2(TILE_SIZE / 2, TILE_SIZE / 2);
						Draw(OeSheet::GetTexture(animTile->_mWrapSheet), position + origin - halfRect + halfRect, source, draw->mColor,
							Math_ToRadians(animTile->mRotation + drawTile->mRotation), halfRect, animTile->mScaler, effects, depth);
					}
					else
					{
						OeSheet* sheet = OeAnimTile::GetAnimationSheet(animTile);
						Rectangle rect = sheet->mRectangle;
						Vector2 halfRect = Vector2(rect.Width / 2, rect.Height / 2);
						Rectangle source = Rectangle(rect.X, rect.Y, rect.Width, rect.Height);
						BlendState oldBlendState = _mCurrentBlendState;
						if (animTile->mIsAdditive)
						{
							_mCurrentBlendState = BlendState::Additive;
						}
						Draw(OeSheet::GetTexture(sheet), position + origin - halfRect + halfRect, source, draw->mColor,
							Math_ToRadians(animTile->mRotation + drawTile->mRotation),
							halfRect, animTile->mScaler, effects, depth);
						if (animTile->mIsAdditive)
						{
							_mCurrentBlendState = oldBlendState;
						}
					}
				}
				else
				{
					Draw(OeDrawTool::GetSinglePixel(), Rectangle((int)position.X, (int)position.Y, TILE_SIZE, TILE_SIZE), Color::Red);
				}
			}
		}
	}
	*/
}
static uint64_t DrawTheInstance(uint8_t* buffer, uint64_t position, double delta, bool drawSheet, bool drawManyRectangle, bool drawString, bool drawTileLayer)
{
	_mCurrentBlendState = BLENDSTATE_NONPREMULTIPLIED;
	_mCurrentShaderProgram = _mGlobalShaderProgram;

	uint8_t drawType = *(buffer + position);
	uint64_t sizeToReturn = 0;
	switch (drawType)
	{
	case RENDERER_TYPE_SHEET:
	{
		sizeToReturn = sizeof(RenderCommandSheet);
		if (drawSheet)
		{
			RenderCommandSheet* commandSheet = (RenderCommandSheet*)(buffer + position);
			_mCurrentBlendState = (BlendState)commandSheet->mBlendState;
			if (commandSheet->mShaderProgram != NULL)
			{
				_mCurrentShaderProgram = commandSheet->mShaderProgram;
			}
			int32_t passes = commandSheet->mExtraPasses + 1;
			for (int32_t i = 0; i < passes; i += 1)
			{
				Renderer_DrawSheet(commandSheet, delta);
			}
		}
	}
	break;
	/*
	case RENDERER_TYPE_MANY_RECTANGLE:
	{
		sizeToReturn = sizeof(RenderCommandManyRectangle);
		if (drawManyRectangle)
		{
			OeRenderer::DrawManyRectangles((OeRenderCommandManyRectangle*)(buffer + position));
		}
	}
	break;
	case RENDERER_TYPE_STRING:
	{
		sizeToReturn = sizeof(RenderCommandString);
		if (drawString)
		{
			OeRenderer::DrawString((OeRenderCommandString*)(buffer + position), delta);
		}
	}
	break;
	case RENDERER_TYPE_TILE_LAYER:
	{
		sizeToReturn = sizeof(RenderCommandTileLayer);
		if (drawTileLayer)
		{
			OeRenderer::DrawTiles((OeRenderCommandTileLayer*)(buffer + position));
		}
	}
	break;
	*/
	}

	return sizeToReturn;
}
static void DrawTheDepth(int32_t depth, RenderStream* drawLayer, double delta, bool drawSheet, bool drawManyRectangle, bool drawString, bool drawTileLayer)
{
	_mCurrentDepth = depth;
	uint64_t currentPosition = 0;
	uint64_t endPosition = DynamicByteBuffer_GetLength(drawLayer->_mBuffer);
	uint8_t* buffer = DynamicByteBuffer_GetBuffer(drawLayer->_mBuffer);
	while (currentPosition < endPosition)
	{
		uint64_t sizeOfCommand = DrawTheInstance(buffer, currentPosition, delta, drawSheet, drawManyRectangle, drawString, drawTileLayer);
		currentPosition += sizeOfCommand;
	}
}
static void DrawEverythingForwards(RenderStream* draws, double delta, bool drawSheet, bool drawManyRectangle, bool drawString, bool drawTileLayer)
{
	for (int32_t i = 0; i < SPRITEBATCH_RENDER_STREAMS_LEN; i += 1)
	{
		DrawTheDepth(i, &draws[i], delta, drawSheet, drawManyRectangle, drawString, drawTileLayer);
	}
}
/*
static void DrawEverythingBackwards(std::vector<std::vector<DrawInstance>>& draws, double delta, bool drawSheet, bool drawManyRectangle, bool drawString, bool drawTileLayer)
{
	for (int i = (draws.size() - 1); i >= 0; i -= 1)
	{
		DrawTheDepth(i, draws[i], delta, drawSheet, drawManyRectangle, drawString, drawTileLayer);
	}
}
*/
void Renderer_Commit(SpriteBatch* render, Vector2 cameraOffset, double delta)
{
	_mCurrentCameraPosition = cameraOffset;
	_mCurrentBlendState = BLENDSTATE_NONPREMULTIPLIED;
	_mCurrentShaderProgram = NULL;

	RenderStream* draws = render->_mRenderStreams;
	//std::vector<std::vector<OeDrawInstance>>& draws = render->GetDraws();

	Renderer_BeforeCommit();

	bool drawTileLayer = true;

	/*
	*
	if (!OeService::PlatformDisablesDepthBufferForRender())
	{
		EnableDepthBufferWrite();

		DrawEverythingBackwards(draws, delta, false, false, false, true);
		drawTileLayer = false;

		FlushBatch();

		DisableDepthBufferWrite();
	}

	DrawEverythingForwards(draws, delta, true, true, true, drawTileLayer);
	*/

	DrawEverythingForwards(draws, delta, true, true, true, drawTileLayer);

	Renderer_AfterCommit();
}
void Renderer_LogInfo(const char* msg)
{
	Logger_LogInformation(msg);
}
void Renderer_LogWarning(const char* msg)
{
	Logger_LogWarning(msg);
}
void Renderer_LogError(const char* msg)
{
	Logger_LogError(msg);
}
SpriteEffects Renderer_GetEffects(bool flipX, bool flipY)
{
	SpriteEffects effects;

	if (flipX && flipY)
	{
		effects = (SpriteEffects)((SPRITEEFFECTS_FLIPHORIZONTALLY | SPRITEEFFECTS_FLIPVERTICALLY));
	}
	else if (flipX)
	{
		effects = SPRITEEFFECTS_FLIPHORIZONTALLY;
	}
	else if (flipY)
	{
		effects = SPRITEEFFECTS_FLIPVERTICALLY;
	}
	else
	{
		effects = SPRITEEFFECTS_NONE;
	}

	return effects;
}
int Renderer_ImageRead(void* context, char* data, int size)
{
	SDL_IOStream* rwop = (SDL_IOStream*)(context);
	return SDL_ReadIO(rwop, data, size);
}
void Renderer_ImageSkip(void* context, int n)
{
	SDL_IOStream* rwop = (SDL_IOStream*)(context);
	SDL_SeekIO(rwop, n, SDL_IO_SEEK_CUR);
}
int Renderer_ImageEndOfFile(void* context)
{
	SDL_IOStream* rwop = (SDL_IOStream*)(context);
	int64_t size = SDL_GetIOSize(rwop);
	int64_t loc = SDL_TellIO(rwop);
	return size == loc ? 1 : 0;
}
ImagePixelData Renderer_CreateImagePixelData(FixedByteBuffer* blob)
{
	SDL_IOStream* rwops = SDL_IOFromMem(FixedByteBuffer_GetBuffer(blob), FixedByteBuffer_GetLength(blob));

	stbi_io_callbacks cb;
	cb.eof = Renderer_ImageEndOfFile;
	cb.read = Renderer_ImageRead;
	cb.skip = Renderer_ImageSkip;

	int imageWidth;
	int imageHeight;
	int imageFormat;
	uint8_t* imageData;

	imageData = stbi_load_from_callbacks(&cb, rwops, &imageWidth, &imageHeight, &imageFormat, STBI_rgb_alpha);

	SDL_CloseIO(rwops);

	ImagePixelData pixelImageData;
	pixelImageData.mData = imageData;
	pixelImageData.mWidth = imageWidth;
	pixelImageData.mHeight = imageHeight;

	return pixelImageData;
}
void* Renderer_CreateSurface(FixedByteBuffer* blob)
{
	return NULL;
	/* //Not needed.
	ImagePixelData image = Renderer_CreateImagePixelData(blob);
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(image.mData, image.mWidth, image.mHeight, 8 * 4, image.mWidth * 4, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	return surface;
	*/
}
void Renderer_Render(double delta)
{
	Renderer_UpdateDisplayDimensions();

	Renderer_BeforeRender();

	Renderer_SetupCommit(delta);

	Renderer_AfterRender();
}
uint16_t* Renderer_GetDefaultIndexBufferData()
{
	if (_mIndexBufferDataSet)
	{
		return _mIndexBufferData;
	}

	for (int i = 0, j = 0; i < MAX_INDICES; i += 6, j += 4)
	{
		_mIndexBufferData[i] = (uint16_t)(j);
		_mIndexBufferData[i + 1] = (uint16_t)(j + 1);
		_mIndexBufferData[i + 2] = (uint16_t)(j + 2);
		_mIndexBufferData[i + 3] = (uint16_t)(j + 3);
		_mIndexBufferData[i + 4] = (uint16_t)(j + 2);
		_mIndexBufferData[i + 5] = (uint16_t)(j + 1);
	}

	_mIndexBufferDataSet = true;

	return _mIndexBufferData;
}
bool Renderer_IsVsync()
{
	return Cvars_GetAsBool(CVARS_USER_IS_VSYNC);
}
void Renderer_UpdateDisplayDimensions()
{
	float width = 0;
	float height = 0;

	Rectangle drawable = Renderer_GetDrawableSize();
	float currentWidth = drawable.Width;
	float currentHeight = drawable.Height;

	int internalRenderWidth = Cvars_GetAsInt(CVARS_ENGINE_INTERNAL_RENDER_WIDTH);
	int internalRenderHeight = Cvars_GetAsInt(CVARS_ENGINE_INTERNAL_RENDER_HEIGHT);

	if (Cvars_GetAsInt(CVARS_USER_DRAW_MODE) == RENDERER_DRAWMODE_PIXELPERFECT)
	{
		if (internalRenderWidth > currentWidth || internalRenderHeight > currentHeight)
		{
			Cvars_SetAsInt(CVARS_USER_DRAW_MODE, RENDERER_DRAWMODE_ASPECT);
		}
	}

	int drawMode = Cvars_GetAsInt(CVARS_USER_DRAW_MODE);
	drawMode = RENDERER_DRAWMODE_ASPECT; //Force this for now
	if ((drawMode == RENDERER_DRAWMODE_ASPECT) || (drawMode == RENDERER_DRAWMODE_SUPERSAMPLE))
	{
		if (Utils_GetCurrentInternalRatio() < Utils_GetCurrentHardwareRatio()) // Conform to aspect ratio
		{
			height = currentHeight;
			width = height * Utils_GetCurrentInternalRatio();

			_mScreenScale.X = internalRenderWidth / width;
			_mScreenScale.Y = _mScreenScale.X;
		}
		else
		{
			width = currentWidth;
			height = width / Utils_GetCurrentInternalRatio();

			_mScreenScale.Y = internalRenderHeight / height;
			_mScreenScale.X = _mScreenScale.Y;
		}
	}
	else if (drawMode == RENDERER_DRAWMODE_PIXELPERFECT)
	{
		Rectangle backBuffer = Renderer_GetWantedBackBufferBounds();
		width = backBuffer.Width;
		height = backBuffer.Height;

		_mScreenScale.X = internalRenderWidth / width; // calculating from either width or height is fine due to perfect scaling
		_mScreenScale.Y = _mScreenScale.X;
	}
	else if (drawMode == RENDERER_DRAWMODE_STRETCH)
	{
		width = currentWidth;
		height = currentHeight;

		_mScreenScale.X = internalRenderWidth / width;
		_mScreenScale.Y = internalRenderHeight / height;
	}

	float offsetX = (currentWidth - width) / 2.0f;
	float offsetY = (currentHeight - height) / 2.0f;
	_mScreenOffset.X = (int)(offsetX);
	_mScreenOffset.Y = (int)(offsetY);

	_mScreenBounds.X = _mScreenOffset.X;
	_mScreenBounds.Y = _mScreenOffset.Y;
	_mScreenBounds.Width = (int)(width);
	_mScreenBounds.Height = (int)(height);
}
Point Renderer_GetScreenOffset()
{
	return _mScreenOffset;
}
Vector2 Renderer_GetScreenScale()
{
	return _mScreenScale;
}
Rectangle Renderer_GetScreenBounds()
{
	return _mScreenBounds;
}
void Renderer_SetupCommit(double delta)
{
	FPSTool_Update(&_mFpsToolDraw, delta);

	//TODO C99
	/*
	if (GameLoader_IsLoading())
	{
		Renderer_Commit(&_mOrangeSpriteBatchHud, Vector2_Zero, 1);
		return;
	}
	*/

	double stepLength = Utils_GetNormalStepLength();
	double drawDelta;
	if (!GameUpdater_IsInterpolated())
	{
		drawDelta = stepLength;
	}
	else
	{
		drawDelta = GameUpdater_GetDeltaAccumulator();
	}
	//Camera* camera = GameStateManager_GetCurrentRenderCamera();
	//Vector2 cam = Camera_GetInterpCameraAsVector2(camera, drawDelta);
	//Vector2 hud = { camera->mWorldWidth / 2, camera->mWorldHeight / 2 };
	//Renderer_Commit(&_mOrangeSpriteBatch, cam, drawDelta); //TODO C99
	Vector2 hud = { 640, 360 };
	Renderer_Commit(&_mOrangeSpriteBatchHud, hud, drawDelta);
}
void Renderer_SetupRenderState()
{
	SpriteBatch_Clear(&_mOrangeSpriteBatchHud);
	Sheet* sheet = Sheet_GetSheet("monsterEyeShootCatchUp_00");
	for (int i = 0; i < 1; i += 1)
	{
		Vector2 position;
		position.X = 25 * i;
		position.Y = 0;
		SpriteBatch_Draw(&_mOrangeSpriteBatchHud, sheet->mTextureResource->mData, Color_White, 0, NULL,
			position, sheet->mRectangle, Vector2_One, 0, false, false, Vector2_Zero);
	}

	/*
	if (GameLoader_IsLoading())
	{
		_mOrangeSpriteBatch.Clear();
		_mOrangeSpriteBatchDrawHud.Clear();
		GameLoader_Draw(&_mOrangeSpriteBatchDrawHud);
		return;
	}

	_mOrangeSpriteBatch.Clear();
	GameStateManager_Draw(&_mOrangeSpriteBatch);
	_mOrangeSpriteBatchDrawHud.Clear();
	GameStateManager_DrawHud(&_mOrangeSpriteBatchDrawHud);
	*/
}
int Renderer_GetFPS()
{
	return _mFpsToolDraw.mCurrentFps;
}
int Renderer_GetRenderTargetScale()
{
	int internalRenderWidth = Utils_GetInternalRenderWidth();
	int internalRenderHeight = Utils_GetInternalRenderHeight();

	int mul = Cvars_GetAsInt(CVARS_USER_INTERNAL_RESOLUTION_MULTIPLE);
	if (mul <= 0) //Auto
	{
		Rectangle drawableSize = Renderer_GetDrawableSize();
		if (!Rectangle_IsEmpty(&drawableSize))
		{
			int widthCheck = drawableSize.Width / internalRenderWidth;
			int heightCheck = drawableSize.Height / internalRenderHeight;
			if (widthCheck >= heightCheck)
			{
				mul = widthCheck;
			}
			else
			{
				mul = heightCheck;
			}
		}
		else
		{
			mul = 1;
		}
	}

	if (mul <= 0)
	{
		mul = 1;
	}

	return mul;
}
