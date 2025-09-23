#include "ComponentPack.h"

#include "../utils/Utils.h"
#include "../utils/Logger.h"
#include "../utils/Exception.h"

static void ResizePack(ComponentPack* pack, int newCapacity)
{
	Entity* newEntities = Utils_malloc(sizeof(Entity) * newCapacity);
	Utils_memset(newEntities, 0, sizeof(Entity) * newCapacity);
	if (pack->Entities != NULL)
	{
		Utils_memcpy(newEntities, pack->Entities, sizeof(Entity) * pack->_mCapacity);
		Utils_free(pack->Entities);
		pack->Entities = NULL;
	}

	void* newComponents = Utils_malloc(pack->mComponentSizeInBytes * newCapacity);
	if (pack->Components != NULL)
	{
		Utils_memcpy(newComponents, pack->Components, pack->mComponentSizeInBytes * pack->_mCapacity);
		Utils_free(pack->Components);
		pack->Components = NULL;
	}

	pack->Entities = newEntities;
	pack->Components = newComponents;

	pack->_mCapacity = newCapacity;
}

void ComponentPack_LogNothingEntityWarning(ComponentPack* pack)
{
	Logger_LogWarning("Attempted to use a nothing entity in a component pack");
}
void ComponentPack_Init(ComponentPack* pack, size_t componentSizeInBytes, int initialSize)
{
	Utils_memset(pack, 0, sizeof(ComponentPack));

	pack->mComponentSizeInBytes = componentSizeInBytes;
	pack->_mMaximumCapacity = 0;
	pack->_mLength = 0;
	pack->_mDummy = Utils_malloc(componentSizeInBytes);

	ResizePack(pack, initialSize);
}
void* ComponentPack_TryGetFirstSetComponent(ComponentPack* pack, bool* wasSuccessful)
{
	int loc = ComponentPack_GetFirstSetEntityLocation(pack);
	if (loc != -1)
	{
		*wasSuccessful = true;
		return pack->Components + (loc * pack->mComponentSizeInBytes);
	}
	else
	{
		*wasSuccessful = false;
		return ComponentPack_GetDummy(pack);
	}
}
void* ComponentPack_TryGetComponent(ComponentPack* pack, Entity entity, bool* wasSuccessful)
{
	int loc = ComponentPack_GetEntityLocation(pack, entity);
	if (loc != -1)
	{
		*wasSuccessful = true;
		return pack->Components + (loc * pack->mComponentSizeInBytes);
	}
	else
	{
		*wasSuccessful = false;
		return ComponentPack_GetDummy(pack);
	}
}
bool ComponentPack_HasComponent(ComponentPack* pack, Entity entity)
{
	return (ComponentPack_GetEntityLocation(pack, entity) != -1);
}
void ComponentPack_SetMaximumCapacity(ComponentPack* pack, int value)
{
	pack->_mMaximumCapacity = value;
}
void* ComponentPack_GetDummy(ComponentPack* pack)
{
	return &pack->_mDummy;
}
int ComponentPack_Length(ComponentPack* pack)
{
	return pack->_mLength;
}
bool ComponentPack_Next(ComponentPack* pack, PackIterator* iter)
{
	bool isComplete = false;
	while (!isComplete)
	{
		if (iter->mSeekPosition >= pack->_mLength)
		{
			return false;
		}

		if (pack->Entities[iter->mSeekPosition] != ENTITY_NOTHING)
		{
			iter->mIndex = iter->mSeekPosition;
			iter->mEntity = pack->Entities[iter->mIndex];
			iter->mSeekPosition += 1;
			return true;
		}
		else
		{
			iter->mSeekPosition += 1;
		}
	}

	return false;
}
int ComponentPack_GetFirstSetEntityLocation(ComponentPack* pack)
{
	for (int i = 0; i < pack->_mLength; i += 1)
	{
		if (pack->Entities[i] != ENTITY_NOTHING)
		{
			return i;
		}
	}
	return -1;
}
int ComponentPack_GetEntityLocation(ComponentPack* pack, int entityNumber)
{
	if (entityNumber == ENTITY_NOTHING)
	{
		ComponentPack_LogNothingEntityWarning(pack);
		return -1;
	}

	for (int i = 0; i < pack->_mLength; i += 1)
	{
		if (pack->Entities[i] == entityNumber)
		{
			return i;
		}
	}

	return -1;
}
bool ComponentPack_IsAnyEntityInPack(ComponentPack* pack)
{
	if (pack->_mLength > 0)
	{
		return true;
	}
	return false;
}
void* ComponentPack_GetFirstSetComponent(ComponentPack* pack)
{
	int loc = ComponentPack_GetFirstSetEntityLocation(pack);
	if (loc != -1)
	{
		return pack->Components + (loc * pack->mComponentSizeInBytes);
	}
	else
	{
		Exception_Run("Cannot retrieve any component in pack: Camera", false);
		return pack->Components;
	}
}
Entity ComponentPack_GetFirstSetEntity(ComponentPack* pack)
{
	int loc = ComponentPack_GetFirstSetEntityLocation(pack);
	if (loc != -1)
	{
		return pack->Entities[loc];
	}
	Exception_Run("Cannot retrieve any entity in pack: Camera", false);
	return ENTITY_NOTHING;
}
void* ComponentPack_GetComponentExclusive(ComponentPack* pack, Entity entity, bool isNotExclusive)
{
	return ComponentPack_SetExclusive(pack, entity, isNotExclusive);
}
void* ComponentPack_GetComponent(ComponentPack* pack, Entity entity)
{
	return ComponentPack_GetComponentExclusive(pack, entity, false);
}

