/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Sheet.h"

static Sheet* _mDummy;

Sheet* Sheet_GetDefaultSheet()
{
	return _mDummy;
}
Sheet* Sheet_GetSheet()
{
	return _mDummy;
}
