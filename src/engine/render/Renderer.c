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

static const float _mCornerOffsetX[] = { 0.0f ,1.0f, 0.0f, 1.0f };
static const float _mCornerOffsetY[] = { 0.0f, 0.0f, 1.0f, 1.0f };

static bool _mIndexBufferDataSet;
static uint16_t _mIndexBufferData[MAX_INDICES];

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