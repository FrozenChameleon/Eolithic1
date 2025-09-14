/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Texture.h"

#include "../render/Renderer.h"

void Texture_Dispose(Texture* tex)
{

}
Texture* Texture_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br)
{
	return Renderer_GetTextureData(path, BufferReader_GetBuffer(br));
}
