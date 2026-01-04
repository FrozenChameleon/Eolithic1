#pragma once

#include "stdbool.h"

void ServiceHelper_Update(double delta);
bool ServiceHelper_HasPlayerHasLostControllerConnection();
int ServiceHelper_GetPlayerThatLostControllerConnection();
void ServiceHelper_HandlePlayerLostControllerConnection();
bool ServiceHelper_HasLoadedEverything();