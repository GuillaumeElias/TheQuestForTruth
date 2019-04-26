#include "ItemsManager.h"

//====================================================================
ItemsManager::ItemsManager()
    : cluesFound(0b00000000)
{
}

//====================================================================
void ItemsManager::foundClue(int8 clueNb)
{
    cluesFound |= 1 << (clueNb - 1);
}

//====================================================================
byte ItemsManager::getCluesFound() const
{
    return cluesFound;
}

//====================================================================
byte ItemsManager::getItems() const
{
    return items;
}

//====================================================================
void ItemsManager::foundItem(int8 itemId)
{
    items |= 1 << (itemId - 1);
}

//====================================================================
bool ItemsManager::hasItem(int8 itemId) const
{
    return cluesFound & (1 << (itemId - 1));
}