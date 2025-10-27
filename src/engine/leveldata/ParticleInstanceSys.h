#pragma once

#include "../systems/System.h"
#include "ParticleInstance.h"

//void Update() override;
//void UpdateLastRenderPosition(OeGameState* gameState) override;
//void Draw(OeSpriteBatch* spriteBatch) override;

void ParticleInstanceSys_Setup(ParticleInstance* data, const char* name, Particle* particleData, float x, float y);
bool ParticleInstanceSys_UpdateRoutine(ParticleInstance* data);
System* ParticleInstanceSys_CreateSystem();