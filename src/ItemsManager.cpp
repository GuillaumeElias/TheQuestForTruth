#include "ItemsManager.h"

//====================================================================
ItemsManager::ItemsManager()
    : cluesFound(0b00000000)
{
}

//====================================================================
void ItemsManager::foundClue(int8 index)
{
    cluesFound |= 1 << index;
}

//====================================================================
byte ItemsManager::getCluesFound() const
{
    return cluesFound;
}