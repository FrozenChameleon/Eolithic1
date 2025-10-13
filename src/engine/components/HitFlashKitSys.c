#include "HitFlashKitSys.h"

#include "../core/Func.h"
#include "../render/ShaderProgram.h"
#include "../components/DrawActor.h"

static ShaderProgram* _mShaderProgram;

void HitFlashKitSys_InitRoutine(Entity owner, HitFlashKit* data)
{
	if (_mShaderProgram == NULL)
	{
		//TODO C99 _mShaderProgram = ShaderProgram_GetShaderWhiteHitFlash();
	}
	data->mState = -1;
}
void HitFlashKitSys_UpdateRoutine(Entity owner, HitFlashKit* data)
{
	if (data->mIsDisabled)
	{
		return;
	}

	if (!data->mShowHitFlash)
	{
		return;
	}

	//TODO C99
	/*
	bool wasSuccessful;
	OeComDrawActor* drawActor = TryGet_Component<OeComDrawActor>(owner, &wasSuccessful);
	if (!wasSuccessful)
	{
		return;
	}

	if (data->mState == -1)
	{
		drawActor->mShaderProgram = _mShaderProgram;
	}
	else
	{
		Do_SetShader(owner, data->mState, _mShaderProgram);
	}
	if (OeTimer_Update(&data->mHitFlashTimer))
	{
		data->mShowHitFlash = false;
		if (data->mState == -1)
		{
			drawActor->mShaderProgram = nullptr;
		}
		else
		{
			Do_SetShader(owner, data->mState, nullptr);
		}
	}*/
}

System* HitFlashKitSys_CreateSystem()
{
	SystemSimple* ss = SystemSimple_Create(C_HitFlashKit);
	ss->_mInitRoutine = HitFlashKitSys_InitRoutine;
	ss->_mUpdateRoutine = HitFlashKitSys_UpdateRoutine;
	return SystemSimple_CreateSystem(ss);
}
