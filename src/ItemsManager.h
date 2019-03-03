#ifndef _ITEM_MANAGER_H_
#define _ITEM_MANAGER_H_

#include <Arduboy2.h>
#include "abstract/Singleton.h"
#include "Constants.h"

class ItemsManager : public Singleton<ItemsManager>
{
    public:
        ItemsManager();
        void foundClue(int8 index);
        byte getCluesFound() const;
    private:
        byte cluesFound;
};

PROGMEM static const char CLUE_1[] PROGMEM = "This is good.";
PROGMEM static const char CLUE_2[] PROGMEM = "It is okay.";

#endif