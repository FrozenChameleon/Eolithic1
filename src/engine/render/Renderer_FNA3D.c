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

#include "RendererMacros.h"
#include "../../DebugDefs.h"
#include "../service/Service.h"
#include "../core/Game.h"
#include "../utils/Cvars.h"
#include "../render/Texture.h"
#include "../utils/Utils.h"
#include "../leveldata/DrawTile.h"
#include "../leveldata/Tile.h"
#include "../leveldata/AnimTile.h"
//#include "../resources/ResourceManagers.h"
//#include "../render/DrawTool.h"
#include "../render/Sheet.h"
#include "../globals/Align.h"
#include "../math/Math.h"
#include "../math/Rectangle.h"
#include "../math/Matrix.h"
#include "../math/MathHelper.h"
#include "../io/File.h"
//#include "RenderTtFont.h"
#include "../utils/Utils.h"
#include "FNA3D.h"
#include "FNA3D_Image.h"
#include "SDL3/SDL.h"
#define MOJOSHADER_NO_VERSION_INCLUDE
#define MOJOSHADER_EFFECT_SUPPORT
#include <mojoshader.h>
#include <mojoshader_effects.h>
#include "../../GlobalDefs.h"

#define MULTI_COLOR_REPLACE_LEN 24
#define TRANSFORM_DEST_LEN 16

typedef struct Effect
{
	FNA3D_Effect* mHandle;
	MOJOSHADER_effect* mData;
	MOJOSHADER_effectStateChanges mStateChanges;
} Effect;

static const char* SHADER_PARAMETER_IS_TOTAL_WHITE_HIT_FLASH = "IsTotalWhiteHitFlash";
static const char* SHADER_PARAMETER_PERFORM_ALPHA_TEST = "PerformAlphaTest";
static const char* SHADER_PARAMETER_MATRIX_TRANSFORM = "MatrixTransform";
static const char* SHADER_PARAMETER_SHADER_TYPE = "ShaderType";
static const char* SHADER_PARAMETER_COLOR_LENGTH = "ColorLength";
static const char* SHADER_PARAMETER_COLOR_TARGET_0 = "ColorTarget0";
static const char* SHADER_PARAMETER_COLOR_REPLACE_0 = "ColorReplace0";
static const char* SHADER_PARAMETER_COLOR_TARGET_1 = "ColorTarget1";
static const char* SHADER_PARAMETER_COLOR_REPLACE_1 = "ColorReplace1";
static const char* SHADER_PARAMETER_COLOR_TARGET_2 = "ColorTarget2";
static const char* SHADER_PARAMETER_COLOR_REPLACE_2 = "ColorReplace2";
static const char* SHADER_PARAMETER_COLOR_TARGET_3 = "ColorTarget3";
static const char* SHADER_PARAMETER_COLOR_REPLACE_3 = "ColorReplace3";
static const char* SHADER_PARAMETER_COLOR_REPLACE_ALPHA = "ColorReplaceAlpha";

static float _mInternalWidth;
static float _mInternalHeight;
static Vector3 _mInternalWorldTranslation;
static float _mInternalWidthRender;
static float _mInternalHeightRender;
static Matrix _mMatrix;
static FNA3D_PresentationParameters _mDeviceParams;
static FNA3D_Device* _mDeviceContext;
static FNA3D_Vec4 _mClearColor;
static void* _mDeviceWindowHandle;
static Effect _mEffect;
static FNA3D_VertexElement _mVertexElements[3];
static FNA3D_RasterizerState _mRasterizerState;
static FNA3D_Color _mWhiteBlendFactor = { 0xFF, 0xFF, 0xFF,0xFF };
static FNA3D_Buffer* _mIndexBuffer;
static FNA3D_SamplerState _mSamplerState;
static FNA3D_DepthStencilState _mDepthStencilState;
//static int _mVertexBufferCounter;
static int _mBatchNumber;
//Setup Render State Stuff
static float _mMultiColorReplaceData[MULTI_COLOR_REPLACE_LEN];
static float _mTransformDest[TRANSFORM_DEST_LEN];
static FNA3D_Texture* _mLastUsedTexture;
static BlendState _mLastUsedBlendState = BLENDSTATE_INVALID;
//
static FNA3D_RenderTargetBinding _mOffscreenTargetBinding;
static Texture _mOffscreenTarget;
static bool _mIsDrawingFromOffscreenTarget;
static bool _mIsDrawingToOffscreenTarget;
static Rectangle _mVirtualBufferBounds;
static Rectangle _mActualBufferBounds;

static Rectangle GetCurrentBufferBounds()
{
	if (_mIsDrawingToOffscreenTarget)
	{
		return _mVirtualBufferBounds;
	}
	else
	{
		return _mActualBufferBounds;
	}
}

static bool IsDepthBufferDisabled()
{
	return Service_PlatformDisablesDepthBufferForRender();
}

static bool IsOffscreenTargetNeeded()
{
	return Service_PlatformRequiresOffscreenTargetForRender();
}

static void InvalidateNextSetupRenderState()
{
	_mLastUsedTexture = NULL;
	_mLastUsedBlendState = BLENDSTATE_INVALID;
}

typedef struct DrawState
{
	FNA3D_Texture* mTexture;
	BlendState mBlendState;
	ShaderProgram* mShaderProgram;
	Vector2 mCameraPosition;
} DrawState;

static bool DrawState_IsEqualTo(const DrawState* ds, const DrawState* other)
{
	if (ds->mTexture != other->mTexture)
	{
		return false;
	}

	if (ds->mBlendState != other->mBlendState)
	{
		return false;
	}

	if (ds->mShaderProgram != other->mShaderProgram)
	{
		return false;
	}
	
	if (Vector2_NotEqual(ds->mCameraPosition, other->mCameraPosition))
	{
		return false;
	}

	return true;
}
typedef struct DrawBatch
{
	int32_t mOffset;
	int32_t mLength;
	DrawState mDrawState;
} DrawBatch;

