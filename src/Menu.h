#ifndef _MENU_H_
#define _MENU_H_

#include <Arduboy2.h>

#include "Constants.h"

typedef enum __attribute__ ((packed))
{
    NONE,
    GO,
    ABOUT
} MenuOption;

class Menu
{
    public:
        Menu();
        void update(Arduboy2 * arduboy);
        void setInGame(bool inGame);
        const MenuOption popSelectedOption(); //returns selectedOption and reset it to NONE
    private:
       MenuOption selectedOption;
       int8 selection;
       bool inGame;
};

#endif
