/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../io/BufferReader.h"

#define SHADER_PROGRAM_MAX_REPLACE_LENGTH 24

typedef struct ShaderProgram
{
	const char* mName;
	uint32_t mIsTotalWhiteHitFlash;
	uint32_t mShaderType;
	uint32_t mMultiColorReplaceLength;
	uint8_t mMultiColorReplace[SHADER_PROGRAM_MAX_REPLACE_LENGTH];
	uint8_t mMultiColorReplaceAlpha;
} ShaderProgram;

ShaderProgram* ShaderProgram_FromStream(BufferReader* br);
void ShaderProgram_Dispose(ShaderProgram* sp);
