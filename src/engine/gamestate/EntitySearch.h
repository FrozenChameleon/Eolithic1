#pragma once

#include "../gamestate/ComponentType.h"
#include "../utils/Macros.h"

//EntitySearch's are created on the "Just This Frame" so they do not need to be manually disposed of.
typedef struct EntitySearch
{
	Entity* entities;
	int32_t len;
	int32_t cap;
} EntitySearch;

void EntitySearch_AddEntityToSearch(EntitySearch* search, Entity addThis);
bool EntitySearch_Check(bool isValid, bool isReverse);
EntitySearch* EntitySearch_CreateNewAllEntitySearch();
EntitySearch* EntitySearch_CreateNewBlankSearchSetCapacity(int32_t cap);
EntitySearch* EntitySearch_CreateNewBlankSearch();
EntitySearch* EntitySearch_SearchForEntitiesWithThisName(const EntitySearch* lookThroughThis, EntitySearch* addToThis,
	const char* name, bool isReverse);
EntitySearch* EntitySearch_SearchForEntitiesWithThisParentNumber(const EntitySearch* lookThroughThis, EntitySearch* addToThis,
	int value, bool isReverse);
EntitySearch* EntitySearch_SearchForEntitiesWithThisIntTag(const EntitySearch* lookThroughThis, EntitySearch* addToThis,
	int value, bool isReverse);
EntitySearch* EntitySearch_SearchForEntitiesWithThisComponent(ComponentType ctype, const EntitySearch* lookThroughThis, EntitySearch* addToThis, 
	bool isReverse);