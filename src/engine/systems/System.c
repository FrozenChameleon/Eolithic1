#include "System.h"

#include "../utils/Utils.h"

System* System_Create()
{
	return Utils_calloc(1, sizeof(System));
}
