#pragma once

#include "stdint.h"
#include "stdbool.h"

void ServiceHelper_Update(double delta);
bool ServiceHelper_HasPlayerHasLostControllerConnection();
int32_t ServiceHelper_GetPlayerThatLostControllerConnection();
void ServiceHelper_HandlePlayerLostControllerConnection();
bool ServiceHelper_HasLoadedEverything();