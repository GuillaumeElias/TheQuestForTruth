#ifndef _ITEM_MANAGER_H_
#define _ITEM_MANAGER_H_

#include <Arduboy2.h>
#include "abstract/Singleton.h"
#include "Constants.h"

class ItemsManager : public Singleton<ItemsManager>
{
    public:
        ItemsManager();
        void foundClue(int8 clueNb);
        byte getCluesFound() const;
        byte getItems() const;
        void foundItem(int8 itemId);
        bool hasItem(int8 itemId) const;
    private:
        byte cluesFound, items;
};

PROGMEM static const char CLUE_PRE_TEXT[] = "You found a clue:";
PROGMEM static const char CLUE_1[] = "That's nice";
PROGMEM static const char CLUE_2[] = "No one will know";

#endif