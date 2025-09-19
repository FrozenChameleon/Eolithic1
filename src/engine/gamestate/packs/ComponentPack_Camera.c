#include "ComponentPack_Camera.h"

#include "../../utils/Utils.h"
#include "../../utils/Logger.h"
#include "../../utils/Exception.h"

static void ResizePack(ComponentPack_Camera* pack, int newCapacity)
{
	Entity* newEntities = Utils_malloc(sizeof(Entity) * newCapacity);
	Utils_memset(newEntities, 0, sizeof(Entity) * newCapacity);
	if (pack->Entities != NULL)
	{
		Utils_memcpy(newEntities, pack->Entities, pack->_mCapacity);
		Utils_free(pack->Entities);
		pack->Entities = NULL;
	}

	Camera* newComponents = Utils_malloc(sizeof(Camera) * newCapacity);
	if (pack->Components != NULL)
	{
		Utils_memcpy(newComponents, pack->Components, pack->_mCapacity);
		Utils_free(pack->Components);
		pack->Components = NULL;
	}

	pack->Entities = newEntities;
	pack->Components = newComponents;

	pack->_mCapacity = newCapacity;
}

void ComponentPack_Camera_LogNothingEntityWarning(ComponentPack_Camera* pack)
{
	Logger_LogWarning("Attempted to use a nothing entity in a component pack");
}
void ComponentPack_Camera_Init(ComponentPack_Camera* pack, int initialSize)
{
	Utils_memset(pack, 0, sizeof(ComponentPack_Camera));

	pack->_mMaximumCapacity = 0;
	pack->_mLength = 0;

	ResizePack(pack, initialSize);
}
Camera* ComponentPack_Camera_TryGetFirstSetComponent(ComponentPack_Camera* pack, bool* wasSuccessful)
{
	int loc = ComponentPack_Camera_GetFirstSetEntityLocation(pack);
	if (loc != -1)
	{
		*wasSuccessful = true;
		return &pack->Components[loc];
	}
	else
	{
		*wasSuccessful = false;
		return ComponentPack_Camera_GetDummy(pack);
	}
}
Camera* ComponentPack_Camera_TryGetComponent(ComponentPack_Camera* pack, Entity entity, bool* wasSuccessful)
{
	int loc = ComponentPack_Camera_GetEntityLocation(pack, entity);
	if (loc != -1)
	{
		*wasSuccessful = true;
		return &pack->Components[loc];
	}
	else
	{
		*wasSuccessful = false;
		return ComponentPack_Camera_GetDummy(pack);
	}
}
bool ComponentPack_Camera_HasComponent(ComponentPack_Camera* pack, Entity entity)
{
	return (ComponentPack_Camera_GetEntityLocation(pack, entity) != -1);
}
void ComponentPack_Camera_SetMaximumCapacity(ComponentPack_Camera* pack, int value)
{
	pack->_mMaximumCapacity = value;
}
Camera* ComponentPack_Camera_GetDummy(ComponentPack_Camera* pack)
{
	return &pack->_mDummy;
}
int ComponentPack_Camera_Length(ComponentPack_Camera* pack)
{
	return pack->_mLength;
}
bool ComponentPack_Camera_Next(ComponentPack_Camera* pack, PackIterator* iter)
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
int ComponentPack_Camera_GetFirstSetEntityLocation(ComponentPack_Camera* pack)
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
int ComponentPack_Camera_GetEntityLocation(ComponentPack_Camera* pack, int entityNumber)
{
	if (entityNumber == ENTITY_NOTHING)
	{
		ComponentPack_Camera_LogNothingEntityWarning(pack);
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
bool ComponentPack_Camera_IsAnyEntityInPack(ComponentPack_Camera* pack)
{
	if (pack->_mLength > 0)
	{
		return true;
	}
	return false;
}
Camera* ComponentPack_Camera_GetFirstSetComponent(ComponentPack_Camera* pack)
{
	int loc = ComponentPack_Camera_GetFirstSetEntityLocation(pack);
	if (loc != -1)
	{
		return &pack->Components[loc];
	}
	else
	{
		Exception_Run("Cannot retrieve any component in pack: Camera", false);
		return &pack->Components[0];
	}
}
Entity ComponentPack_Camera_GetFirstSetEntity(ComponentPack_Camera* pack)
{
	int loc = ComponentPack_Camera_GetFirstSetEntityLocation(pack);
	if (loc != -1)
	{
		return pack->Entities[loc];
	}
	Exception_Run("Cannot retrieve any entity in pack: Camera", false);
	return ENTITY_NOTHING;
}
Camera* ComponentPack_Camera_GetComponentExclusive(ComponentPack_Camera* pack, Entity entity, bool isNotExclusive)
{
	return ComponentPack_Camera_SetExclusive(pack, entity, isNotExclusive);
}
Camera* ComponentPack_Camera_GetComponent(ComponentPack_Camera* pack, Entity entity)
{
	return ComponentPack_Camera_GetComponentExclusive(pack, entity, false);
}

Camera* ComponentPack_Camera_SetExclusive(ComponentPack_Camera* pack, Entity entity, bool isNotExclusive)
{
	if (entity == ENTITY_NOTHING)
	{
		ComponentPack_Camera_LogNothingEntityWarning(pack);
		return &pack->Components[0];
	}

	if (!isNotExclusive)
	{
		int loc = ComponentPack_Camera_GetEntityLocation(pack, entity);
		if (loc != -1)
		{
			return &pack->Components[loc];
		}
	}

	for (int i = 0; i < pack->_mCapacity; i += 1)
	{
		if (pack->Entities[i] != ENTITY_NOTHING)
		{
			continue;
		}

		pack->Entities[i] = entity;
		Utils_memset(&pack->Components[i], 0, sizeof(Camera));
		if ((i + 1) > pack->_mLength)
		{
			pack->_mLength = (i + 1);
		}
		return &pack->Components[i];
	}

	if ((pack->_mMaximumCapacity > 0) && (pack->_mCapacity >= pack->_mMaximumCapacity))
	{
		Logger_LogInformation("Reached maximum capacity for pack: Camera");
		return &pack->_mDummy;
	}

	Logger_LogInformation("Component pack is expanding for pack: Camera");

	ResizePack(pack, pack->_mCapacity * 2);

	return ComponentPack_Camera_SetExclusive(pack, entity, isNotExclusive);
}
Camera* ComponentPack_Camera_Set(ComponentPack_Camera* pack, Entity entity)
{
	return ComponentPack_Camera_SetExclusive(pack, entity, false);
}
void ComponentPack_Camera_Unset(ComponentPack_Camera* pack, int entityNumber)
{
	if (entityNumber == ENTITY_NOTHING)
	{
		ComponentPack_Camera_LogNothingEntityWarning(pack);
		return;
	}

	for (int i = 0; i < pack->_mLength; i += 1)
	{
		if (pack->Entities[i] == entityNumber)
		{
			ComponentPack_Camera_UnsetAtIndex(pack, i);
		}
	}
}
void ComponentPack_Camera_UnsetAtIndex(ComponentPack_Camera* pack, int index)
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
void ComponentPack_Camera_UnsetAll(ComponentPack_Camera* pack)
{
	for (int i = 0; i < pack->_mCapacity; i += 1)
	{
		pack->Entities[i] = ENTITY_NOTHING;
	}
	pack->_mLength = 0;
}
void ComponentPack_Camera_CopyTo(ComponentPack_Camera* pack, ComponentPack_Camera* to)
{
	to->_mLength = pack->_mLength;
	to->_mMaximumCapacity = pack->_mMaximumCapacity;

	if (pack->_mCapacity != to->_mCapacity) //Mismatch?
	{
		ResizePack(to, pack->_mCapacity);
	}

	Utils_memcpy(to->Entities, pack->Entities, pack->_mCapacity);  //Copy all entity data!
	Utils_memcpy(to->Components, pack->Components, pack->_mLength); //Only copy active length of components...
}
ComponentPack_Camera* ComponentPack_Camera_CreateCopy(ComponentPack_Camera* pack)
{
	ComponentPack_Camera* copyPack = Utils_malloc(sizeof(ComponentPack_Camera));
	ComponentPack_Camera_CopyTo(pack, copyPack);
	return copyPack;
}
ComponentPack_Camera* ComponentPack_Camera_Dispose(ComponentPack_Camera* pack)
{
	Utils_free(pack->Entities);
	pack->Entities = NULL;

	Utils_free(pack->Components);
	pack->Components = NULL;

	Utils_memset(pack, 0, sizeof(pack));
}
