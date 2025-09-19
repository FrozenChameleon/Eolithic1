#pragma once

#include "../../utils/Macros.h"
#include "../../components/Camera.h"
#include "../PackIterator.h"

typedef struct ComponentPack_Camera
{
	int32_t _mMaximumCapacity;
	int32_t _mLength;
	int32_t _mCapacity;
	Camera _mDummy;
	Entity* Entities;
	Camera* Components;
} ComponentPack_Camera;

void ComponentPack_Camera_LogNothingEntityWarning(ComponentPack_Camera* pack);
void ComponentPack_Camera_Init(ComponentPack_Camera* pack, int initialSize);
Camera* ComponentPack_Camera_TryGetFirstSetComponent(ComponentPack_Camera* pack, bool* wasSuccessful);
Camera* ComponentPack_Camera_TryGetComponent(ComponentPack_Camera* pack, Entity entity, bool* wasSuccessful);
bool ComponentPack_Camera_HasComponent(ComponentPack_Camera* pack, Entity entity);
void ComponentPack_Camera_SetMaximumCapacity(ComponentPack_Camera* pack, int value);
Camera* ComponentPack_Camera_GetDummy(ComponentPack_Camera* pack);
int ComponentPack_Camera_Length(ComponentPack_Camera* pack);
bool ComponentPack_Camera_Next(ComponentPack_Camera* pack, PackIterator* iter);
int ComponentPack_Camera_GetFirstSetEntityLocation(ComponentPack_Camera* pack );
int ComponentPack_Camera_GetEntityLocation(ComponentPack_Camera* pack, int entityNumber);
bool ComponentPack_Camera_IsAnyEntityInPack(ComponentPack_Camera* pack );
Camera* ComponentPack_Camera_GetFirstSetComponent(ComponentPack_Camera* pack );
Entity ComponentPack_Camera_GetFirstSetEntity(ComponentPack_Camera* pack);
Camera* ComponentPack_Camera_GetComponentExclusive(ComponentPack_Camera* pack, Entity entity, bool isNotExclusive);
Camera* ComponentPack_Camera_GetComponent(ComponentPack_Camera* pack, Entity entity);
Camera* ComponentPack_Camera_SetExclusive(ComponentPack_Camera* pack, Entity entity, bool isNotExclusive);
Camera* ComponentPack_Camera_Set(ComponentPack_Camera* pack, Entity entity);
void ComponentPack_Camera_Unset(ComponentPack_Camera* pack, int entityNumber);
void ComponentPack_Camera_UnsetAtIndex(ComponentPack_Camera* pack, int index);
void ComponentPack_Camera_UnsetAll(ComponentPack_Camera* pack);
void ComponentPack_Camera_CopyTo(ComponentPack_Camera* pack, ComponentPack_Camera* to);
ComponentPack_Camera* ComponentPack_Camera_CreateCopy(ComponentPack_Camera* pack);
ComponentPack_Camera* ComponentPack_Camera_Dispose(ComponentPack_Camera* pack);
/*
std::type_index ComponentPack_Camera_GetComponentType()
{
	return std::type_index(typeid(T));
}
std::vector<OeEntity>& ComponentPack_Camera_DebugGetEntities()
{
	return Entities;
}
*/