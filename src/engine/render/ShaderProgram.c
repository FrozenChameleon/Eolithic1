/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "ShaderProgram.h"
#include "../utils/Utils.h"
#include "Renderer.h"

static ShaderProgram _mShaderProgramFullRed;
static ShaderProgram _mShaderProgramFullRed2;

ShaderProgram* ShaderProgram_GetShaderFullRed()
{
	_mShaderProgramFullRed.mShaderType = RENDERER_SHADER_TYPE_WHITE_HIT_FLASH;
	return &_mShaderProgramFullRed;
}
ShaderProgram* ShaderProgram_GetShaderFullRed2()
{
	_mShaderProgramFullRed2.mShaderType = RENDERER_SHADER_TYPE_WHITE_HIT_FLASH;
	_mShaderProgramFullRed2.mIsTotalWhiteHitFlash = true;
	return &_mShaderProgramFullRed2;
}
