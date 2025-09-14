/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../math/Rectangle.h"
#include "../io/BufferReader.h"
#include "../utils/FixedChar260.h"

typedef struct Texture
{
	FixedChar260 mPath;
	void* mTextureData;
	//void* mSurfaceData;
	Rectangle mBounds;
} Texture;

void Texture_Dispose(Texture* tex);
Texture* Texture_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br);
/*
static const std::vector<std::string>& GetUserDirectories();
static const std::vector<std::string>& GetDebugDirectories();
static const std::vector<std::string>& GetFontDirectories();
static const std::vector<std::string>& GetMovieDirectories();
*/