void DrawBatch_Init(DrawBatch* db)
{
	db->mOffset = 0;
	db->mLength = 0;
	memset(&db->mDrawState, 0, sizeof(DrawState));
}
int DrawBatch_GetEndPositionInVertexBuffer(const DrawBatch* db)
{
	return db->mOffset + db->mLength;
}

typedef struct VertexBufferInstance
{
	FNA3D_VertexBufferBinding mVertexBufferBinding;
	FNA3D_Buffer* mVertexBuffer;
	VertexPositionColorTexture* mVertices;
} VertexBufferInstance;

void VertexBufferInstance_Init(VertexBufferInstance* vbi)
{
	vbi->mVertexBuffer = FNA3D_GenVertexBuffer(_mDeviceContext, 1, FNA3D_BUFFERUSAGE_WRITEONLY, MAX_VERTICES * sizeof(VertexPositionColorTexture));
	vbi->mVertices = Utils_malloc(sizeof(VertexPositionColorTexture) * MAX_VERTICES);

	FNA3D_VertexDeclaration vertexDeclaration = { 0 };
	vertexDeclaration.elementCount = 3;
	vertexDeclaration.vertexStride = sizeof(VertexPositionColorTexture);
	vertexDeclaration.elements = _mVertexElements;

	memset(&vbi->mVertexBufferBinding, 0, sizeof(FNA3D_VertexBufferBinding));
	vbi->mVertexBufferBinding.instanceFrequency = 0;
	vbi->mVertexBufferBinding.vertexBuffer = vbi->mVertexBuffer;
	vbi->mVertexBufferBinding.vertexDeclaration = vertexDeclaration;
	vbi->mVertexBufferBinding.vertexOffset = 0;
}
void VertexBufferInstance_SetData(VertexBufferInstance* vbi, int32_t offset, int32_t length)
{
	int32_t start = offset * sizeof(VertexPositionColorTexture);
	FNA3D_SetVertexBufferData(_mDeviceContext, vbi->mVertexBuffer, start, vbi->mVertices, length,
		sizeof(VertexPositionColorTexture), sizeof(VertexPositionColorTexture), FNA3D_SETDATAOPTIONS_DISCARD);
}

static DrawBatch _mCurrentDrawBatch;
static VertexBufferInstance _mVertexBuffer;
static FNA3D_BlendState _mBlendControlTypeNonPremultiplied;
static FNA3D_BlendState _mBlendControlTypeAdditive;
static FNA3D_BlendState _mBlendControlTypeAlphaBlend;

