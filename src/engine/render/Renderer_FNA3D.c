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

#include "FNA3D.h"
#include "FNA3D_Image.h"
#include "SDL3/SDL.h"
#define MOJOSHADER_NO_VERSION_INCLUDE
#define MOJOSHADER_EFFECT_SUPPORT
#include "mojoshader.h"
#include "mojoshader_effects.h"
#include "../math/Rectangle.h"
#include "../math/Vector3.h"
#include "../math/Vector2.h"
#include "Texture2D.h"
#include "BlendState.h"
#include "ShaderProgram.h"
#include "RendererMacros.h"
#include "../utils/Utils.h"
#include "../io/File.h"
#include "../utils/Macros.h"

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
//static Matrix _mMatrix;
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
static int _mBatchNumber;
//Setup Render State Stuff
static float _mMultiColorReplaceData[MULTI_COLOR_REPLACE_LEN];
static float _mTransformDest[TRANSFORM_DEST_LEN];
static FNA3D_Texture* _mLastUsedTexture;
static BlendState _mLastUsedBlendState = BLENDSTATE_INVALID;
//
static FNA3D_RenderTargetBinding _mOffscreenTargetBinding;
static Texture2D _mOffscreenTarget;
static bool _mIsDrawingFromOffscreenTarget;
static bool _mIsDrawingToOffscreenTarget;
static Rectangle _mVirtualBufferBounds;
static Rectangle _mActualBufferBounds;

static FNA3D_BlendState _mBlendControlTypeNonPremultiplied;
static FNA3D_BlendState _mBlendControlTypeAdditive;
static FNA3D_BlendState _mBlendControlTypeAlphaBlend;

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
	return true;
	//return OeService::PlatformDisablesDepthBufferForRender();
}

static bool IsOffscreenTargetNeeded()
{
	return false;
	//return OeService::PlatformRequiresOffscreenTargetForRender();
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

static bool DrawState_IsEqualTo(const DrawState* valueA, const DrawState* valueB)
{
	if (valueA->mTexture != valueB->mTexture)
	{
		return false;
	}

	if (valueA->mBlendState != valueB->mBlendState)
	{
		return false;
	}

	if (valueA->mShaderProgram != valueB->mShaderProgram)
	{
		return false;
	}

	if (Vector2_NotEqual(valueA->mCameraPosition, valueB->mCameraPosition))
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

static int DrawBatch_GetEndPositionInVertexBuffer(const DrawBatch* value)
{
	return value->mOffset + value->mLength;
}
typedef struct VertexBufferInstance
{
	FNA3D_VertexBufferBinding mVertexBufferBinding;
	FNA3D_Buffer* mVertexBuffer;
	VertexPositionColorTexture* mVertices;
} VertexBufferInstance;
static void VertexBufferInstance_Init(VertexBufferInstance* value)
{
	value->mVertexBuffer = FNA3D_GenVertexBuffer(_mDeviceContext, 1, FNA3D_BUFFERUSAGE_WRITEONLY, MAX_VERTICES * sizeof(VertexPositionColorTexture));
	value->mVertices = Utils_malloc(sizeof(VertexPositionColorTexture) * MAX_VERTICES);

	FNA3D_VertexDeclaration vertexDeclaration = { 0 };
	vertexDeclaration.elementCount = 3;
	vertexDeclaration.vertexStride = sizeof(VertexPositionColorTexture);
	vertexDeclaration.elements = _mVertexElements;

	Utils_memset(&value->mVertexBufferBinding, 0, sizeof(FNA3D_VertexBufferBinding));
	value->mVertexBufferBinding.instanceFrequency = 0;
	value->mVertexBufferBinding.vertexBuffer = value->mVertexBuffer;
	value->mVertexBufferBinding.vertexDeclaration = vertexDeclaration;
	value->mVertexBufferBinding.vertexOffset = 0;
}

static DrawBatch _mCurrentDrawBatch;
static VertexBufferInstance _mVertexBuffer;
static FNA3D_BlendState _mBlendControlTypeNonPremultiplied;
static FNA3D_BlendState _mBlendControlTypeAdditive;
static FNA3D_BlendState _mBlendControlTypeAlphaBlend;

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
	FNA3D_Rect scissor;
	scissor.x = backBufferBounds.X;
	scissor.y = backBufferBounds.Y;
	scissor.w = backBufferBounds.Width;
	scissor.h = backBufferBounds.Height;
	FNA3D_SetScissorRect(_mDeviceContext, &scissor);
}
void Renderer_UpdateVsync()
{
	bool useVsync = true;

	//bool useVsync = IsVsync();
	//if (OeService::PlatformForcesVsync())
	//{
	//	useVsync = true;
	//}

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
static void LoadShader(const char* shaderName, Effect* effect)
{
	//std::string strBasePath = OeFile::GetBasePath();
	//std::string strEffectPath = OeFile::Combine(strBasePath, "data", shaderName);
	SharedFixedChar260* sharedStringBuffer = Utils_GetSharedFixedChar260();
	File_Combine3(sharedStringBuffer, File_GetBasePath(), "data", "SHADER.fxc");
	SDL_IOStream* effectFile = SDL_IOFromFile(sharedStringBuffer, "rb");
	sharedStringBuffer->mIsInUse = false;
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
int32_t Renderer_Init(void* deviceWindowHandle)
{
	_mInternalWidth = 480;
	_mInternalHeight = 272;
	_mInternalWidthRender = 480;
	_mInternalHeightRender = 270;
	//_mInternalWidth = OeUtils::GetInternalWidth();
	//_mInternalHeight = OeUtils::GetInternalHeight();
	//_mInternalWidthRender = OeUtils::GetInternalRenderWidth();
	//_mInternalHeightRender = OeUtils::GetInternalRenderHeight();
	Vector3_Init(&_mInternalWorldTranslation, _mInternalWidth / 2.0f, _mInternalHeight / 2.0f, 0);

	_mDeviceWindowHandle = deviceWindowHandle;

	//FNA3D_HookLogFunctions(LogInfo, LogWarning, LogError);

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
	//Rectangle wantedBackBufferBounds = GetWantedBackBufferBounds();
	Rectangle wantedBackBufferBounds = { 0, 0, 480, 270 };
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
	LoadShader("SHADER.fxc", &_mEffect);

	return 0;
}
void Renderer_ApplyChanges()
{

}