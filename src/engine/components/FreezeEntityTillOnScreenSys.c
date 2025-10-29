#include "FreezeEntityTillOnScreenSys.h"

#include "Camera.h"
#include "FreezeEntityTillOnScreen.h"
#include "../gamestate/ComponentPack.h"
#include "../core/Func.h"
#include "../math/Rectangle.h"

static void Update(System* sys)
{
	Camera* camera = Get_Camera();
	ComponentPack* pack = Get_ComponentPack(C_FreezeEntityTillOnScreen);
	PackIterator iter = PackIterator_Begin;
	while (ComponentPack_Next(pack, &iter))
	{
		FreezeEntityTillOnScreen* freezeData = ComponentPack_GetComponentAtIndex(pack, iter.mIndex);
		const Rectangle* freezeRect = &freezeData->mRectangle;
		if (Camera_IntersectsCameraRectMul(camera, freezeRect, CAMERA_EXTENDED_CAMERA))
		{
			if (freezeData->mFacesPlayer)
			{
				Do_FacePlayer(iter.mEntity, freezeData->mIsFacingFlipped);
			}
			if (Camera_IntersectsCameraRect(camera, freezeRect))
			{
				Do_SetBodyDisabled(iter.mEntity, false);
				Do_SetUpdateDisabled(iter.mEntity, false);
				ComponentPack_UnsetAtIndex(pack, iter.mIndex);
			}
		}
	}
}

System* FreezeEntityTillOnScreenSys_CreateSystem()
{
	System* sys = System_Create();
	sys->_mUpdate = Update;
	return sys;
}
