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
    private:
        byte cluesFound;
};

PROGMEM static const char CLUE_1[] = "This is your\n first clue.\n ...that's nice.";
PROGMEM static const char CLUE_2[] = "Second clue:\nNo one will know.";

#endif