static void ApplyEffect(Effect* effect)
{
	FNA3D_ApplyEffect(_mDeviceContext, effect->mHandle, 0, &effect->mStateChanges);
}
void Renderer_BeforeRender()
{
	FNA3D_Clear(_mDeviceContext, FNA3D_CLEAROPTIONS_TARGET, &_mClearColor, 0, 0);
	if (!IsDepthBufferDisabled())
	{
		FNA3D_Clear(_mDeviceContext, FNA3D_CLEAROPTIONS_DEPTHBUFFER, &_mClearColor, 1, 0);
	}

	if (IsOffscreenTargetNeeded())
	{
		_mIsDrawingToOffscreenTarget = true;

		_mOffscreenTargetBinding.levelCount = 1;
		_mOffscreenTargetBinding.texture = (FNA3D_Texture*)(_mOffscreenTarget.mTextureData);
		_mOffscreenTargetBinding.type = FNA3D_RENDERTARGET_TYPE_2D;
		FNA3D_SetRenderTargets(_mDeviceContext, &_mOffscreenTargetBinding, 1, NULL, FNA3D_DEPTHFORMAT_NONE, 0);
		Renderer_UpdateViewport();
		Renderer_UpdateScissor();

		FNA3D_Clear(_mDeviceContext, FNA3D_CLEAROPTIONS_TARGET, &_mClearColor, 0, 0);
	}
}
void Renderer_AfterRender()
{
	_mIsDrawingToOffscreenTarget = false;

	if (IsOffscreenTargetNeeded())
	{
		FNA3D_SetRenderTargets(_mDeviceContext, NULL, 0, NULL, FNA3D_DEPTHFORMAT_NONE, 0);
		FNA3D_ResolveTarget(_mDeviceContext, &_mOffscreenTargetBinding);
		Renderer_UpdateViewport();
		Renderer_UpdateScissor();

		Renderer_INTERNAL_SetCurrentShaderProgram(NULL);
		Renderer_INTERNAL_SetCurrentCameraPosition(Vector2_Zero);
		Renderer_INTERNAL_SetCurrentBlendState(BLENDSTATE_NONPREMULTIPLIED);
		Renderer_INTERNAL_SetCurrentDepth(100);

		if (Cvars_GetAsInt(CVARS_USER_IS_LINEAR_FILTER_ALLOWED))
		{
			_mSamplerState.filter = FNA3D_TEXTUREFILTER_LINEAR;
		}
		else
		{
			_mSamplerState.filter = FNA3D_TEXTUREFILTER_POINT;
		}
		Rectangle destinationRectangle = Renderer_GetScreenBounds();
		_mIsDrawingFromOffscreenTarget = true;
		Renderer_Draw3(&_mOffscreenTarget, destinationRectangle, COLOR_WHITE);
		Renderer_FlushBatch();
		_mIsDrawingFromOffscreenTarget = false;
		_mSamplerState.filter = FNA3D_TEXTUREFILTER_POINT;
	}

	FNA3D_SwapBuffers(_mDeviceContext, NULL, NULL, _mDeviceWindowHandle);
}
static void CreateIndexBuffer()
{
	if (_mIndexBuffer != NULL)
	{
		return;
	}

	uint16_t* indexBufferData = Renderer_GetDefaultIndexBufferData();
	size_t sizeInBytes = MAX_INDICES * sizeof(uint16_t);
	_mIndexBuffer = FNA3D_GenIndexBuffer(_mDeviceContext, 0, FNA3D_BUFFERUSAGE_WRITEONLY, sizeInBytes);
	FNA3D_SetIndexBufferData(_mDeviceContext, _mIndexBuffer, 0, indexBufferData, sizeInBytes, FNA3D_SETDATAOPTIONS_NONE);
}
static FNA3D_BlendState GetBlendStateFromBlendState(BlendState value)
{
	FNA3D_BlendState blendState;
	switch (value)
	{
	case BLENDSTATE_ADDITIVE:
		blendState = _mBlendControlTypeAdditive;
		break;
	case BLENDSTATE_ALPHABLEND:
		blendState = _mBlendControlTypeAlphaBlend;
		break;
	default:
		blendState = _mBlendControlTypeNonPremultiplied;
		break;
	}
	return blendState;
}
static void ApplyWhiteHitFlashShader(Effect* white)
{
	for (int i = 0; i < 3; i++)
	{
		_mMultiColorReplaceData[i] = 1.0f;
	}

#ifdef GLOBAL_DEF_GAME_IS_MUTE_CRIMSON_DX
	//TODO C99
	/*
	ShaderProgram* globalShaderProgram = Renderer_GetGlobalShaderProgram();
	if (globalShaderProgram != NULL)
	{
		if (globalShaderProgram->mMultiColorReplace.size() >= 6)
		{
			_mMultiColorReplaceData[0] = (float)(globalShaderProgram->mMultiColorReplace[3]) / 0xFF; //Replace color with first target color
			_mMultiColorReplaceData[1] = (float)(globalShaderProgram->mMultiColorReplace[4]) / 0xFF;
			_mMultiColorReplaceData[2] = (float)(globalShaderProgram->mMultiColorReplace[5]) / 0xFF;
		}
	}
	else
	{
		_mMultiColorReplaceData[0] = 0.71f; //Otherwise replace with red
		_mMultiColorReplaceData[1] = 0.19f;
		_mMultiColorReplaceData[2] = 0.13f;
	}
	*/
#endif

	for (int i = 0; i < white->mData->param_count; i++)
	{
		const char* paramName = white->mData->params[i].value.name;
		if (Utils_StringEqualTo(SHADER_PARAMETER_COLOR_REPLACE_0, paramName))
		{
			Utils_memcpy(white->mData->params[i].value.values, &_mMultiColorReplaceData[0], sizeof(float) * 3);
			break;
		}
	}

	ApplyEffect(white);
}
static void ApplyMultiColorReplaceShader(Effect* multi, ShaderProgram* shaderProgram)
{
	int colorLength = shaderProgram->mMultiColorReplaceLength;
	//TODO C99
	/*
	for (int i = 0; i < shaderProgram->mMultiColorReplace.size(); i += 1)
	{
		_mMultiColorReplaceData[i] = (float)(shaderProgram->mMultiColorReplace[i]) / 0xFF;
	}
	*/
	float colorReplaceAlpha = (float)(shaderProgram->mMultiColorReplaceAlpha) / 0xFF;

	for (int i = 0; i < multi->mData->param_count; i++)
	{
		const char* paramName = multi->mData->params[i].value.name;
		if (Utils_StringEqualTo(SHADER_PARAMETER_COLOR_LENGTH, paramName))
		{
			Utils_memcpy(multi->mData->params[i].value.values, &colorLength, sizeof(int) * 1);
		}
		else if (Utils_StringEqualTo(SHADER_PARAMETER_COLOR_TARGET_0, paramName))
		{
			Utils_memcpy(multi->mData->params[i].value.values, &_mMultiColorReplaceData[0], sizeof(float) * 3);
		}
		else if (Utils_StringEqualTo(SHADER_PARAMETER_COLOR_REPLACE_0, paramName))
		{
			Utils_memcpy(multi->mData->params[i].value.values, &_mMultiColorReplaceData[3], sizeof(float) * 3);
		}
		else if (Utils_StringEqualTo(SHADER_PARAMETER_COLOR_TARGET_1, paramName))
		{
			Utils_memcpy(multi->mData->params[i].value.values, &_mMultiColorReplaceData[6], sizeof(float) * 3);
		}
		else if (Utils_StringEqualTo(SHADER_PARAMETER_COLOR_REPLACE_1, paramName))
		{
			Utils_memcpy(multi->mData->params[i].value.values, &_mMultiColorReplaceData[9], sizeof(float) * 3);
		}
		else if (Utils_StringEqualTo(SHADER_PARAMETER_COLOR_TARGET_2, paramName))
		{
			Utils_memcpy(multi->mData->params[i].value.values, &_mMultiColorReplaceData[12], sizeof(float) * 3);
		}
		else if (Utils_StringEqualTo(SHADER_PARAMETER_COLOR_REPLACE_2, paramName))
		{
			Utils_memcpy(multi->mData->params[i].value.values, &_mMultiColorReplaceData[15], sizeof(float) * 3);
		}
		else if (Utils_StringEqualTo(SHADER_PARAMETER_COLOR_TARGET_3, paramName))
		{
			Utils_memcpy(multi->mData->params[i].value.values, &_mMultiColorReplaceData[18], sizeof(float) * 3);
		}
		else if (Utils_StringEqualTo(SHADER_PARAMETER_COLOR_REPLACE_3, paramName))
		{
			Utils_memcpy(multi->mData->params[i].value.values, &_mMultiColorReplaceData[21], sizeof(float) * 3);
		}
		else if (Utils_StringEqualTo(SHADER_PARAMETER_COLOR_REPLACE_ALPHA, paramName))
		{
			Utils_memcpy(multi->mData->params[i].value.values, &colorReplaceAlpha, sizeof(float) * 1);
		}
	}

	ApplyEffect(multi);
}
static void SetupRenderState(Vector2 cameraPos, Vector2 scale, BlendState blendStateToUse, FNA3D_Texture* texture, ShaderProgram* shaderProgram)
{
	Matrix transformMatrix = { 0 };
	double widthForTf;
	double heightForTf;
	if (_mIsDrawingFromOffscreenTarget)
	{
		Rectangle drawable = Renderer_GetDrawableSize();
		widthForTf = drawable.Width;
		heightForTf = drawable.Height;

		Vector3 matrixTranslationValue = { -widthForTf / 2.0f, -heightForTf / 2.0f, 0 };
		Matrix matrixTranslation = Matrix_CreateTranslation(matrixTranslationValue);

		Vector3 matrixScaleValue = { 1.0f, 1.0f, 1.0f };
		Matrix matrixScale = Matrix_CreateScale(matrixScaleValue);

		Vector3 matrixWorldValue = { widthForTf / 2.0f, heightForTf / 2.0f, 0 };
		Matrix matrixWorld = Matrix_CreateTranslation(matrixWorldValue);

		transformMatrix = Matrix_Mul(&matrixTranslation, Matrix_Mul(&matrixScale, matrixWorld));
	}
	else
	{
		widthForTf = _mInternalWidthRender;
		heightForTf = _mInternalHeightRender;

		//Vector3 matrixTranslationValue = { -cameraPos.X, -cameraPos.Y, 0 };
		Vector3 matrixTranslationValue = { 0, 0, 0 };
		Matrix matrixTranslation = Matrix_CreateTranslation(matrixTranslationValue);

		//Vector3 matrixScaleValue = { scale.X, scale.Y, 1.0f };
		Vector3 matrixScaleValue = { 1.0f,  1.0f, 1.0f };
		Matrix matrixScale = Matrix_CreateScale(matrixScaleValue);

		Vector3 matrixWorldValue = { 0, 0, 0 };
		//Matrix matrixWorld = Matrix_CreateTranslation(_mInternalWorldTranslation);
		Matrix matrixWorld = Matrix_CreateTranslation(matrixWorldValue);

		transformMatrix = Matrix_Mul(&matrixTranslation, Matrix_Mul(&matrixScale, matrixWorld));

		transformMatrix = Matrix_Identity(); //TODO C99 PUT THIS BACk.
	}

	// Inlined CreateOrthographicOffCenter * transformMatrix
	// (and convert from row major to column major)
	float tfWidth = (float)(2.0 / widthForTf);
	float tfHeight = (float)(-2.0 / heightForTf);

	_mTransformDest[0] = (tfWidth * transformMatrix.M11) - transformMatrix.M14;
	_mTransformDest[1] = (tfWidth * transformMatrix.M21) - transformMatrix.M24;
	_mTransformDest[2] = (tfWidth * transformMatrix.M31) - transformMatrix.M34;
	_mTransformDest[3] = (tfWidth * transformMatrix.M41) - transformMatrix.M44;
	_mTransformDest[4] = (tfHeight * transformMatrix.M12) + transformMatrix.M14;
	_mTransformDest[5] = (tfHeight * transformMatrix.M22) + transformMatrix.M24;
	_mTransformDest[6] = (tfHeight * transformMatrix.M32) + transformMatrix.M34;
	_mTransformDest[7] = (tfHeight * transformMatrix.M42) + transformMatrix.M44;
	_mTransformDest[8] = transformMatrix.M13;
	_mTransformDest[9] = transformMatrix.M23;
	_mTransformDest[10] = transformMatrix.M33;
	_mTransformDest[11] = transformMatrix.M43;
	_mTransformDest[12] = transformMatrix.M14;
	_mTransformDest[13] = transformMatrix.M24;
	_mTransformDest[14] = transformMatrix.M34;
	_mTransformDest[15] = transformMatrix.M44;

	if (_mLastUsedBlendState != blendStateToUse)
	{
		_mLastUsedBlendState = blendStateToUse;

		FNA3D_BlendState blendState = GetBlendStateFromBlendState(blendStateToUse);
		FNA3D_SetBlendState(_mDeviceContext, &blendState);
	}

	FNA3D_SetDepthStencilState(_mDeviceContext, &_mDepthStencilState);

	FNA3D_ApplyRasterizerState(_mDeviceContext, &_mRasterizerState);

	if (_mLastUsedTexture != texture)
	{
		_mLastUsedTexture = texture;
		FNA3D_VerifySampler(_mDeviceContext, 0, texture, &_mSamplerState);
	}

	int isTotalWhiteHitFlash = 0;
	int shaderType = RENDERER_SHADER_TYPE_SPRITE_EFFECT;
	if (shaderProgram != NULL)
	{
		isTotalWhiteHitFlash = shaderProgram->mIsTotalWhiteHitFlash;
		shaderType = shaderProgram->mShaderType;
	}
	int performAlphaTest = 0;
	if (!IsDepthBufferDisabled())
	{
		if (_mDepthStencilState.depthBufferWriteEnable == 1)
		{
			performAlphaTest = 1;
		}
	}

	bool hasSetTheTransform = false;
	bool hasSetTheShaderType = false;
	bool hasSetTheAlphaTest = false;
	bool hasSetTheIsTotalWhiteHitFlash = false;

	for (int i = 0; i < _mEffect.mData->param_count; i++)
	{
		const char* paramName = _mEffect.mData->params[i].value.name;
		if (!hasSetTheIsTotalWhiteHitFlash)
		{
			if (Utils_StringEqualTo(SHADER_PARAMETER_IS_TOTAL_WHITE_HIT_FLASH, paramName))
			{
				Utils_memcpy(_mEffect.mData->params[i].value.values, &isTotalWhiteHitFlash, sizeof(int) * 1);
				hasSetTheIsTotalWhiteHitFlash = true;
				continue;
			}
		}
		if (!hasSetTheAlphaTest)
		{
			if (Utils_StringEqualTo(SHADER_PARAMETER_PERFORM_ALPHA_TEST, paramName))
			{
				Utils_memcpy(_mEffect.mData->params[i].value.values, &performAlphaTest, sizeof(int) * 1);
				hasSetTheAlphaTest = true;
				continue;
			}
		}
		if (!hasSetTheTransform)
		{
			if (Utils_StringEqualTo(SHADER_PARAMETER_MATRIX_TRANSFORM, paramName))
			{
				Utils_memcpy(_mEffect.mData->params[i].value.values, _mTransformDest, sizeof(float) * 16);
				hasSetTheTransform = true;
				continue;
			}
		}
		if (!hasSetTheShaderType)
		{
			if (Utils_StringEqualTo(SHADER_PARAMETER_SHADER_TYPE, paramName))
			{
				Utils_memcpy(_mEffect.mData->params[i].value.values, &shaderType, sizeof(int) * 1);
				hasSetTheShaderType = true;
				continue;
			}
		}
		if (hasSetTheTransform && hasSetTheShaderType)
		{
			break;
		}
	}

	ApplyEffect(&_mEffect);

	if (shaderProgram != NULL)
	{
		switch (shaderType)
		{
		case RENDERER_SHADER_TYPE_WHITE_HIT_FLASH:
			ApplyWhiteHitFlashShader(&_mEffect);
			break;
		case RENDERER_SHADER_TYPE_MULTI_COLOR_REPLACE:
			ApplyMultiColorReplaceShader(&_mEffect, shaderProgram);
			break;
		}
	}
}
static void DrawTheBatch(DrawBatch drawBatch)
{
	SetupRenderState(drawBatch.mDrawState.mCameraPosition, Vector2_One, drawBatch.mDrawState.mBlendState, drawBatch.mDrawState.mTexture, drawBatch.mDrawState.mShaderProgram);

	VertexBufferInstance* vbInstance = &_mVertexBuffer;

	VertexBufferInstance_SetData(vbInstance, drawBatch.mOffset, drawBatch.mLength);

	FNA3D_ApplyVertexBufferBindings(_mDeviceContext, &vbInstance->mVertexBufferBinding, 1, 1, 0);

	FNA3D_DrawIndexedPrimitives(_mDeviceContext, FNA3D_PRIMITIVETYPE_TRIANGLELIST, 0, 0,
		drawBatch.mLength, 0, drawBatch.mLength / 2, _mIndexBuffer, FNA3D_INDEXELEMENTSIZE_16BIT);

	_mBatchNumber += 1;
}
static void NextBatch(bool keepDrawState)
{
	DrawState drawState;
	if (keepDrawState)
	{
		drawState = _mCurrentDrawBatch.mDrawState;
	}

	//int end = _mCurrentDrawBatch.GetEndPositionInVertexBuffer();
	if (_mCurrentDrawBatch.mLength > 0)
	{
		DrawTheBatch(_mCurrentDrawBatch);
	}
	DrawBatch_Init(&_mCurrentDrawBatch);

	if (keepDrawState)
	{
		_mCurrentDrawBatch.mDrawState = drawState;
	}
}
void Renderer_DrawTtText(Texture* texture, const float* verts, const float* tcoords, const unsigned int* colors, int nverts)
{
	NextBatch(false);

	const TtFontState* fontState = Renderer_GetTtFontState();

	float scaleFactor = fontState->mScaleFactor;

	Vector2 scaler = { 1.0f / scaleFactor, 1.0f / scaleFactor };
	Vector2 currentCameraPosition = Renderer_INTERNAL_GetCurrentCameraPosition();
	Vector2 offsetPosition = Vector2_Sub(currentCameraPosition, fontState->mPosition);
	Vector2 cameraPos = Vector2_MulSingle(offsetPosition, scaleFactor);
	SetupRenderState(cameraPos, scaler, BLENDSTATE_NONPREMULTIPLIED, (FNA3D_Texture*)(texture->mTextureData), Renderer_INTERNAL_GetCurrentShaderProgram());

	Renderer_SetupVerticesForTtFont(_mVertexBuffer.mVertices, fontState->mColor, 0, verts, tcoords, colors, nverts);

	VertexBufferInstance_SetData(&_mVertexBuffer, 0, nverts);

	FNA3D_ApplyVertexBufferBindings(_mDeviceContext, &_mVertexBuffer.mVertexBufferBinding, 1, 1, 0);

	FNA3D_DrawPrimitives(_mDeviceContext, FNA3D_PRIMITIVETYPE_TRIANGLELIST, 0, nverts / 3);
}
static void CheckBatchState(const DrawState* state)
{
	if (!DrawState_IsEqualTo(&_mCurrentDrawBatch.mDrawState, state))
	{
		NextBatch(false);
	}

	_mCurrentDrawBatch.mDrawState = *state;
}
static void CheckBatchSize(bool keepState)
{
	if (DrawBatch_GetEndPositionInVertexBuffer(&_mCurrentDrawBatch) + VERTICES_IN_SPRITE >= MAX_VERTICES)
	{
		NextBatch(true);
	}
}
void Renderer_DrawVertexPositionColorTexture4(Texture* texture, const VertexPositionColorTexture4* sprite)
{
	FNA3D_Texture* fnTexture = (FNA3D_Texture*)(texture->mTextureData);

	DrawState newDrawState;
	newDrawState.mTexture = fnTexture;
	newDrawState.mBlendState = Renderer_INTERNAL_GetCurrentBlendState();
	newDrawState.mShaderProgram = Renderer_INTERNAL_GetCurrentShaderProgram();
	newDrawState.mCameraPosition = Renderer_INTERNAL_GetCurrentCameraPosition();

	CheckBatchState(&newDrawState);

	CheckBatchSize(true);

	int pos = DrawBatch_GetEndPositionInVertexBuffer(&_mCurrentDrawBatch);

	_mCurrentDrawBatch.mLength += VERTICES_IN_SPRITE;

	Renderer_SetupVerticesFromVPCT4(_mVertexBuffer.mVertices, pos, sprite);
}
Texture* Renderer_GetTextureData(const char* path, FixedByteBuffer* blob)
{
	SDL_IOStream* rwops = SDL_IOFromMem(FixedByteBuffer_GetBuffer(blob), FixedByteBuffer_GetLength(blob));

	int w;
	int h;
	int len;
	uint8_t* imageData = FNA3D_Image_Load(Renderer_ImageRead, Renderer_ImageSkip, Renderer_ImageEndOfFile, rwops, &w, &h, &len, -1, -1, 0);

	SDL_CloseIO(rwops);

	Texture* tex = Renderer_GetNewTextureData(path, w, h, false);

	FNA3D_Texture* texture = (FNA3D_Texture*)tex->mTextureData;

	FNA3D_SetTextureData2D(_mDeviceContext, texture, 0, 0, w, h, 0, imageData, len);

	FNA3D_Image_Free(imageData);

	return tex;
}
Texture* Renderer_GetNewTextureData(const char* path, int width, int height, bool clearTexture)
{
	InvalidateNextSetupRenderState();

	FNA3D_Texture* texture = FNA3D_CreateTexture2D(_mDeviceContext, FNA3D_SURFACEFORMAT_COLOR, width, height, 1, 0);

	if (clearTexture)
	{
		int dataLength = width * height * 4;
		uint8_t* clearData = Utils_malloc(sizeof(uint8_t) * dataLength);
		memset(clearData, 0, dataLength);
		FNA3D_SetTextureData2D(_mDeviceContext, texture, 0, 0, width, height, 0, clearData, dataLength);
		Utils_free(clearData);
	}

	Texture* tex = Utils_malloc(sizeof(Texture));
	memset(tex, 0, sizeof(Texture));
	Utils_strlcpy(tex->mPath.mValue, path, FIXED_CHAR_260_LENGTH);
	tex->mBounds.Width = width;
	tex->mBounds.Height = height;
	tex->mTextureData = texture;

	return tex;
}
void Renderer_UpdateTextureData(Texture* texture, int x, int y, int w, int h, int level, void* data, int dataLength)
{
	InvalidateNextSetupRenderState();

	FNA3D_SetTextureData2D(_mDeviceContext, (FNA3D_Texture*)(texture->mTextureData), x, y, w, h, level, data, dataLength);
}
static void LoadShader(Effect* effect, const char* shaderName)
{
	SharedFixedChar260* path = Utils_CreateSharedFixedChar260();
	File_Combine3(path, File_GetBasePath(), "data", shaderName);
	SDL_IOStream* effectFile = SDL_IOFromFile(path, "rb");
	SDL_SeekIO(effectFile, 0, SDL_IO_SEEK_END);
	int64_t effectCodeLength = SDL_TellIO(effectFile);
	SDL_SeekIO(effectFile, 0, SDL_IO_SEEK_SET);
	uint8_t* effectCode = Utils_malloc(sizeof(uint8_t) * effectCodeLength);
	SDL_ReadIO(effectFile, effectCode, effectCodeLength);
	SDL_CloseIO(effectFile);
	FNA3D_CreateEffect(_mDeviceContext, effectCode, effectCodeLength, &effect->mHandle, &effect->mData);
	Utils_free(effectCode);
	effectCode = NULL;
}
int Renderer_Init(void* deviceWindowHandle)
{
	_mInternalWidth = Utils_GetInternalWidth();
	_mInternalHeight = Utils_GetInternalHeight();
	_mInternalWidthRender = Utils_GetInternalRenderWidth();
	_mInternalHeightRender = Utils_GetInternalRenderHeight();
	_mInternalWorldTranslation.X = _mInternalWidth / 2.0f;
	_mInternalWorldTranslation.Y = _mInternalHeight / 2.0f;
	_mInternalWorldTranslation.Z = 0;

	_mDeviceWindowHandle = deviceWindowHandle;

	FNA3D_HookLogFunctions(Renderer_LogInfo, Renderer_LogWarning, Renderer_LogError);

	//Blend States
	// 
	//NonPremultiplied
	_mBlendControlTypeNonPremultiplied.alphaBlendFunction = FNA3D_BLENDFUNCTION_ADD;
	_mBlendControlTypeNonPremultiplied.alphaDestinationBlend = FNA3D_BLEND_INVERSESOURCEALPHA;
	_mBlendControlTypeNonPremultiplied.alphaSourceBlend = FNA3D_BLEND_SOURCEALPHA;
	_mBlendControlTypeNonPremultiplied.blendFactor = _mWhiteBlendFactor;
	_mBlendControlTypeNonPremultiplied.colorBlendFunction = FNA3D_BLENDFUNCTION_ADD;
	_mBlendControlTypeNonPremultiplied.colorDestinationBlend = FNA3D_BLEND_INVERSESOURCEALPHA;
	_mBlendControlTypeNonPremultiplied.colorSourceBlend = FNA3D_BLEND_SOURCEALPHA;
	_mBlendControlTypeNonPremultiplied.colorWriteEnable = FNA3D_COLORWRITECHANNELS_ALL;
	_mBlendControlTypeNonPremultiplied.colorWriteEnable1 = FNA3D_COLORWRITECHANNELS_ALL;
	_mBlendControlTypeNonPremultiplied.colorWriteEnable2 = FNA3D_COLORWRITECHANNELS_ALL;
	_mBlendControlTypeNonPremultiplied.colorWriteEnable3 = FNA3D_COLORWRITECHANNELS_ALL;
	_mBlendControlTypeNonPremultiplied.multiSampleMask = -1;

	//Additive
	_mBlendControlTypeAdditive.alphaBlendFunction = FNA3D_BLENDFUNCTION_ADD;
	_mBlendControlTypeAdditive.alphaDestinationBlend = FNA3D_BLEND_ONE;
	_mBlendControlTypeAdditive.alphaSourceBlend = FNA3D_BLEND_SOURCEALPHA;
	_mBlendControlTypeAdditive.blendFactor = _mWhiteBlendFactor;
	_mBlendControlTypeAdditive.colorBlendFunction = FNA3D_BLENDFUNCTION_ADD;
	_mBlendControlTypeAdditive.colorDestinationBlend = FNA3D_BLEND_ONE;
	_mBlendControlTypeAdditive.colorSourceBlend = FNA3D_BLEND_SOURCEALPHA;
	_mBlendControlTypeAdditive.colorWriteEnable = FNA3D_COLORWRITECHANNELS_ALL;
	_mBlendControlTypeAdditive.colorWriteEnable1 = FNA3D_COLORWRITECHANNELS_ALL;
	_mBlendControlTypeAdditive.colorWriteEnable2 = FNA3D_COLORWRITECHANNELS_ALL;
	_mBlendControlTypeAdditive.colorWriteEnable3 = FNA3D_COLORWRITECHANNELS_ALL;
	_mBlendControlTypeAdditive.multiSampleMask = -1;

	//Alpha Blend
	_mBlendControlTypeAlphaBlend.alphaBlendFunction = FNA3D_BLENDFUNCTION_ADD;
	_mBlendControlTypeAlphaBlend.alphaDestinationBlend = FNA3D_BLEND_INVERSESOURCEALPHA;
	_mBlendControlTypeAlphaBlend.alphaSourceBlend = FNA3D_BLEND_ONE;
	_mBlendControlTypeAlphaBlend.blendFactor = _mWhiteBlendFactor;
	_mBlendControlTypeAlphaBlend.colorBlendFunction = FNA3D_BLENDFUNCTION_ADD;
	_mBlendControlTypeAlphaBlend.colorDestinationBlend = FNA3D_BLEND_INVERSESOURCEALPHA;
	_mBlendControlTypeAlphaBlend.colorSourceBlend = FNA3D_BLEND_ONE;
	_mBlendControlTypeAlphaBlend.colorWriteEnable = FNA3D_COLORWRITECHANNELS_ALL;
	_mBlendControlTypeAlphaBlend.colorWriteEnable1 = FNA3D_COLORWRITECHANNELS_ALL;
	_mBlendControlTypeAlphaBlend.colorWriteEnable2 = FNA3D_COLORWRITECHANNELS_ALL;
	_mBlendControlTypeAlphaBlend.colorWriteEnable3 = FNA3D_COLORWRITECHANNELS_ALL;
	_mBlendControlTypeAlphaBlend.multiSampleMask = -1;

	//Sampler State
	_mSamplerState.addressU = FNA3D_TEXTUREADDRESSMODE_WRAP;
	_mSamplerState.addressV = FNA3D_TEXTUREADDRESSMODE_WRAP;
	_mSamplerState.addressW = FNA3D_TEXTUREADDRESSMODE_WRAP;
	_mSamplerState.filter = FNA3D_TEXTUREFILTER_POINT;
	_mSamplerState.maxAnisotropy = 0;
	_mSamplerState.maxMipLevel = 0;
	_mSamplerState.mipMapLevelOfDetailBias = 0;

	//Vertex Elements
	_mVertexElements[0].offset = 0;
	_mVertexElements[0].usageIndex = 0;
	_mVertexElements[0].vertexElementFormat = FNA3D_VERTEXELEMENTFORMAT_VECTOR3;
	_mVertexElements[0].vertexElementUsage = FNA3D_VERTEXELEMENTUSAGE_POSITION;

	_mVertexElements[1].offset = sizeof(float) * 3;
	_mVertexElements[1].usageIndex = 0;
	_mVertexElements[1].vertexElementFormat = FNA3D_VERTEXELEMENTFORMAT_VECTOR4;
	_mVertexElements[1].vertexElementUsage = FNA3D_VERTEXELEMENTUSAGE_COLOR;

	_mVertexElements[2].offset = sizeof(float) * 7;
	_mVertexElements[2].usageIndex = 0;
	_mVertexElements[2].vertexElementFormat = FNA3D_VERTEXELEMENTFORMAT_VECTOR2;
	_mVertexElements[2].vertexElementUsage = FNA3D_VERTEXELEMENTUSAGE_TEXTURECOORDINATE;

	if (IsDepthBufferDisabled())
	{
		_mDeviceParams.depthStencilFormat = FNA3D_DEPTHFORMAT_NONE;
	}
	else
	{
		_mDeviceParams.depthStencilFormat = FNA3D_DEPTHFORMAT_D24;
	}
	_mDeviceParams.deviceWindowHandle = deviceWindowHandle;
	_mDeviceParams.backBufferFormat = FNA3D_SURFACEFORMAT_COLOR;
	Rectangle wantedBackBufferBounds = Renderer_GetWantedBackBufferBounds();
	_mDeviceParams.backBufferWidth = wantedBackBufferBounds.Width;
	_mDeviceParams.backBufferHeight = wantedBackBufferBounds.Height;
	Renderer_UpdateVsync();
	_mDeviceContext = FNA3D_CreateDevice(&_mDeviceParams, 0);
	if (_mDeviceContext == NULL)
	{
		return -1;
	}

	Renderer_UpdateViewport();

	Renderer_UpdateScissor();

	CreateIndexBuffer();

	VertexBufferInstance_Init(&_mVertexBuffer);

	FNA3D_SetBlendState(_mDeviceContext, &_mBlendControlTypeNonPremultiplied);

	if (IsDepthBufferDisabled())
	{
		_mDepthStencilState.depthBufferEnable = 0;
	}
	else
	{
		_mDepthStencilState.depthBufferEnable = 1;
	}
	_mDepthStencilState.depthBufferWriteEnable = 0;
	_mDepthStencilState.depthBufferFunction = FNA3D_COMPAREFUNCTION_LESSEQUAL;
	_mDepthStencilState.stencilEnable = 0;
	FNA3D_SetDepthStencilState(_mDeviceContext, &_mDepthStencilState);

	_mRasterizerState.cullMode = FNA3D_CULLMODE_NONE;
	_mRasterizerState.fillMode = FNA3D_FILLMODE_SOLID;
	_mRasterizerState.depthBias = 0;
	_mRasterizerState.multiSampleAntiAlias = 0;
	_mRasterizerState.scissorTestEnable = 0;
	_mRasterizerState.slopeScaleDepthBias = 0;
	FNA3D_ApplyRasterizerState(_mDeviceContext, &_mRasterizerState);

	// load effect
	LoadShader(&_mEffect, "SHADER.fxc");

	return 0;
}
void Renderer_BeforeCommit()
{
	_mBatchNumber = 0;
}
void Renderer_AfterCommit()
{
	Renderer_FlushBatch();
}
void Renderer_FlushBatch()
{
	NextBatch(false);
}
void Renderer_EnableDepthBufferWrite()
{
	if (IsDepthBufferDisabled())
	{
		return;
	}

	_mDepthStencilState.depthBufferWriteEnable = 1;
}
void Renderer_DisableDepthBufferWrite()
{
	if (IsDepthBufferDisabled())
	{
		return;
	}

	_mDepthStencilState.depthBufferWriteEnable = 0;
}
void Renderer_UpdateVsync()
{
	bool useVsync = Renderer_IsVsync();
	if (Service_PlatformForcesVsync())
	{
		useVsync = true;
	}

#ifdef DEBUG_DEF_FORCE_VSYNC_OFF
	useVsync = false;
#endif

#ifdef DEBUG_DEF_FORCE_VSYNC_ON
	useVsync = true;
#endif

	if (useVsync)
	{
		_mDeviceParams.presentationInterval = FNA3D_PRESENTINTERVAL_ONE;
	}
	else
	{
		_mDeviceParams.presentationInterval = FNA3D_PRESENTINTERVAL_IMMEDIATE;
	}
}
void Renderer_ApplyChanges()
{
	Renderer_ResetBackBuffer();
	Renderer_UpdateViewport();
	Renderer_UpdateScissor();
}
void Renderer_UpdateViewport()
{
	Rectangle backBufferBounds = GetCurrentBufferBounds();
	FNA3D_Viewport viewport = { 0 };
	viewport.w = backBufferBounds.Width;
	viewport.h = backBufferBounds.Height;
	viewport.maxDepth = 1;
	FNA3D_SetViewport(_mDeviceContext, &viewport);
}
void Renderer_UpdateScissor()
{
	Rectangle backBufferBounds = GetCurrentBufferBounds();
	FNA3D_Rect scissor = { 0 };
	scissor.x = backBufferBounds.X;
	scissor.y = backBufferBounds.Y;
	scissor.w = backBufferBounds.Width;
	scissor.h = backBufferBounds.Height;
	FNA3D_SetScissorRect(_mDeviceContext, &scissor);
}
void Renderer_ResetBackBuffer()
{
	Rectangle wantedBackBufferBounds = Renderer_GetWantedBackBufferBounds();

	_mVirtualBufferBounds.Width = wantedBackBufferBounds.Width;
	_mVirtualBufferBounds.Height = wantedBackBufferBounds.Height;

	if (IsOffscreenTargetNeeded())
	{
		_mActualBufferBounds = Renderer_GetDrawableSize();
	}
	else
	{
		_mActualBufferBounds = _mVirtualBufferBounds;
	}

	_mDeviceParams.backBufferWidth = _mActualBufferBounds.Width;
	_mDeviceParams.backBufferHeight = _mActualBufferBounds.Height;

	Logger_LogInformation("Back Buffer has been reset");
	//Logger_LogInformation("Actual buffer bounds: " + std::to_string(_mActualBufferBounds.Width) + "x" + std::to_string(_mActualBufferBounds.Height));

	FNA3D_ResetBackbuffer(_mDeviceContext, &_mDeviceParams);

	if (IsOffscreenTargetNeeded())
	{
		//Logger_LogInformation("Virtual buffer bounds: " + std::to_string(_mVirtualBufferBounds.Width) + "x" + std::to_string(_mVirtualBufferBounds.Height));

		if (_mOffscreenTarget.mTextureData != NULL)
		{
			FNA3D_AddDisposeTexture(_mDeviceContext, (FNA3D_Texture*)(_mOffscreenTarget.mTextureData));
			_mOffscreenTarget.mTextureData = NULL;
		}

		_mOffscreenTargetBinding.twod.width = _mVirtualBufferBounds.Width;
		_mOffscreenTargetBinding.twod.height = _mVirtualBufferBounds.Height;

		_mOffscreenTarget.mTextureData = FNA3D_CreateTexture2D(_mDeviceContext, FNA3D_SURFACEFORMAT_COLOR, _mVirtualBufferBounds.Width, _mVirtualBufferBounds.Height, 1, 1);
		_mOffscreenTarget.mBounds.Width = _mVirtualBufferBounds.Width;
		_mOffscreenTarget.mBounds.Height = _mVirtualBufferBounds.Height;
	}
}
Rectangle Renderer_GetDrawableSize()
{
	Rectangle drawableSize;
	drawableSize.X = 0;
	drawableSize.Y = 0;
	SDL_GetWindowSizeInPixels(_mDeviceWindowHandle, &drawableSize.Width, &drawableSize.Height);
	//FNA3D_GetDrawableSize(_mDeviceWindowHandle, &drawableSize.Width, &drawableSize.Height);
	return drawableSize;
}