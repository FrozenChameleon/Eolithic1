#ifdef AUDIO_DUMMY

#include "AudioEngine.h"

int32_t AudioEngine_Init(void)
{
	return 0;
}
void* AudioEngine_GetContext(void)
{
	return NULL;
}

#endif

typedef int compiler_warning_compliance;