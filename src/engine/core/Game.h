/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

/* Derived from code by Ethan Lee (Copyright 2009-2024).
 * Released under the Microsoft Public License.
 * See fna.LICENSE for details.

 * Derived from code by the Mono.Xna Team (Copyright 2006).
 * Released under the MIT License. 
 * See monoxna.LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"

int32_t Game_Init();
int32_t Game_Run();
void Game_PollEvents();
bool Game_IsExitingGame();
void Game_Exit();
bool Game_IsActive();