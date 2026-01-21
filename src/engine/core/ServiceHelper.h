#pragma once

#include "stdint.h"
#include "stdbool.h"

void ServiceHelper_Update(double delta);
bool ServiceHelper_HasPlayerHasLostControllerConnection(void);
int32_t ServiceHelper_GetPlayerThatLostControllerConnection(void);
void ServiceHelper_HandlePlayerLostControllerConnection(void);
bool ServiceHelper_HasLoadedEverything(void);