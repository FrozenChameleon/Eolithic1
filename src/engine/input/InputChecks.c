/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "InputChecks.h"

#include "../utils/Exception.h"

InputCheck* InputChecks_Get(InputChecks* data, int index)
{
	if ((index >= 0) && (index < INPUT_CHECKS_LENGTH))
	{
		return &data->Checks[index];
	}

	Exception_Run("Out of input checks bounds!", false);
	return NULL;
}

void InputChecks_Set(InputChecks* data, int index, InputCheck check)
{
	if ((index >= 0) && (index < INPUT_CHECKS_LENGTH))
	{
		data->Checks[index] = check;
		return;
	}

	Exception_Run("Out of input checks bounds!", false);
}
