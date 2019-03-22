#ifndef _MENU_H_
#define _MENU_H_

#include <Arduboy2.h>

#include "Constants.h"

typedef enum __attribute__ ((packed))
{
    NONE,
    GO,
    ABOUT,
    CLUES,
    INVENTORY
} MenuOption;

class Menu
{
    public:
        Menu();
        void update(Arduboy2 * arduboy);
        void setInGame(bool inGame);
        const MenuOption getSelectedOption() const;
        void clearSelectedOption();
    private:
       void displayClues(Arduboy2 * arduboy);
       void printFromProgmem(Arduboy2 * arduboy, char * textInProgMem);
       
       MenuOption selectedOption;
       int8 selection;
       bool inGame;
};

#endif