void* ComponentPack_SetExclusive(ComponentPack* pack, Entity entity, bool isNotExclusive)
{
	if (entity == ENTITY_NOTHING)
	{
		ComponentPack_LogNothingEntityWarning(pack);
		return pack->Components;
	}

	if (!isNotExclusive)
	{
		int loc = ComponentPack_GetEntityLocation(pack, entity);
		if (loc != -1)
		{
			return pack->Components + (loc * pack->mComponentSizeInBytes);
		}
	}

	for (int i = 0; i < pack->_mCapacity; i += 1)
	{
		if (pack->Entities[i] != ENTITY_NOTHING)
		{
			continue;
		}

		pack->Entities[i] = entity;
		Utils_memset(pack->Components + (i * pack->mComponentSizeInBytes), 0, pack->mComponentSizeInBytes);
		if ((i + 1) > pack->_mLength)
		{
			pack->_mLength = (i + 1);
		}
		return pack->Components + (i * pack->mComponentSizeInBytes);
	}

	if ((pack->_mMaximumCapacity > 0) && (pack->_mCapacity >= pack->_mMaximumCapacity))
	{
		Logger_LogInformation("Reached maximum capacity for pack: Camera");
		return &pack->_mDummy;
	}

	Logger_LogInformation("Component pack is expanding for pack: Camera");

	ResizePack(pack, pack->_mCapacity * 2);

	return ComponentPack_SetExclusive(pack, entity, isNotExclusive);
}
void* ComponentPack_Set(ComponentPack* pack, Entity entity)
{
	return ComponentPack_SetExclusive(pack, entity, false);
}
void ComponentPack_Unset(ComponentPack* pack, int entityNumber)
{
	if (entityNumber == ENTITY_NOTHING)
	{
		ComponentPack_LogNothingEntityWarning(pack);
		return;
	}

	for (int i = 0; i < pack->_mLength; i += 1)
	{
		if (pack->Entities[i] == entityNumber)
		{
			ComponentPack_UnsetAtIndex(pack, i);
		}
	}
}
void ComponentPack_UnsetAtIndex(ComponentPack* pack, int index)
{
	pack->Entities[index] = ENTITY_NOTHING;

	if (pack->_mLength == (index + 1))
	{
		for (int i = (pack->_mCapacity - 1); i >= 0; i -= 1) //Need to find new last entity
		{
			if (pack->Entities[i] != ENTITY_NOTHING)
			{
				pack->_mLength = (i + 1);
				return;
			}
		}

		pack->_mLength = 0; //Empty...
	}
}
void ComponentPack_UnsetAll(ComponentPack* pack)
{
	for (int i = 0; i < pack->_mCapacity; i += 1)
	{
		pack->Entities[i] = ENTITY_NOTHING;
	}
	pack->_mLength = 0;
}
void ComponentPack_CopyTo(ComponentPack* from, ComponentPack* to)
{
	to->_mLength = from->_mLength;
	to->_mMaximumCapacity = from->_mMaximumCapacity;

	if (from->_mCapacity != to->_mCapacity) //Mismatch?
	{
		ResizePack(to, from->_mCapacity);
	}

	Utils_memcpy(to->Entities, from->Entities, from->_mCapacity);  //Copy all entity data!
	Utils_memcpy(to->Components, from->Components, from->_mLength); //Only copy active length of components...
}
ComponentPack* ComponentPack_CreateCopy(ComponentPack* pack)
{
	ComponentPack* copyPack = Utils_malloc(sizeof(ComponentPack));
	ComponentPack_CopyTo(pack, copyPack);
	return copyPack;
}
void ComponentPack_Dispose(ComponentPack* pack)
{
	Utils_free(pack->_mDummy);
	pack->_mDummy = NULL;

	Utils_free(pack->Entities);
	pack->Entities = NULL;

	Utils_free(pack->Components);
	pack->Components = NULL;

	Utils_memset(pack, 0, sizeof(pack));
}
