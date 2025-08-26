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

int32_t Renderer_Init(void* deviceWindowHandle);
uint16_t* Renderer_GetDefaultIndexBufferData();
void Renderer_UpdateVsync();
void Renderer_UpdateViewport();
void Renderer_UpdateScissor();
void Renderer_ApplyChanges();