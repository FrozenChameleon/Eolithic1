/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "InputCheck.h"

enum
{
	INPUT_CHECKS_BEGINNING_OF_CONTROLLER = 0,
	INPUT_CHECKS_END_OF_CONTROLLER = 2,
	INPUT_CHECKS_BEGINNING_OF_KBM = 3,
	INPUT_CHECKS_END_OF_KBM = 5,
	INPUT_CHECKS_SECTION_LENGTH = 3,
	INPUT_CHECKS_LENGTH = 6
};

typedef struct InputChecks
{
	InputCheck Checks[INPUT_CHECKS_LENGTH];
} InputChecks;


InputCheck* InputChecks_Get(InputChecks* data, int index);
void InputChecks_Set(InputChecks* data, int index, InputCheck check);