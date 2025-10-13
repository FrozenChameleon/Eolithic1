#pragma once

#include "../systems/SystemSimple.h"
#include "Camera.h"

void CameraSys_UpdateLastRenderPositionRoutine(Camera* data);
void CameraSys_InitRoutine(Entity owner, Camera* data);
void CameraSys_InitCamera(Camera* data);
void CameraSys_UpdateRoutine(Entity owner, Camera* data);
void CameraSys_UpdateCamera(Camera* data);

System* CameraSys_CreateSystem();