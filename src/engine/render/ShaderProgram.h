/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../io/BufferReader.h"

typedef struct ShaderProgram
{
	int mDummy;
} ShaderProgram;

ShaderProgram* ShaderProgram_FromStream(BufferReader* br);