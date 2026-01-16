#pragma once

#include "ComponentType.h"
#include "../utils/Macros.h"
#include "../components/Camera.h"
#include "PackIterator.h"

typedef struct ComponentPack
{
	size_t _mComponentSizeInBytes; //Fixed to all of same type.
	ComponentType _mComponentType;
	int32_t _mMaximumCapacity;
	uint8_t* _mDummy;
	int32_t _mLength; //Change per instance of pack in memory.
	int32_t _mCapacity;
	Entity* Entities;
	uint8_t* Components;
} ComponentPack;

void ComponentPack_Init(ComponentType ctype, ComponentPack* pack, size_t componentSizeInBytes, int32_t initialSize);
void* ComponentPack_TryGetFirstSetComponent(ComponentPack* pack, bool* wasSuccessful);
void* ComponentPack_TryGetComponent(ComponentPack* pack, Entity entity, bool* wasSuccessful);
bool ComponentPack_HasComponent(ComponentPack* pack, Entity entity);
void ComponentPack_SetMaximumCapacity(ComponentPack* pack, int32_t value);
void* ComponentPack_GetDummy(ComponentPack* pack);
int ComponentPack_Length(ComponentPack* pack);
bool ComponentPack_Next(ComponentPack* pack, PackIterator* iter);
int ComponentPack_GetFirstSetEntityLocation(ComponentPack* pack );
int ComponentPack_GetEntityLocation(ComponentPack* pack, int32_t entityNumber);
bool ComponentPack_IsAnyEntityInPack(ComponentPack* pack );
void* ComponentPack_GetFirstSetComponent(ComponentPack* pack );
Entity ComponentPack_GetFirstSetEntity(ComponentPack* pack);
void* ComponentPack_GetComponent2(ComponentPack* pack, Entity entity, bool isNotExclusive);
void* ComponentPack_GetComponent(ComponentPack* pack, Entity entity);
void* ComponentPack_GetComponentAtIndex(ComponentPack* pack, int32_t index);
void* ComponentPack_Set2(ComponentPack* pack, Entity entity, bool isNotExclusive);
void* ComponentPack_Set(ComponentPack* pack, Entity entity);
void ComponentPack_Unset(ComponentPack* pack, int32_t entityNumber);
void ComponentPack_UnsetAtIndex(ComponentPack* pack, int32_t index);
void ComponentPack_UnsetAll(ComponentPack* pack);
void ComponentPack_CopyTo(ComponentPack* pack, ComponentPack* to);
ComponentPack* ComponentPack_CreateCopy(ComponentPack* pack);
void ComponentPack_Dispose(ComponentPack* pack);
/*
std::type_index ComponentPack_GetComponentType()
{
	return std::type_index(typeid(T));
}
std::vector<OeEntity>& ComponentPack_DebugGetEntities()
{
	return Entities;
}
*/